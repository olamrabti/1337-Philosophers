/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:46:40 by olamrabt          #+#    #+#             */
/*   Updated: 2024/07/09 12:24:11 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_turn(t_philo *philo, char *msg)
{
    if (!someone_is_dead(philo) && philo->dinner->all_full != 1)
    {
        pthread_mutex_lock(&philo->dinner->read_mtx);
        pthread_mutex_lock(&philo->dinner->print_mtx);
        print_philosopher(philo);
        printf("at %zu seconds: philo %zu %s\n", get_time_ms() - philo->dinner->start_time, philo->id, msg);
        pthread_mutex_unlock(&philo->dinner->read_mtx);
        pthread_mutex_unlock(&philo->dinner->print_mtx);
        return;
    }
}

void take_fork(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_turn(philo, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    print_turn(philo, "has taken a fork");
}
// TODO : li bghyti
void ft_usleep(size_t time)
{
    size_t start_time;

    start_time = get_time_ms();
    while (get_time_ms() - start_time < time)
    {
        //
        usleep(500);
    }
}

void *start_simulation(void *arg)
{
    t_philo *philo;
    philo = (t_philo *)arg;
    if (philo->id % 2)
        ft_usleep(philo->dinner->time_to_eat);
    while (1)
    {
        if (someone_is_dead(philo))
            return NULL;
        pthread_mutex_lock(&philo->dinner->check_meals_mtx);
        if (philo->dinner->eat_limit != -1 && philo->dinner->all_full == 1)
        {
            pthread_mutex_unlock(&philo->dinner->check_meals_mtx);
            return NULL;
        }
        pthread_mutex_unlock(&philo->dinner->check_meals_mtx);

        take_fork(philo);
        print_turn(philo, "is eating");
        pthread_mutex_lock(&philo->dinner->read_mtx);
        philo->last_meal = get_time_ms();
        pthread_mutex_unlock(&philo->dinner->read_mtx);

        ft_usleep(philo->dinner->time_to_eat);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);

        if (philo->dinner->eat_limit != -1)
            incr_eaten_meals(philo);

        print_turn(philo, "is sleeping");
        ft_usleep(philo->dinner->time_to_sleep);
        print_turn(philo, "is thinking");
    }
    return NULL;
}

void ft_monitor(t_dinner *dinner)
{
    size_t i;

    while (1)
    {
        i = 0;
        // if (philos_are_full(dinner))
        // {
        //     declare_philos_are_full(dinner);
        //     return;
        // }
        pthread_mutex_lock(&dinner->read_mtx);
        while (i < dinner->number_of_philos)
        {
            if (get_time_ms() - dinner->philos[i].last_meal >= dinner->time_to_die)
            {
                pthread_mutex_unlock(&dinner->read_mtx);
                print_turn(&dinner->philos[i], "died");
                declare_someone_is_dead(dinner);
                return;
            }
            i++;
        }
        pthread_mutex_unlock(&dinner->read_mtx);
    }
}

int create_philosophers(t_dinner *dinner, t_addr **addr)
{
    size_t i;
    dinner->philos = ft_calloc(addr, dinner->number_of_philos, sizeof(t_philo));
    if (dinner->philos == NULL)
        return FAILURE;
    i = 0;
    dinner->start_time = get_time_ms();
    while (i < dinner->number_of_philos)
    {
        dinner->philos[i].id = i + 1;
        dinner->philos[i].eaten_meals = 0;
        dinner->philos[i].left_fork = &dinner->forks[i];
        dinner->philos[i].right_fork = &dinner->forks[(i + 1) % dinner->number_of_philos];
        dinner->philos[i].ret_val = 0;
        dinner->philos[i].dinner = dinner;
        dinner->philos[i].last_meal = get_time_ms();
        if (pthread_create(&dinner->philos[i].thread, NULL, start_simulation, &dinner->philos[i]))
            return FAILURE;

        i++;
    }
    return SUCCESS;
}

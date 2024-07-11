/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:46:40 by olamrabt          #+#    #+#             */
/*   Updated: 2024/07/11 14:57:25 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_turn(t_philo *philo, char *msg)
{
    if (!someone_is_dead(philo) && !ft_all_full(philo))
    {
        pthread_mutex_lock(&philo->simulation->print_mtx);
        printf("%zu %zu %s\n", get_time_ms() - philo->simulation->start_time, philo->id, msg);
        pthread_mutex_unlock(&philo->simulation->print_mtx);
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
void ft_usleep(size_t time, t_philo *philo)
{
    size_t start_time;

    start_time = get_time_ms();
    while (get_time_ms() - start_time < time)
    {
        if (raised_flags(philo))
            return;
        usleep(500);
    }
}

int ft_all_full(t_philo *philo)
{
    if (philo->simulation->eat_limit == -1)
        return 0;
    pthread_mutex_lock(&philo->simulation->full);
    if (philo->simulation->all_full == 1)
        return pthread_mutex_unlock(&philo->simulation->full), 1;
    pthread_mutex_unlock(&philo->simulation->full);
    return 0;
}
int one_philo(t_philo *philo)
{
    if (philo->left_fork == philo->right_fork)
    {
        pthread_mutex_lock(philo->left_fork);
        print_turn(philo, "has taken a fork");
        pthread_mutex_unlock(philo->left_fork);
        ft_usleep(philo->simulation->time_to_eat, philo);
        return 1;
    }
    return 0;
}

void *start_simulation(void *arg)
{
    t_philo *philo;
    philo = (t_philo *)arg;
    if (one_philo(philo))
        return NULL;
    if (philo->id % 2)
        ft_usleep(philo->simulation->time_to_eat, philo);
    while (!someone_is_dead(philo) && !ft_all_full(philo))
    {
        take_fork(philo);
        pthread_mutex_lock(&philo->simulation->read_mtx);
        philo->last_meal = get_time_ms();
        if (!philo->last_meal)
            return NULL;
        pthread_mutex_unlock(&philo->simulation->read_mtx);
        print_turn(philo, "is eating");
        ft_usleep(philo->simulation->time_to_eat, philo);
        incr_eaten_meals(philo);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        print_turn(philo, "is sleeping");
        ft_usleep(philo->simulation->time_to_sleep, philo);
        print_turn(philo, "is thinking");
    }
    return NULL;
}

void ft_monitor(t_simulation *simulation)
{
    size_t i;

    while (1)
    {
        i = 0;
        if (simulation->eat_limit != -1 && !philos_are_full(simulation))
        {
            declare_philos_are_full(simulation);
            return;
        }
        pthread_mutex_lock(&simulation->read_mtx);
        while (i < simulation->number_of_philos)
        {
            if (get_time_ms() - simulation->philos[i].last_meal >= simulation->time_to_die)
            {
                pthread_mutex_unlock(&simulation->read_mtx);
                print_turn(&simulation->philos[i], "died");
                declare_someone_is_dead(simulation);
                return;
            }
            i++;
        }
        pthread_mutex_unlock(&simulation->read_mtx);
    }
}

int create_philosophers(t_simulation *simulation, t_addr **addr)
{
    size_t i;
    simulation->philos = ft_calloc(addr, simulation->number_of_philos, sizeof(t_philo));
    if (simulation->philos == NULL)
        return FAILURE;
    i = 0;
    simulation->start_time = get_time_ms();
    while (i < simulation->number_of_philos)
    {
        simulation->philos[i].id = i + 1;
        simulation->philos[i].eaten_meals = 0;
        simulation->philos[i].left_fork = &simulation->forks[i];
        simulation->philos[i].right_fork = &simulation->forks[(i + 1) % simulation->number_of_philos];
        simulation->philos[i].ret_val = 0;
        simulation->philos[i].simulation = simulation;
        simulation->philos[i].last_meal = get_time_ms();
        if (pthread_create(&simulation->philos[i].thread, NULL, start_simulation, &simulation->philos[i]))
            return FAILURE;

        i++;
    }
    return SUCCESS;
}

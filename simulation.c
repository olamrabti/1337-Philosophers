/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:46:40 by olamrabt          #+#    #+#             */
/*   Updated: 2024/07/11 17:06:51 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void take_fork(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_turn(philo, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    print_turn(philo, "has taken a fork");
}

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
// TODO : li bghyti
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
        ft_usleep(philo->simulation->time_to_eat, philo); // if you reverse orders with th following line it hangs 
        incr_eaten_meals(philo);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        print_turn(philo, "is sleeping"); //NOTE it breaks inside usleep, doest it print after death declaration ?
        ft_usleep(philo->simulation->time_to_sleep, philo);
        print_turn(philo, "is thinking");
    }
    return NULL;
}




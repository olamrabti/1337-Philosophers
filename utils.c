/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:39:11 by olamrabt          #+#    #+#             */
/*   Updated: 2024/07/11 17:10:40 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t get_time_ms()
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL) == -1)
        return 0;
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

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

int raised_flags(t_philo *philo)
{
    if (ft_all_full(philo))
        return 1;
    pthread_mutex_lock(&philo->simulation->is_dead_mtx);
    if (philo->simulation->dead_philo)
        return pthread_mutex_unlock(&philo->simulation->is_dead_mtx), 1;
    pthread_mutex_unlock(&philo->simulation->is_dead_mtx);
    return 0;
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

int someone_is_dead(t_philo *philo)
{
    pthread_mutex_lock(&philo->simulation->is_dead_mtx);
    if (philo->simulation->dead_philo == 1)
    {
        pthread_mutex_unlock(&philo->simulation->is_dead_mtx);
        return 1;
    }
    pthread_mutex_unlock(&philo->simulation->is_dead_mtx);
    return 0;
}
 
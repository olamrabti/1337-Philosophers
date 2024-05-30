/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:46:40 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/30 17:34:34 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *start_simulation(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *) arg;
    while(philo->monitor->is_ready_flag == 0) // needs a mutex to avoid data race
        ; // dont start until all threads are ready
    return NULL;
}

int create_philosophers(t_monitor *monitor, t_addr **addr)
{
    size_t i ;
    monitor->philos = ft_calloc(addr, monitor->number_of_philos , sizeof(t_philo));
    if (monitor->philos == NULL)
        return FAILURE;
    i = 0;
    while(i < monitor->number_of_philos)
    {
        monitor->philos[i].id = i + 1;
        monitor->philos[i].last_meal = monitor->start_time;
        monitor->philos[i].dead = 0;
        monitor->philos[i].eaten_meals = 0;
        monitor->philos[i].left_fork = &monitor->forks[i];
        monitor->philos[i].right_fork = &monitor->forks[(i + 1) % monitor->number_of_philos];
        monitor->philos[i].monitor = monitor;
        if (pthread_create(&monitor->philos[i].thread, NULL, start_simulation, &monitor->philos[i])) // maybe for later !
            return FAILURE;
        i++;
    }
    return SUCCESS;
}

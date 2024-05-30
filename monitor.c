/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:48:08 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/30 12:43:03 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor_work(void *arg)
{
    t_monitor *monitor;
    size_t i ;
    size_t current_time ;
    size_t time_since_last_meal;

    monitor = (t_monitor *)arg;
    while (!monitor->end_simulation)
    {
        i = 0;
        while(i < monitor->number_of_philos)
        {
            current_time = get_current_time_ms();
            time_since_last_meal = current_time - monitor->philos[i].last_meal;
            if (time_since_last_meal > monitor->time_to_die)
            {
                printf("Philosopher %zu has died.\n", monitor->philos[i].id);
                monitor->end_simulation = 1;
                break;
            }
            i++;
        }
        if (monitor->full_philos >= monitor->number_of_philos)
        {
            printf("All philosophers are full.\n");
            monitor->end_simulation = 1;
            break;
        }
    }
    return NULL;
}

int start_monitor(t_monitor *monitor)
{
    if (pthread_create(&monitor->monitor_thread, NULL, monitor_work, monitor) != 0)
        return FAILURE;
    return SUCCESS;
}

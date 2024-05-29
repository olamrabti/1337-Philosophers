/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:28:14 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/29 16:50:04 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_params(t_monitor *monitor)
{
        printf("number_of_philos : %zu\n", monitor->number_of_philos);
        printf("full_philos : %d\n", monitor->full_philos);
        printf("time_to_die : %zu\n", monitor->time_to_die);
        printf("time_to_eat : %zu\n", monitor->time_to_eat);
        printf("time_to_sleep : %zu\n", monitor->time_to_sleep);
        printf("eat_limit : %d\n", monitor->eat_limit);
}
int main(int ac, char **av)
{
    t_monitor *monitor;



    monitor = malloc(sizeof(t_monitor));
    if ((ac == 5 || ac == 6) && parse_args(monitor, av, ac) == EXIT_SUCCESS)
    {
        if (monitor->time_to_die < 60000 || monitor->time_to_eat < 60000 || monitor->time_to_sleep < 60000)
            return printf("Use timestamps major than 60\n"), FAILURE;
        print_params(monitor);
        // philos_are_dining(&monitor);
        // clean(&monitor);
        return SUCCESS;
    }
    return printf("Unsuffisant parameters\n"), FAILURE;
}
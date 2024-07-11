/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:28:14 by olamrabt          #+#    #+#             */
/*   Updated: 2024/07/11 14:52:44 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_clean(t_simulation *simulation)
{
    size_t i;
    i = 0;
    while (i < simulation->number_of_philos)
    {
        pthread_join(simulation->philos[i].thread, &simulation->philos[i].ret_val);
        i++;
    }
    i = 0;
    while (i < simulation->number_of_philos)
        pthread_mutex_destroy(&simulation->forks[i++]);
    pthread_mutex_destroy(&simulation->print_mtx);
    pthread_mutex_destroy(&simulation->full);
    pthread_mutex_destroy(&simulation->is_dead_mtx);
    pthread_mutex_destroy(&simulation->read_mtx);
    pthread_mutex_destroy(&simulation->check_meals_mtx);
}

int main(int ac, char **av)
{
    t_simulation *simulation;
    t_addr *addr;

    addr = NULL;
    simulation = ft_calloc(&addr, 1, sizeof(t_simulation));
    if (!simulation)
        return FAILURE;
    if (ac < 5 || ac > 6)
        return print_exit("Too many or insufficient parameters", &addr);
    if (parse_args(simulation, av, ac))
        return print_exit(NULL, &addr);
    if (ft_init(simulation, &addr))
        return print_exit("Failed to initialize forks", &addr);
    if (create_philosophers(simulation, &addr))
        return print_exit("Failed to create philosopher threads", &addr);
    ft_monitor(simulation);
    ft_clean(simulation);
    return print_exit(NULL, &addr),SUCCESS;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:28:14 by olamrabt          #+#    #+#             */
/*   Updated: 2024/07/10 16:10:07 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_params(t_simulation *simulation)
{
    printf("number_of_philos : %zu\n", simulation->number_of_philos);
    printf("full_philos : %zu\n", simulation->full_philos);
    printf("time_to_die : %zu\n", simulation->time_to_die);
    printf("time_to_eat : %zu\n", simulation->time_to_eat);
    printf("time_to_sleep : %zu\n", simulation->time_to_sleep);
    printf("eat_limit : %d\n", simulation->eat_limit);
}

int main(int ac, char **av)
{
    t_simulation *simulation;
    size_t i ;
    t_addr *addr;

    addr = NULL;
    simulation = ft_calloc(&addr, 1, sizeof(t_simulation));
    if (!simulation)
        return FAILURE;
    if (parse_args(simulation, av, ac))
        return print_exit("Too many or insufficient parameters", &addr);
    // if (simulation->time_to_die < 60 || simulation->time_to_eat < 60 || simulation->time_to_sleep < 60)
    //     return print_exit("Use timestamps major than 60", &addr);
    if (ft_init(simulation, &addr))
        return print_exit("Failed to initialize forks", &addr);
    if (create_philosophers(simulation, &addr))
        return print_exit("Failed to create philosopher threads", &addr);

    ft_monitor(simulation);

    i = 0;
    while (i < simulation->number_of_philos)
    {
        pthread_join(simulation->philos[i].thread, &simulation->philos[i].ret_val);
        i++;
    }
    i = 0;
    while (i < simulation->number_of_philos)
        pthread_mutex_destroy(&simulation->forks[i++]);
    // pthread_mutex_unlock(&simulation->print_mtx);
    pthread_mutex_destroy(&simulation->print_mtx);
    pthread_mutex_destroy(&simulation->full);
    pthread_mutex_destroy(&simulation->is_dead_mtx);
    pthread_mutex_destroy(&simulation->read_mtx);
    pthread_mutex_destroy(&simulation->check_meals_mtx);
    return SUCCESS;
}

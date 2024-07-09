/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:28:14 by olamrabt          #+#    #+#             */
/*   Updated: 2024/07/09 12:07:02 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_params(t_dinner *dinner)
{
    printf("number_of_philos : %zu\n", dinner->number_of_philos);
    printf("full_philos : %zu\n", dinner->full_philos);
    printf("time_to_die : %zu\n", dinner->time_to_die);
    printf("time_to_eat : %zu\n", dinner->time_to_eat);
    printf("time_to_sleep : %zu\n", dinner->time_to_sleep);
    printf("eat_limit : %d\n", dinner->eat_limit);
}

int main(int ac, char **av)
{
    t_dinner *dinner;
    size_t i ;
    t_addr *addr;

    addr = NULL;
    dinner = ft_calloc(&addr, 1, sizeof(t_dinner));
    if (!dinner)
        return FAILURE;
    if (parse_args(dinner, av, ac))
        return print_exit("Too many or insufficient parameters", &addr);
    // if (dinner->time_to_die < 60 || dinner->time_to_eat < 60 || dinner->time_to_sleep < 60)
    //     return print_exit("Use timestamps major than 60", &addr);
    if (ft_init(dinner, &addr))
        return print_exit("Failed to initialize forks", &addr);
    if (create_philosophers(dinner, &addr))
        return print_exit("Failed to create philosopher threads", &addr);

    ft_monitor(dinner);

    i = 0;
    while (i < dinner->number_of_philos)
    {
        pthread_join(dinner->philos[i].thread, &dinner->philos[i].ret_val);
        i++;
    }
    i = 0;
    while (i < dinner->number_of_philos)
        pthread_mutex_destroy(&dinner->forks[i++]);
    // pthread_mutex_unlock(&dinner->print_mtx);
    pthread_mutex_destroy(&dinner->print_mtx);
    pthread_mutex_destroy(&dinner->is_dead_mtx);
    pthread_mutex_destroy(&dinner->read_mtx);
    pthread_mutex_destroy(&dinner->check_meals_mtx);
    return SUCCESS;
}

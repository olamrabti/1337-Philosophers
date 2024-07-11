/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:28:14 by olamrabt          #+#    #+#             */
/*   Updated: 2024/07/11 17:08:04 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int print_exit(char *msg, t_addr **addr)
{
    if (msg)
        printf("%s\n", msg);
    ft_lstclear(addr, free);
    return FAILURE;
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

int ft_init(t_simulation *simulation, t_addr **addr)
{
    size_t i;

    simulation->forks = ft_calloc(addr, simulation->number_of_philos, sizeof(pthread_mutex_t));
    simulation->dead_philo = 0;
    simulation->full_philos = 0;
    simulation->all_full = 0;
    if (simulation->forks == NULL)
        return FAILURE;
    i = 0;
    while (i < simulation->number_of_philos)
        if (pthread_mutex_init(&simulation->forks[i++], NULL))
            return FAILURE;
    if (pthread_mutex_init(&simulation->print_mtx, NULL))
        return FAILURE;
    if (pthread_mutex_init(&simulation->full, NULL))
        return FAILURE;
    if (pthread_mutex_init(&simulation->read_mtx, NULL))
        return FAILURE;
    if (pthread_mutex_init(&simulation->is_dead_mtx, NULL))
        return FAILURE;
    if (pthread_mutex_init(&simulation->check_meals_mtx, NULL))
        return FAILURE;
    return SUCCESS;
}

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

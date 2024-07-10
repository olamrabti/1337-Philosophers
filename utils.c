/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:39:11 by olamrabt          #+#    #+#             */
/*   Updated: 2024/07/10 15:34:28 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
size_t get_time_ms()
{
    struct timeval tv;
    // should it have a mutex ?

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void print_philosopher(t_philo *philo)
{
    pthread_mutex_lock(&philo->simulation->is_dead_mtx);
    printf("\nPhilosopher %zu - Last Meal: %zu, Eaten Meals: %d\n",
           philo->id, philo->last_meal, philo->eaten_meals);
    pthread_mutex_unlock(&philo->simulation->is_dead_mtx);
}
int print_exit(char *msg, t_addr **addr)
{
    printf("%s\n", msg);
    ft_lstclear(addr, free);
    return FAILURE;
}

// int is_ready(t_simulation *simulation)
// {
//     pthread_mutex_lock(&simulation->read_mtx);
//     return simulation->is_ready_flag;
// }
void yes_is_ready(t_simulation *simulation)
{
    pthread_mutex_lock(&simulation->read_mtx);
    simulation->start_time = get_time_ms();
    pthread_mutex_unlock(&simulation->read_mtx);
}
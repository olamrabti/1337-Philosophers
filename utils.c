/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:39:11 by olamrabt          #+#    #+#             */
/*   Updated: 2024/07/09 12:07:02 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_init(t_dinner *dinner, t_addr **addr)
{
    size_t i;

    dinner->forks = ft_calloc(addr, dinner->number_of_philos, sizeof(pthread_mutex_t));
    dinner->dead_philo = 0;
    dinner->full_philos = 0;
    if (dinner->forks == NULL)
        return FAILURE;
    i = 0;
    while (i < dinner->number_of_philos)
        if (pthread_mutex_init(&dinner->forks[i++], NULL))
            return FAILURE;
    if (pthread_mutex_init(&dinner->print_mtx, NULL))
        return FAILURE;
    if (pthread_mutex_init(&dinner->read_mtx, NULL))
        return FAILURE;
    if (pthread_mutex_init(&dinner->is_dead_mtx, NULL))
        return FAILURE;
    if (pthread_mutex_init(&dinner->check_meals_mtx, NULL))
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
    pthread_mutex_lock(&philo->dinner->is_dead_mtx);
    printf("\nPhilosopher %zu - Last Meal: %zu, Eaten Meals: %d\n",
           philo->id, philo->last_meal, philo->eaten_meals);
    pthread_mutex_unlock(&philo->dinner->is_dead_mtx);
}
int print_exit(char *msg, t_addr **addr)
{
    printf("%s\n", msg);
    ft_lstclear(addr, free);
    return FAILURE;
}

// int is_ready(t_dinner *dinner)
// {
//     pthread_mutex_lock(&dinner->read_mtx);
//     return dinner->is_ready_flag;
// }
void yes_is_ready(t_dinner *dinner)
{
    pthread_mutex_lock(&dinner->read_mtx);
    dinner->start_time = get_time_ms();
    pthread_mutex_unlock(&dinner->read_mtx);
}
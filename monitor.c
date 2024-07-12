/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:22:09 by olamrabt          #+#    #+#             */
/*   Updated: 2024/07/12 09:30:09 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	incr_eaten_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->simulation->check_meals_mtx);
	philo->eaten_meals++;
	pthread_mutex_unlock(&philo->simulation->check_meals_mtx);
}

void	declare_someone_is_dead(t_simulation *simulation)
{
	pthread_mutex_lock(&simulation->is_dead_mtx);
	simulation->dead_philo = 1;
	pthread_mutex_unlock(&simulation->is_dead_mtx);
}

int	philos_are_full(t_simulation *simulation)
{
	size_t	i;
	int		temp_el;

	temp_el = simulation->eat_limit;
	i = 0;
	while (i < simulation->number_of_philos)
	{
		pthread_mutex_lock(&simulation->check_meals_mtx);
		if (simulation->philos[i].eaten_meals < temp_el)
			return (pthread_mutex_unlock(&simulation->check_meals_mtx), 1);
		pthread_mutex_unlock(&simulation->check_meals_mtx);
		i++;
	}
	return (0);
}

void	declare_philos_are_full(t_simulation *simulation)
{
	pthread_mutex_lock(&simulation->full);
	pthread_mutex_lock(&simulation->print_mtx);
	simulation->all_full = 1;
	pthread_mutex_unlock(&simulation->full);
}

void	ft_monitor(t_simulation *simulation)
{
	size_t	i;

	while (1)
	{
		i = 0;
		if (simulation->eat_limit != -1 && !philos_are_full(simulation))
		{
			declare_philos_are_full(simulation);
			return ;
		}
		pthread_mutex_lock(&simulation->read_mtx);
		while (i < simulation->number_of_philos)
		{
			if (get_time_ms() - simulation->philos[i].last_meal \
			>= simulation->time_to_die)
			{
				pthread_mutex_unlock(&simulation->read_mtx);
				print_turn(&simulation->philos[i], "died");
				declare_someone_is_dead(simulation);
				return ;
			}
			i++;
		}
		pthread_mutex_unlock(&simulation->read_mtx);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:14:49 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/29 18:19:27 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h> // gettimeofday

# define FAILURE 1;
# define SUCCESS 0;

typedef struct monitor
{
    size_t number_of_philos;
    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    size_t start_time;
    int eat_limit;
    int full_philos; // once full philos  == philos number break 
    int end_simulation; // flag to stop the program if one philo died or all philos are full
} t_monitor;

typedef struct philo
{
    size_t id; // will be usefull to check odd philos
    size_t last_meal; // to determine if he's dead 
    int dead;
    int eaten_meals; // to stop eating if reached the limit
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_t		thread; // every philo is a thread
    t_monitor *monitor;
} t_philo;

int parse_args(t_monitor *monitor, char **av, int ac);


#endif
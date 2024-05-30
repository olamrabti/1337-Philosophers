/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:14:49 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/30 15:49:24 by olamrabt         ###   ########.fr       */
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
    size_t full_philos;
    int end_simulation;
    int is_ready_flag;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    pthread_mutex_t is_ready;
    pthread_t monitor_thread;
    struct philo *philos;
} t_monitor;

typedef struct philo
{
    size_t id;
    size_t last_meal;
    int dead;
    int eaten_meals;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_t thread;
    t_monitor *monitor;
} t_philo;

typedef struct s_addr
{
	void				*address;
	struct s_addr		*nxt;
}	t_addr;

void	*ft_calloc(t_addr **addr, size_t count, size_t size);
t_addr	*new_addr(char *value);
int	add_addr(t_addr **list, t_addr *new);
void	ft_lstclear(t_addr **lst, void (*del)(void *));


int parse_args(t_monitor *monitor, char **av, int ac);
void *monitor_work(void *arg);
void *start_simulation(void *arg);
int create_philosophers(t_monitor *monitor, t_addr **addr);
long get_current_time_ms();

#endif
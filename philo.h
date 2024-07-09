/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:14:49 by olamrabt          #+#    #+#             */
/*   Updated: 2024/07/09 12:19:30 by olamrabt         ###   ########.fr       */
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

typedef struct dinner
{
    size_t number_of_philos;
    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    size_t start_time;
    int eat_limit;
    int dead_philo;
    int all_full;
    size_t full_philos;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mtx;
    pthread_mutex_t read_mtx;
    pthread_mutex_t is_dead_mtx;
    pthread_mutex_t check_meals_mtx;
    struct philo *philos;
} t_dinner;

typedef struct philo
{
    size_t id;
    size_t last_meal;
    int eaten_meals;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_t thread;
    void *ret_val; // NOTE : leave it or remove it
    t_dinner *dinner;
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
int parse_args(t_dinner *dinner, char **av, int ac);
void *start_simulation(void *arg);
int create_philosophers(t_dinner *dinner, t_addr **addr);
size_t get_time_ms();
int ft_init(t_dinner *dinner, t_addr **addr);
void print_philosopher(t_philo *philo);
int print_exit(char *msg, t_addr **addr);
// int is_ready(t_dinner *dinner);
void yes_is_ready(t_dinner *dinner);
void ft_monitor(t_dinner *dinner);
void print_params(t_dinner *dinner);
int someone_is_dead(t_philo *philo);
int get_eaten_meals(t_philo *philo);
void incr_eaten_meals(t_philo *philo);
void declare_someone_is_dead(t_dinner *dinner);
int philos_are_full(t_dinner *dinner);
void declare_philos_are_full(t_dinner *dinner);

#endif
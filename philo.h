/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:14:49 by olamrabt          #+#    #+#             */
/*   Updated: 2024/07/11 17:12:47 by olamrabt         ###   ########.fr       */
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
#include <sys/time.h>

# define FAILURE 1;
# define SUCCESS 0;

typedef struct simulation
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
    pthread_mutex_t full;
    struct philo *philos;
} t_simulation;

typedef struct philo
{
    size_t id;
    size_t last_meal;
    int eaten_meals;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_t thread;
    void *ret_val; // NOTE : leave it or remove it
    t_simulation *simulation;
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
int parse_args(t_simulation *simulation, char **av, int ac);
void *start_simulation(void *arg);
int create_philosophers(t_simulation *simulation, t_addr **addr);
size_t get_time_ms();
int ft_init(t_simulation *simulation, t_addr **addr);
int print_exit(char *msg, t_addr **addr);
void print_turn(t_philo *philo, char *msg);
void ft_usleep(size_t time, t_philo *philo);
void ft_monitor(t_simulation *simulation);
int someone_is_dead(t_philo *philo);
void incr_eaten_meals(t_philo *philo);
void declare_someone_is_dead(t_simulation *simulation);
int philos_are_full(t_simulation *simulation);
void declare_philos_are_full(t_simulation *simulation);
int raised_flags(t_philo *philo);
int ft_all_full(t_philo *philo);

#endif
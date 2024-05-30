/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:28:14 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/30 15:56:04 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_params(t_monitor *monitor)
{
    printf("number_of_philos : %zu\n", monitor->number_of_philos);
    printf("full_philos : %zu\n", monitor->full_philos);
    printf("time_to_die : %zu\n", monitor->time_to_die);
    printf("time_to_eat : %zu\n", monitor->time_to_eat);
    printf("time_to_sleep : %zu\n", monitor->time_to_sleep);
    printf("eat_limit : %d\n", monitor->eat_limit);
}

int ft_init(t_monitor *monitor, t_addr **addr)
{
    size_t i ;

    monitor->forks = ft_calloc(addr, monitor->number_of_philos , sizeof(pthread_mutex_t));
    if (monitor->forks == NULL)
        return FAILURE;
    i = 0;
    while (i < monitor->number_of_philos)
        if (pthread_mutex_init(&monitor->forks[i++], NULL))
            return FAILURE;
    if (pthread_mutex_init(&monitor->print, NULL))
        return FAILURE;
    if (pthread_mutex_init(&monitor->is_ready, NULL))
        return FAILURE;
    return SUCCESS;
}
long get_current_time_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void print_philosopher(t_philo *philo)
{
    printf("Philosopher %zu - Last Meal: %zu, Dead: %d, Eaten Meals: %d\n",
           philo->id, philo->last_meal, philo->dead, philo->eaten_meals);
}
int  print_exit(char *msg,t_addr **addr)
{
    printf("%s\n", msg);
    ft_lstclear(addr, free);
    return FAILURE;
}

int main(int ac, char **av)
{
    t_monitor *monitor;
    size_t i ;
    t_addr *addr;

    addr = NULL;
    monitor = ft_calloc(&addr, 1, sizeof(t_monitor));
    if (!monitor)
        return FAILURE;
    if (parse_args(monitor, av, ac))
        return print_exit("Too many or insufficient parameters", &addr);
    if (monitor->time_to_die < 60000 || monitor->time_to_eat < 60000 
            || monitor->time_to_sleep < 60000)
        return print_exit("Use timestamps major than 60", &addr);
    if (ft_init(monitor, &addr))
        return print_exit("Failed to initialize forks", &addr);
    if (create_philosophers(monitor, &addr))
        return print_exit("Failed to create philosopher threads", &addr);
    i = 0;
    while(i < monitor->number_of_philos)
        print_philosopher(&monitor->philos[i++]);
    // create thread for monitor
    monitor->is_ready_flag = 1;
    // start simulation ..........
    i = 0;
    while (i < monitor->number_of_philos)
        pthread_join(monitor->philos[i++].thread, NULL);
    i = 0;
    while (i < monitor->number_of_philos)
        pthread_mutex_destroy(&monitor->forks[i++]);
    return ft_lstclear(&addr, free), SUCCESS;
}

// int main(int ac, char **av)
// {
//     t_monitor *monitor;

//     // maybe work with garbage collector;
//     monitor = malloc(sizeof(t_monitor));
//     if ((ac == 5 || ac == 6) && !parse_args(monitor, av, ac))
//     {
//         if (monitor->time_to_die < 60000 || monitor->time_to_eat < 60000 
//             || monitor->time_to_sleep < 60000)
//             return printf("Use timestamps major than 60\n"), FAILURE;
//         print_params(monitor);
//         // philos_simulation(&monitor);
//         // clean(&monitor);
//         return SUCCESS;
//     }
//     return printf("too many or Insufficient parameters\n"), FAILURE;
// }

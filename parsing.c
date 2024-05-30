/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:42:11 by olamrabt          #+#    #+#             */
/*   Updated: 2024/05/29 20:16:36 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_flow(int sign, long long num, char c)
{
	if (num > (INT_MAX - (c - '0')) / 10)
	{
		if (sign == -1 && -(num * 10 + c - 48) == INT_MIN)
			return (0);
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	if (!str || !*str)
		return (-1);
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
	{
		if (ft_check_flow(sign, num, *str))
			return (-1);
		num = num * 10 + *str - 48;
		str++;
	}
	if (*str) // or maybe i wont need it 
		return -1;
	return ((int)(num * sign));
}

int parse_args(t_monitor *monitor, char **av, int ac)
{
    int temp;

    temp = -3;
    monitor->eat_limit = -1;
    if (ac == 6)
    {
        monitor->eat_limit = ft_atoi(av[5]);
        if (monitor->eat_limit < 0)
            return printf("%s is not a valid parameter\n", av[5]), FAILURE;
    }
    while (--ac > 0)
    {
        temp = ft_atoi(av[ac]);
        if (temp < 0)
            return printf("%s is not a valid parameter\n", av[ac]), FAILURE;
    }
    monitor->number_of_philos = ft_atoi(av[1]);
    monitor->full_philos = -1 * ft_atoi(av[1]);
    monitor->time_to_die = ft_atoi(av[2]) * 1000;
    monitor->time_to_eat = ft_atoi(av[3]) * 1000;
    monitor->time_to_sleep = ft_atoi(av[4]) * 1000;
    monitor->end_simulation = 0;
    monitor->start_time = 0; //gettimeofday
    return SUCCESS;
}

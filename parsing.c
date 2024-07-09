/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:42:11 by olamrabt          #+#    #+#             */
/*   Updated: 2024/07/08 16:45:41 by olamrabt         ###   ########.fr       */
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
	if (*str)
		return -1;
	return ((int)(num * sign));
}

int parse_args(t_dinner *dinner, char **av, int ac)
{
    int temp;

    temp = -3;
	dinner->eat_limit = -1;
	if (ac == 6)
    {
		dinner->eat_limit = ft_atoi(av[5]);
		if (dinner->eat_limit < 0)
			return printf("%s is not a valid parameter\n", av[5]), FAILURE;
    }
    while (--ac > 0)
    {
        temp = ft_atoi(av[ac]);
        if (temp < 0)
            return printf("%s is not a valid parameter\n", av[ac]), FAILURE;
    }
	dinner->number_of_philos = ft_atoi(av[1]);
	dinner->time_to_die = ft_atoi(av[2]);
	dinner->time_to_eat = ft_atoi(av[3]);
	dinner->time_to_sleep = ft_atoi(av[4]);
	dinner->start_time = 0;
	return SUCCESS;
}

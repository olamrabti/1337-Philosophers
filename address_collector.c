/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:11:24 by olamrabt          #+#    #+#             */
/*   Updated: 2024/07/13 15:12:49 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_exit(char *msg, t_addr **addr)
{
	if (msg)
		printf("%s\n", msg);
	ft_lstclear(addr, free);
	return (1);
}

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*temp;
	unsigned int	i;

	temp = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		temp[i] = 0;
		i++;
	}
}

void	*ft_calloc(t_addr **addr, size_t count, size_t size)
{
	char	*copy;

	if (count != 0 && size > 9223372036854775807ULL / count)
		return (NULL);
	copy = (char *)malloc(count * size);
	if (!copy)
		return (NULL);
	ft_bzero(copy, size * count);
	if (add_addr(addr, new_addr(copy)))
		return (NULL);
	return (copy);
}

t_addr	*new_addr(char *value)
{
	t_addr	*node;

	node = malloc(sizeof(t_addr));
	if (!node)
		return (NULL);
	node->nxt = NULL;
	node->address = value;
	return (node);
}

int	add_addr(t_addr **list, t_addr *new)
{
	t_addr	*temp;

	if (!list || !new)
		return (1);
	new->nxt = NULL;
	if (!*list)
	{
		*list = new;
		return (0);
	}
	temp = *list;
	while (temp->nxt != NULL)
		temp = temp->nxt;
	temp->nxt = new;
	return (0);
}

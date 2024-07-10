# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 13:28:42 by olamrabt          #+#    #+#              #
#    Updated: 2024/07/10 16:04:01 by olamrabt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread
NAME = philo

SRCS = philo.c parsing.c simulation.c address_collector.c address_collector_utils.c utils.c getters_setters.c

OBJS = $(SRCS:.c=.o)

all:
	@$(MAKE) $(NAME)

$(NAME) : $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -pthread -o $(NAME) 

%.o: %.c philo.h 
	$(CC) $(CFLAGS)  -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 13:28:42 by olamrabt          #+#    #+#              #
#    Updated: 2024/05/29 15:17:20 by olamrabt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

NAME = philosophers

SRCS = philo.c parsing.c

OBJS = $(SRCS:.c=.o)

all:
	@$(MAKE) $(NAME)

$(NAME) : $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME) 

%.o: %.c philo.h 
	$(CC) $(CFLAGS)  -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

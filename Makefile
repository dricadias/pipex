# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/20 21:35:33 by adias-do          #+#    #+#              #
#    Updated: 2025/04/20 21:40:17 by adias-do         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFTDIR = libft
RM = rm -rf

SRCS = scrs/pipex.c

OBJS = $(SRCS:.c=.o)

INCLUDE = -L ./libft -lft

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	@make -s -C $(LIBFTDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDE)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	@make -s -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	@make -s -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
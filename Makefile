# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/29 22:59:42 by kojwatan          #+#    #+#              #
#    Updated: 2024/04/02 17:49:07 by kojwatan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wextra -Werror -Wall -g -fsanitize=address
SRCS = srcs/main.c srcs/lexer.c srcs/tokenize.c srcs/token_type.c srcs/sort_token.c srcs/quotation_validate.c srcs/debug.c srcs/free.c

OBJS = $(SRCS:.c=.o)
READ_LINE_PREFIX = $(shell brew --prefix readline)
NAME = minishell
HEAD = ../includes/minishell.h
LIBFT = ./libft

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -I $(HEAD) -L$(READ_LINE_PREFIX)/lib -lreadline -I$(READ_LINE_PREFIX)/include -L$(LIBFT) -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I $(HEAD) -I$(READ_LINE_PREFIX)/include -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean $(NAME)

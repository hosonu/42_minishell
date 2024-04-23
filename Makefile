# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/29 22:59:42 by kojwatan          #+#    #+#              #
#    Updated: 2024/04/23 08:16:12 by kojwatan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wextra -g -fsanitize=address
# -Werror -Wall

SRCS =	srcs/main.c \
		srcs/prompt_handle/tokenize.c \
		srcs/prompt_handle/token_type.c \
		srcs/prompt_handle/sort_token.c \
		srcs/prompt_handle/token_join.c \
		srcs/prompt_handle/token_split1.c \
		srcs/prompt_handle/token_split2.c \
		srcs/prompt_handle/prompt_validate.c \
		srcs/prompt_handle/metachar_validate.c \
		srcs/prompt_handle/string_utils.c \
		srcs/prompt_handle/prompt_handle.c \
		srcs/prompt_handle/free.c \
		srcs/dispatch_token_v2.c \
		srcs/execve_token.c \
		srcs/fcntl_token.c \
		srcs/manage_fd.c \
		srcs/expand_variable.c \
		srcs/handle_token.c \
		srcs/x_funcs.c \
		srcs/x_funcs_second.c \
		srcs/error_msg.c \
		srcs/builtins/environ1.c \
		srcs/builtins/environ2.c \
		srcs/builtins/environ3.c \
		srcs/builtins/42_cd.c \
		srcs/builtins/42_echo.c \
		srcs/builtins/42_env.c \
		srcs/builtins/42_exit.c \
		srcs/builtins/42_export.c \
		srcs/builtins/42_pwd.c \
		srcs/builtins/42_unset.c \
		srcs/check_builtins.c

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

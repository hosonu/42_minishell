# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/29 22:59:42 by kojwatan          #+#    #+#              #
#    Updated: 2024/05/09 14:54:59 by hoyuki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wextra -Werror -Wall -g -fsanitize=address

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
		srcs/token_runner/dispatch_token.c \
		srcs/token_runner/dispatch_token_utils.c \
		srcs/token_runner/wait.c\
		srcs/token_runner/execve_token.c \
		srcs/token_runner/fcntl_token.c \
		srcs/token_runner/heredoc_init.c \
		srcs/token_runner/minish_split.c \
		srcs/token_runner/manage_fd.c \
		srcs/token_runner/expand_variable.c \
		srcs/token_runner/handle_token.c \
		srcs/token_runner/check_builtins.c \
		srcs/x_funcs/error_msg.c \
		srcs/x_funcs/x_funcs.c \
		srcs/x_funcs/x_funcs_second.c \
		srcs/x_funcs/x_funcs_third.c \
		srcs/builtins/environ1.c \
		srcs/builtins/environ2.c \
		srcs/builtins/environ3.c \
		srcs/builtins/env_split.c \
		srcs/builtins/42_cd1.c \
		srcs/builtins/42_cd2.c \
		srcs/builtins/42_echo.c \
		srcs/builtins/42_env.c \
		srcs/builtins/42_exit.c \
		srcs/builtins/42_export1.c \
		srcs/builtins/42_export2.c \
		srcs/builtins/42_pwd.c \
		srcs/builtins/42_unset.c 

OBJS = $(SRCS:.c=.o)
READ_LINE_PREFIX = $(shell brew --prefix readline)
NAME = minishell
HEAD = ../includes/minishell.h
LIBFT = ./libft

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -I $(HEAD) -L$(READ_LINE_PREFIX)/lib -lreadline -lhistory -I$(READ_LINE_PREFIX)/include -L$(LIBFT) -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I $(HEAD) -I$(READ_LINE_PREFIX)/include -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean $(NAME)

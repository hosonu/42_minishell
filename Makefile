# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/29 22:59:42 by kojwatan          #+#    #+#              #
#    Updated: 2024/04/16 15:54:19 by kojwatan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED=\033[0;31m
GREEN=\033[0;32m
BLUE=\033[0;34m
NC=\033[0m

CC = cc
CFLAGS =  -Wextra 
# -Wall  -Wextra -Werror

# -g -fsanitize=address
SRCS =	srcs/main.c \
		srcs/tokenize.c \
		srcs/token_type.c \
		srcs/sort_token.c \
		srcs/token_split.c \
		srcs/prompt_validate.c \
		srcs/string_utils.c \
		srcs/debug.c srcs/free.c \
		srcs/token_runner/dispatch_token.c \
		srcs/token_runner/dispatch_token_utils.c \
		srcs/token_runner/wait.c\
		srcs/token_runner/execve_token.c \
		srcs/token_runner/fcntl_token.c \
		srcs/token_runner/manage_fd.c \
		srcs/token_runner/expand_variable.c \
		srcs/token_runner/handle_token.c \
		srcs/token_runner/check_builtins.c \
		srcs/token_runner/heredoc_init.c \
		srcs/x_funcs/error_msg.c \
		srcs/x_funcs/x_funcs.c \
		srcs/x_funcs/x_funcs_second.c \
		srcs/x_funcs/x_funcs_third.c \
		srcs/environ_init.c \
		srcs/builtins/42_cd.c \
		srcs/builtins/42_echo.c \
		srcs/builtins/42_env.c \
		srcs/builtins/42_exit.c \
		srcs/builtins/42_export.c \
		srcs/builtins/42_pwd.c \
		srcs/builtins/42_unset.c 

OBJS = $(SRCS:.c=.o)
# READ_LINE_PREFIX = $(shell brew --prefix readline)
READ_LINE_PREFIX = /usr/local/opt/readline
NAME = minishell
HEAD = ../includes/minishell.h
LIBFT = ./libft

all: progress compile_success

progress: $(NAME)
	@bash progress_bar.sh

compile_success:
	@echo "\n${GREEN}✨ Compilation successful! ✨${NC}"
	@echo "${BLUE}🎉 $(NAME) created! 🎉${NC}"

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT) >/dev/null 2>&1
	@$(CC) $(CFLAGS) $(OBJS) -I $(HEAD) -L$(READ_LINE_PREFIX)/lib -lreadline -I$(READ_LINE_PREFIX)/include -L$(LIBFT) -lft -o $(NAME) >/dev/null 2>&1

%.o: %.c
	@$(CC) $(CFLAGS) -I $(HEAD) -I$(READ_LINE_PREFIX)/include -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT) clean >/dev/null 2>&1
	@rm -f $(OBJS)
	@echo "${YELLOW}💨 Object files removed 💨${NC}"

fclean: clean
	@$(MAKE) -C $(LIBFT) fclean >/dev/null 2>&1
	@rm -f $(NAME)
	@echo "${RED}🗑  $(NAME) removed 🗑${NC}"

re: fclean progress
	@$(MAKE) all
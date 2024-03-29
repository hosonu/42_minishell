CC = cc
CFLAGS = -Wextra -Werror -Wall -g -fsanitize=address
SRCS = src/main.c src/lexer.c src/tokenize.c src/token_type.c src/sort_token.c src/quotation_validate.c

OBJS = $(SRCS:.c=.o)
READ_LINE_PREFIX = $(shell brew --prefix readline)
NAME = minishell
LIBFT = ./libft

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(READ_LINE_PREFIX)/lib -lreadline -I$(READ_LINE_PREFIX)/include -L$(LIBFT) -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(READ_LINE_PREFIX)/include -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean $(NAME)

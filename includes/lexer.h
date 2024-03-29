#ifndef LEXER_H
# define LEXER_H

#include "./minishell.h"

t_token	*new_token(char *content);
t_token	*lexer(char *str);
void	token_addlast(t_token *top, t_token *new);
void	token_insert(t_token *node, t_token *new);
void	token_destroy(t_token *node);

#endif

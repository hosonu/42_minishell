#ifndef DEBUG_H
# define DEBUG_H

#include "./minishell.h"

void	print_linear_tokens(t_token **top);
void	print_chain_tokens(t_token *top);
void	print_quote(t_quotes *list);

#endif

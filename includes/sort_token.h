#ifndef SORT_TOKEN_H
# define SORT_TOKEN_H

#include "./minishell.h"

void	print_to(t_token **top);
t_token	**linear_token_list(t_token *top);
void	sort_token(t_token **list);

#endif

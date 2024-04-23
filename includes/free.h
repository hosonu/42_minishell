#ifndef FREE_H
# define FREE_H

#include "./minishell.h"

void	free_linear_token_list(t_token **list);
void	free_chain_token_list(t_token *top);
void	free_env(t_env *env);

#endif

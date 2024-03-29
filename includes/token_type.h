#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

#include "./minishell.h"

t_token	*devide_file(t_token *node);
t_token	*devide_cmd(t_token *node);
void	token_revise(t_token *top);
void	token_type_revise(t_token **list);
void	decide_type_util(t_token *token, int meta_type, int type);
int	decide_type(t_token *top);

#endif

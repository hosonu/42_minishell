#include "../includes/minishell.h"

void	free_linear_token_list(t_token **list)
{
	int	i;

	i = 0;
	while (list[i] != NULL)
	{
		free(list[i]->token);
		free(list[i]);
		i++;
	}
}

void	free_chain_token_list(t_token *top)
{
	t_token	*tmp;

	while (top != NULL)
	{
		tmp = top;
		free(top->token);
		top = top->next;
		free(tmp);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:31:26 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/24 01:06:11 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	free(list);
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

void	free_env(t_env *env)
{
	t_env	*tmp;

	env = env->next;
	while (env != NULL)
	{
		tmp = env;
		env = env->next;
		destroy_env(tmp);
	}
	free(env);
}

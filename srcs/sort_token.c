/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:00:30 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/02 15:05:01 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	token_count(t_token *top)
{
	int	count;

	count = 0;
	while (top != NULL)
	{
		count++;
		top = top->next;
	}
	return (count);
}

t_token	**linear_token_list(t_token *top)
{
	t_token	**list;
	int	i;

	list = malloc(sizeof(t_token *) * (token_count(top) + 1));
	i = 0;
	while (top != NULL)
	{
		list[i] = top;
		i++;
		top = top->next;
	}
	list[i] = NULL;
	return (list);
}

void	sort_token(t_token **list)
{
	int	i;
	t_token	*tmp;

	i = 0;
	while (list[i] != NULL)
	{
		if (list[i + 1] != NULL)
		{
			if (list[i]->type >= COMMAND && list[i + 1]->type < COMMAND && list[i + 1]->type != METAPIPE)
			{
				tmp = list[i];
				list[i] = list[i + 1];
				list[i + 1] = tmp;
			}
		}
		i++;
	}
}

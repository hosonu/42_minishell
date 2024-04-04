/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:00:30 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/04 02:08:58 by kojwatan         ###   ########.fr       */
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

void	sort_token(t_token **top)
{
	t_token	*node;
	t_token	*tmp_now;
	t_token	*tmp_next;

	if (!top || !*top)
		return;
	node = *top;
	while (node != NULL && node->next != NULL)
	{
		if (node->type >= COMMAND && node->next->type < COMMAND && node->next->type != METAPIPE)
		{
			tmp_now = node;
			tmp_next = node->next;
			tmp_now->next = tmp_next->next;
			if (tmp_next->next != NULL)
				tmp_next->next->prev = tmp_now;
			tmp_next->next = tmp_now;
			tmp_next->prev = tmp_now->prev;
			if (tmp_now->prev != NULL)
				tmp_now->prev->next = tmp_next;
			else
				*top = tmp_next;
			tmp_now->prev = tmp_next;
			node = *top;
			continue;
		}
		node = node->next;
	}
}
/*
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
*/

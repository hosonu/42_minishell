/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:00:30 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/18 23:34:19 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	token_swap(t_token **top, t_token *node)
{
	t_token	*tmp_now;
	t_token	*tmp_next;

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
}

void	sort_token(t_token **top)
{
	t_token	*node;

	if (!top || !*top)
		return ;
	node = *top;
	while (node != NULL && node->next != NULL)
	{
		if (node->type >= COMMAND && node->next->type < COMMAND
			&& node->next->type != METAPIPE)
		{
			token_swap(top, node);
			node = *top;
			continue ;
		}
		node = node->next;
	}
}

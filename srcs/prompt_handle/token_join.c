/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:31:48 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/18 22:57:54 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*token_join_util(t_token *node)
{
	char	*tmp;
	char	*new_token;

	new_token = ft_strjoin(node->token, " ");
	if (new_token == NULL)
		return (NULL);
	tmp = new_token;
	new_token = ft_strjoin(new_token, node->next->token);
	free(tmp);
	if (new_token == NULL)
		return (NULL);
	free(node->token);
	node->token = new_token;
	token_destroy(node->next);
	return (node);
}

t_token	*token_join(t_token *top)
{
	t_token	*node;
	t_token	*ret;

	node = top;
	while (node != NULL)
	{
		if (node->type >= COMMAND && node->next != NULL)
		{
			while (node->next != NULL && node->next->type == COMMAND)
			{
				ret = token_join_util(node);
				if (ret == NULL)
					return (NULL);
			}
		}
		node = node->next;
	}
	return (top);
}

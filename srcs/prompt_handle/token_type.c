/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:00:37 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/24 01:25:44 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	decide_type_util(t_token *token, int8_t meta_type, int8_t type)
{
	token->type = meta_type;
	if (token->next != NULL)
		token->next->type = type;
}

void	decide_type(t_token *top)
{
	int		len;
	t_token	*node;

	node = top;
	while (node != NULL)
	{
		len = ft_strlen(node->token);
		if (ft_strnstr(node->token, ">>", len) == node->token)
			decide_type_util(node, METAAPNDOUT, APNDOUTFILE);
		else if (ft_strnstr(node->token, ">", len) == node->token)
			decide_type_util(node, METAOUT, TRUNCOUTFILE);
		else if (ft_strnstr(node->token, "<<", len) == node->token)
			decide_type_util(node, METAHEREDOC, HEREDOC);
		else if (ft_strnstr(node->token, "<", len) == node->token)
			decide_type_util(node, METAIN, INFILE);
		else if (ft_strnstr(node->token, "|", len) == node->token)
			decide_type_util(node, METAPIPE, COMMAND);
		else if (node->type == 0)
			node->type = COMMAND;
		node = node->next;
	}
}

static void	tt_revise_util(t_token **list, uint8_t *ppfg, int8_t *type)
{
	if (*type == (METAIN * -1 | METAHEREDOC * -1))
		list[0]->type = HEREDOCCOMMAND;
	else if (*type == (METAOUT * -1 | METAIN * -1 | METAHEREDOC * -1))
		list[0]->type = REOUTHEREDOCCOMMAND;
	else
		list[0]->type = list[0]->type + *type;
	*type = 0;
	list[0]->pipein = *ppfg;
	*ppfg = false;
	if (list[1] != NULL)
	{
		if (list[1]->type == METAPIPE)
			list[0]->pipeout = true;
	}
}

void	token_type_revise(t_token **list)
{
	int		i;
	uint8_t	pipefg;
	int8_t	token_type;

	i = 0;
	token_type = 0;
	pipefg = 0;
	while (list[i] != NULL)
	{
		if (list[i]->type < 0 && list[i]->type != METAPIPE)
			token_type = token_type | (list[i]->type * -1);
		else if (list[i]->type >= 30)
			tt_revise_util(&list[i], &pipefg, &token_type);
		else if (list[i]->type == METAPIPE)
		{
			token_type = 0;
			pipefg = true;
		}
		i++;
	}
}

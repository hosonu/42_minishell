/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:00:13 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/16 15:34:01 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*new_token(char *content)
{
	t_token	*new;

	if (content == NULL)
		return (NULL);
	new = malloc(sizeof(t_token));
	new->token = ft_strdup(content);
	new->type = 0;
	new->pipein = false;
	new->pipeout = false;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*lexer(char *str)
{
	char	**splited_token;
	int	i;
	t_token	*top;
	t_token	*new;

	i = 0;
	top = NULL;
	splited_token = token_split(str, ' ');
	while (splited_token[i] != NULL)
	{
		new = new_token(splited_token[i]);
		if (top == NULL)
			top = new;
		else
			token_addlast(top, new);
		i++;
	}
	return (top);
}

void	token_addlast(t_token *top, t_token *new)
{
	t_token	*lst;

	lst = top;
	while (lst->next != NULL)
		lst = lst->next;
	lst->next = new;
	new->prev = lst;
}

void	token_insert(t_token *node, t_token *new)
{
	new->next = node->next;
	node->next = new;
	new->prev = node;
}

void	token_destroy(t_token *node)
{
	if (node->next != NULL)
		node->next->prev = node->prev;
	if (node->prev != NULL)
		node->prev->next = node->next;
	free(node->token);
	free(node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:00:13 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/04 02:28:49 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*new_token(char *content)
{
	t_token	*new;

	if (content == NULL)
		return (NULL);
	new = malloc(sizeof(t_token));
	new->token = content;
	new->type = 0;
	new->pipein = false;
	new->pipeout = false;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*new_metatoken(char *str)
{
	int	start;
	int	len;
	t_token	*new;

	start = token_len(str);
	len = 0;
	if (start == (int)ft_strlen(str))
		return (NULL);
	while (str[start] == ' ')
		start++;
	while (is_metachar(str[start + len]) == 1)
		len++;
	new = new_token(ft_substr(str, start, len));
	return (new);
}

t_token	*lexer(char *str)
{
	char	*left;
	t_token	*top;
	t_token	*new;


	new = NULL;
	top = new_token(tokenizer(str));
	if (top == NULL)
		top = new_metatoken(str);
	else
		new = new_metatoken(str);
	if (new != NULL)
		token_addlast(top, new);
	left = strdup_right(str);
	while (left != NULL)
	{
		new = new_token(tokenizer(left));
		if (new != NULL)
			token_addlast(top, new);
		new = new_metatoken(left);
		if (new != NULL)
			token_addlast(top, new);
		left = strdup_right(left);
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

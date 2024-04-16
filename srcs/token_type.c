/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:00:37 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/16 16:13:11 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	decide_type_util(t_token *token, int8_t meta_type, int8_t type)
{
	token->type = meta_type;
	token->next->type = type;
}

void	decide_type(t_token *top)
{
	int	len;
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

t_token	*devide_file(t_token *node)
{
	int	len;
	int	start;
	char	*token;
	t_token	*new;

	len = 0;
	start = 0;
	while (node->token[start] == ' ')
		start++;
	while (node->token[start + len] != '\0')
	{
		if (node->token[start + len] == ' ' && is_quoted(node->token, &node->token[start + len]) == -1)
			break ;
		else
			len++;
	}
	token = ft_substr(node->token, start, len);
	new = new_token(token);
	if (new != NULL)
		new->type = node->type;
	return (new);
}

t_token	*devide_cmd(t_token *node)
{
	int	len;
	int	start;
	char	*token;
	t_token	*new;

	len = 0;
	start = 0;
	while (node->token[start] == ' ')
		start++;
	while (node->token[start] != ' ' || is_quoted(node->token, &node->token[start]) == 1)
		start++;
	while (node->token[start] == ' ')
		start++;
	while (node->token[start + len] != '\0')
		len++;
	token = ft_substr(node->token, start, len);
	new = new_token(token);
	if (new != NULL) new->type = COMMAND;
	return (new);
}

void	token_revise(t_token *top)
{
	t_token	*node;
	t_token	*file;
	t_token	*cmd;
	char	*tmp;
	char	*tmp_token;

	node = top;
	while (node != NULL)
	{
		if (node->type < COMMAND && is_more_than_word(node->token) == 1)
		{
			file = devide_file(node);
			cmd = devide_cmd(node);
			token_insert(node, file);
			token_insert(file, cmd);
			token_destroy(node);
			node = cmd;
		}
		else if (node->type >= COMMAND && node->next != NULL)
		{
			while (node->next != NULL && node->next->type == COMMAND)
			{
				tmp = node->token;
				tmp_token = ft_strjoin(node->token, " ");
				node->token = ft_strjoin(tmp_token, node->next->token);
				free(tmp);
				free(tmp_token);
				token_destroy(node->next);
			}
		}
		node = node->next;
	}
}

void	token_type_revise(t_token **list)
{
	int	i;
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
		{
			if (token_type == (METAIN * -1 | METAHEREDOC * -1))
				list[i]->type = HEREDOCCOMMAND;
			else if (token_type == (METAOUT * -1 | METAIN * -1 | METAHEREDOC * -1))
				list[i]->type = REOUTHEREDOCCOMMAND;
			else
				list[i]->type = list[i]->type + token_type;
			token_type = 0;
			list[i]->pipein = pipefg;
			pipefg = false;
			if (list[i + 1] != NULL)
			{
				if (list[i + 1]->type == METAPIPE)
					list[i]->pipeout = true;
			}
		}
		else if (list[i]->type == METAPIPE)
		{
			token_type = 0;
			pipefg = true;
		}
		i++;
	}
}

t_token	**token_list(t_token *tokens)
{
	t_token	**list;

	decide_type(tokens);
	token_revise(tokens);
	sort_token(&tokens);
	token_revise(tokens);
	list = linear_token_list(tokens);
	token_type_revise(list);
	return (list);
}

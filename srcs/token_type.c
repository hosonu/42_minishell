/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:00:37 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/03 02:42:47 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	decide_type_util(t_token *token, int8_t meta_type, int8_t type)
{
	token->type = meta_type;
	if (token->next == NULL)
	{
		ft_printf("syntaxerror\n");
		return (-1);
	}
	else
		token->next->type = type;
	return (1);
}

int	decide_type(t_token *top)
{
	int	len;
	int	ret;
	t_token	*node;

	node = top;
	ret = 0;
	while (node != NULL)
	{
		len = ft_strlen(node->token);
		if (ft_strnstr(node->token, ">>", len) == node->token)
			ret = decide_type_util(node, METAAPNDOUT, APNDOUTFILE);
		else if (ft_strnstr(node->token, ">", len) == node->token)
			ret = decide_type_util(node, METAOUT, TRUNCOUTFILE);
		else if (ft_strnstr(node->token, "<<", len) == node->token)
			ret = decide_type_util(node, METAHEREDOC, HEREDOC);
		else if (ft_strnstr(node->token, "<", len) == node->token)
			ret = decide_type_util(node, METAIN, INFILE);
		else if (ft_strnstr(node->token, "|", len) == node->token)
			ret = decide_type_util(node, METAPIPE, COMMAND);
		else if (node->type == 0)
			node->type = COMMAND;
		if (ret < 0)
			return (-1);
		node = node->next;
	}
	return (1);
}

int	more_than_word(char *str)
{
	char	*pnt[5];

	pnt[0] = strchr(str, '\"');
	if (pnt[0] != NULL)
		pnt[1] = strchr(pnt[0] + 1, '\"');
	pnt[2] = strchr(str, '\'');
	if (pnt[2] != NULL)
		pnt[3] = strchr(pnt[2] + 1, '\'');
	if (pnt[0] != NULL || pnt[2] != NULL)
	{
		if (pnt[0] != NULL && pnt[2] == NULL)
			pnt[4] = strchr(pnt[1], ' ');
		else if (pnt[0] == NULL && pnt[2] != NULL)
			pnt[4] = strchr(pnt[3], ' ');
		else if (pnt[0] < pnt[2])
			pnt[4] = strchr(pnt[1], ' ');
		else
			pnt[4] = strchr(pnt[3], ' ');
	}
	else
		pnt[4] = strchr(str, ' ');
	return (pnt[4] != NULL);
}

t_token	*devide_file(t_token *node)
{
	int	len;
	int	start;
	char	*token;
	char	*pnt[5];
	t_token	*new;

	len = 0;
	start = 0;
	pnt[0] = strchr(node->token, '\"');
	if (pnt[0] != NULL)
		pnt[1] = strchr(node->token + 1, '\"');
	pnt[2] = strchr(node->token, '\'');
	if (pnt[2] != NULL)
		pnt[3] = strchr(node->token + 1, '\'');
	pnt[4] = strchr(node->token, ' ');
	while (node->token[start] == ' ')
		start++;
	if (pnt[0] == NULL && pnt[2] == NULL)
	{
		while (node->token[start + len] != ' ')
			len++;
	}
	else if (pnt[0] < pnt[4] || pnt[2] < pnt[4])
	{
		if (pnt[0] != NULL && pnt[2] == NULL)
			len = (pnt[1] - pnt[0]) + 1;
		else if (pnt[0] == NULL && pnt[2] != NULL)
			len = (pnt[3] - pnt[2]) + 1;
		else if (pnt[0] < pnt[2])
			len = (pnt[1] - pnt[0]) + 1;
		else
			len = (pnt[3] - pnt[2]) + 1;
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
	char	*pnt[5];
	t_token	*new;

	len = 0;
	start = 0;
	pnt[0] = strchr(node->token, '\"');
	if (pnt[0] != NULL)
		pnt[1] = strchr(pnt[0] + 1, '\"');
	pnt[2] = strchr(node->token, '\'');
	if (pnt[2] != NULL)
		pnt[3] = strchr(pnt[2] + 1, '\'');
	pnt[4] = NULL;
	if (pnt[0] != NULL || pnt[2] != NULL)
	{
		if (pnt[0] != NULL && pnt[2] == NULL)
			pnt[4] = strchr(pnt[1], ' ');
		else if (pnt[0] == NULL && pnt[2] != NULL)
			pnt[4] = strchr(pnt[3], ' ');
		else if (pnt[0] < pnt[2])
			pnt[4] = strchr(pnt[1], ' ');
		else
			pnt[4] = strchr(pnt[3], ' ');
		start = (pnt[4] - node->token) + 1;
		while (node->token[start] == ' ')
			start++;
	}
	else
	{
		while (node->token[start] == ' ')
			start++;
		while (node->token[start] != ' ')
			start++;
		while (node->token[start] == ' ')
			start++;
	}
	while (node->token[start + len] != '\0')
		len++;
	token = ft_substr(node->token, start, len);
	new = new_token(token);
	if (new != NULL)
		new->type = COMMAND;
	return (new);
}

void	token_revise(t_token *top)
{
	t_token	*node;
	t_token	*file;
	t_token	*cmd;

	node = top;
	while (node != NULL)
	{
		if (node->type < COMMAND && more_than_word(node->token) == 1)
		{
			//devide command and filename
			file = devide_file(node);
			cmd = devide_cmd(node);
			//printf("DEBUG check: file %s\tcmd %s\n", file->token, cmd->token);
			//insert func and destory origin
			token_insert(node, file);
			token_insert(file, cmd);
			token_destroy(node);
			node = cmd;
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
		{
			token_type = token_type | (list[i]->type * -1);
			//printf("DEBUG token_type_revise: %d\n", token_type);
		}
		else if (list[i]->type >= 30)
		{
			//printf("DEBUG token_type_revise: %d\n", list[i]->type);
			if (token_type == (METAIN * -1 | METAHEREDOC * -1))
				list[i]->type = HEREDOCCOMMAND;
			else if (token_type == (METAOUT * -1 | METAIN * -1 | METAHEREDOC * -1))
				list[i]->type = REOUTHEREDOCCOMMAND;
			else
				list[i]->type = list[i]->type + token_type;
			token_type = 0;
			list[i]->pipein = pipefg;
			pipefg = 0;
			if (list[i + 1] != NULL)
			{
				if (list[i + 1]->type == METAPIPE)
					list[i]->pipeout = 1;
			}
		}
		else if (list[i]->type == METAPIPE)
		{
			token_type = 0;
			pipefg = 1;
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:00:37 by kojwatan          #+#    #+#             */
/*   Updated: 2024/03/29 23:00:38 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	decide_type_util(t_token *token, int meta_type, int type)
{
	token->type = meta_type;
	if (token->next == NULL)
	{
		perror("syntaxerror");
		exit(EXIT_FAILURE);
	}
	else
		token->next->type = type;
}

int	decide_type(t_token *top)
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
			decide_type_util(node, METAOUT, OWOUTFILE);
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
	int	token_type;

	i = 0;
	token_type = 0;
	while (list[i] != NULL)
	{
		if (list[i]->type < 0)
		{
			token_type = token_type | (list[i]->type * -1);
			//printf("DEBUG token_type_revise: %d\n", token_type);
		}
		else if (list[i]->type >= 30)
		{
			//printf("DEBUG token_type_revise: %d\n", list[i]->type);
			list[i]->type = list[i]->type + token_type;
			token_type = 0;
			if (list[i + 1] != NULL)
			{
				if (list[i + 1]->type == METAPIPE)
				{
					switch (list[i]->type)
					{
						case COMMAND:
							list[i]->type = PIPEOUTCOMMAND;
							printf("DEBUG: a\n");
							break ;
						case HEREDOCCOMMAND:
							list[i]->type = PIPEOUTHEREDOCCOMMAND;
							break ;
						case REINHEREDOCCOMMAND:
							list[i]->type = REINPIPEOUTCOMMAND;
							break ;
						case REOUTHEREDOCCOMMAND:
							list[i]->type = REOUTPIPEOUTHEREDOCCOMMAND;
							break ;
						case REINOUTHEREDOCCOMMAND:
							list[i]->type = REINOUTPIPEOUTCOMMAND;
							break ;
						case PIPEINHEREDOCCOMMAND:
							list[i]->type = PIPEINOUTHEREDOCCOMMAND;
							break ;
						case REINOUTPIPEINHEREDOCCOMMAND:
							list[i]->type = REINOUTPIPEINOUTHEREDOCCOMMAND;
							break ;
						case REINCOMMAND:
							list[i]->type = REINPIPEOUTCOMMAND;
							break ;
						case REINOUTCOMMAND:
							list[i]->type = REINOUTPIPEOUTCOMMAND;
							break ;
						case REINOUTPIPEINCOMMAND:
							list[i]->type = REINOUTPIPEINOUTCOMMAND;
							break ;
						case REOUTPIPEINCOMMAND:
							list[i]->type = REOUTPIPEINOUTCOMMAND;
							break ;
						case PIPEINCOMMAND:
							list[i]->type = PIPEINOUTCOMMAND;
							break ;
						case INFILE:
							list[i]->type = INFILETOPIPE;
							break ;
					}
				}
			}
		}
		i++;
	}
}

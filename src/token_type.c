#include "../minishell.h"

void	decide_type_util(t_token *token, int meta_type, int type)
{
	token->type = meta_type;
	if (token->next == NULL)
		perror("syntaxerror");
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
			decide_type_util(node, METAPIPE, PIPEINCOMMAND);
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

void	check(t_token *top)
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
			printf("DEBUG: file %s\tcmd %s\n", file->token, cmd->token);
			//insert func and destory origin
			token_insert(node, file);
			token_insert(file, cmd);
			token_destroy(node);
			node = cmd;
		}
		node = node->next;
	}
}

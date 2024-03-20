#include "../minishell.h"

void	decide_type_util(t_token *token, int type)
{
	token->type = METACHAR;
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
		if (ft_strnstr(node->token, ">>", len))
			decide_type_util(node, APNDOUTFILE);
		else if (ft_strnstr(node->token, ">", len))
			decide_type_util(node, OWOUTFILE);
		else if (ft_strnstr(node->token, "<<", len))
			decide_type_util(node, HEREDOC);
		else if (ft_strnstr(node->token, "<", len))
			decide_type_util(node, INFILE);
		else if (ft_strnstr(node->token, "|", len))
			decide_type_util(node, PIPECOMMAND);
		else if (node->type == 0)
			node->type = COMMAND;
		node = node->next;
	}
	return (1);
}

int	count_word(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		count++;
		while (str[i] != ' ' && str[i] != '\0')
			i++;
		while (str[i] == ' ' && str[i] != '\0')
			i++;
	}
	return (count);
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
	while (node->token[start + len] != ' ')
		len++;
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
	while (node->token[start] != ' ')
		start++;
	while (node->token[start] == ' ')
		start++;
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
		if (node->type != COMMAND && count_word(node->token) > 1)
		{
			//devide command and filename
			file = devide_file(node);
			cmd = devide_cmd(node);
			//insert func and destory origin
			token_insert(node, file);
			token_insert(file, cmd);
			token_destroy(node);
			node = cmd;
		}
		node = node->next;
	}
}

#include "../minishell.h"

int	token_len(char *src)
{
	int	srclen;
	int	token_len;
	int	len;
	char	*pnt[5];
	int	i;

	srclen = ft_strlen(src);
	token_len = srclen;
	pnt[0] = ft_strnstr(src, ">>", srclen);
	pnt[1] = ft_strnstr(src, ">", srclen);
	pnt[2] = ft_strnstr(src, "<<", srclen);
	pnt[3] = ft_strnstr(src, "<", srclen);
	pnt[4] = ft_strnstr(src, "|", srclen);
	i = 0;
	while (i < 5)
	{
		if (pnt[i] != NULL)
		{
			len = pnt[i] - src;
			if (len < token_len)
				token_len = len;
		}
		i++;
	}
	return (token_len);
}

char	*tokenizer(char *str)
{
	char	*token;
	int	len;

	len = 0;
	len = token_len(str);
	token = NULL;
	//case 1 token
	//case 2 metacharacter
	if (len > 0)
		token = ft_substr(str, 0, len);
/*	else if (len == 0)
	{
		if (str[0] == str[1])
			token = ft_substr(str, 0, 2);
		else
			token = ft_substr(str, 0 , 1);
	}
*/	return (token);
}

int	is_metachar(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (-1);
}

char	*strdup_right(char *str)
{
	int	len;

	len = token_len(str);
	if (len == (int)ft_strlen(str))
		return (NULL);
	while (is_metachar(str[len]) == 1)
		len++;
	return (ft_strdup(&str[len]));
}

int	decide_type(t_token *top)
{
	int	len;
	t_token	*node;

	node = top;
	while (node->next != NULL)
	{
		len = ft_strlen(node->token);
		if (ft_strnstr(node->token, ">>", len))
		{
			node->type = METACHAR;
			node->next->type = APNDOUTFILE;
		}
		else if (ft_strnstr(node->token, ">", len))
		{
			node->type = METACHAR;
			node->next->type = OWOUTFILE;
		}
		else if (ft_strnstr(node->token, "<<", len))
		{
			node->type = METACHAR;
			node->next->type = HEREDOC;
		}
		else if (ft_strnstr(node->token, "<", len))
		{
			node->type = METACHAR;
			node->next->type = INFILE;
		}
		else if (ft_strnstr(node->token, "|", len))
		{
			node->type = METACHAR;
			node->next->type = PIPECOMMAND;
		}
		else
			node->type = COMMAND;
		node = node->next;
	}
	return (1);
}

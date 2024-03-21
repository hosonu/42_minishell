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
	int	start;
	int	i;

	len = 0;
	len = token_len(str);
	token = NULL;
	start = 0;
	while (str[start] == ' ' && str[start] != '\0')
		start++;
	if (len > 0)
		token = ft_substr(str, start, len - start);
	i = 0;
	if (token != NULL)
	{
		while (token[i] == ' ')
			i++;
		if (i == len)
			return (NULL);
	}
	return (token);
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
	while (str[len] == ' ')
		len++;
	return (ft_strdup(&str[len]));
}

#include "../minishell.h"

int	token_len(char *src)
{
	int	srclen;
	int	token_len;
	int	len;
	char	*pnt[9];
	int	i;

	srclen = ft_strlen(src);
	pnt[0] = ft_strnstr(src, ">>", srclen);
	pnt[1] = ft_strnstr(src, ">", srclen);
	pnt[2] = ft_strnstr(src, "<<", srclen);
	pnt[3] = ft_strnstr(src, "<", srclen);
	pnt[4] = ft_strnstr(src, "|", srclen);
	pnt[5] = ft_strchr(src, '\"');
	if (pnt[5] != NULL)
		pnt[6] = ft_strchr(pnt[5] + 1, '\"');
	pnt[7] = ft_strchr(src, '\'');
	if (pnt[7] != NULL)
		pnt[8] = ft_strchr(pnt[7] + 1, '\'');
	token_len = srclen;
	i = 0;
	while (i < 5)
	{
		if (pnt[i] != NULL)
		{
			len = pnt[i] - src;
			if (len < token_len)
			{
				if (pnt[5] != NULL || pnt[7] != NULL)
				{
					if (pnt[7] == NULL && (pnt[5] < pnt[i] && pnt[6] > pnt[i]))
						token_len = (pnt[6] - src) + 1;
					else if (pnt[5] == NULL && (pnt[7] < pnt[i] && pnt[8] > pnt[i]))
						token_len = (pnt[8] - src) + 1;
					else
						token_len = len;
				}
				else
					token_len = len;
			}
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
	while (str[len] == ' ')
		len--;
	if (len > 0)
		token = ft_substr(str, start, len - start);
	i = 0;
	if (token != NULL)
	{
		while (token[i] == ' ')
			i++;
		if (token[i] == '\0')
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
	while (str[len] == ' ')
		len++;
	while (is_metachar(str[len]) == 1)
		len++;
	while (str[len] == ' ')
		len++;
	return (ft_strdup(&str[len]));
}

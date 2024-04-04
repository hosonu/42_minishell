/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:00:48 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/04 00:23:18 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	metachr_quote_revise(src, pnt);
	i = 0;
	while (i < 5)
	{
		if (pnt[i] != NULL)
		{
			len = pnt[i] - src;
			if (token_len > len)
				token_len = len;
		}
		i++;
	}
	return (token_len);
}

void	metachr_quote_revise(char *str, char *pnt[5])
{
	int	i;
	int	srclen;

	srclen = ft_strlen(str);
	//printf("DEBUG metachr_quote_revise:\n");
	i = 0;
	while (i < 5)
	{
		while (pnt[i] != NULL && is_quoted(str, pnt[i]) == 1)
		{
			switch (i)
			{
				case 0:
					pnt[0] = ft_strnstr(pnt[0] + 1, ">>", srclen);
					break ;
				case 1:
					pnt[1] = ft_strnstr(pnt[1] + 1, ">", srclen);
					break ;
				case 2:
					pnt[2] = ft_strnstr(pnt[2] + 1, "<<", srclen);
					break ;
				case 3:
					pnt[3] = ft_strnstr(pnt[3] + 1, "<", srclen);
					break ;
				case 4:
					pnt[4] = ft_strnstr(pnt[4] + 1, "|", srclen);
					break ;
			}
		}
		i++;
	}

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
	//printf("DEBUG tokenizer: len %d\n", len);
	while (str[start] == ' ' && str[start] != '\0')
		start++;
	while (len != 0 && (str[len] == ' ' || is_metachar(str[len]) == 1))
		len--;
	if (len > 0)
		token = ft_substr(str, start, (len - start) + 1);
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

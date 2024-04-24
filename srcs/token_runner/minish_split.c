/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-23 16:12:05 by user              #+#    #+#             */
/*   Updated: 2024-04-23 16:12:05 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	count_word(const char *s, char c)
{
	size_t	words;
	int		quoted;
	int		dblquoted;

	words = 1;
	quoted = 0;
	dblquoted = 0;
	while (*s)
	{
		if (*s == '"' && quoted % 2 == 0)
			dblquoted += 1;
		else if (*s == '\'' && dblquoted % 2 == 0)
			quoted += 1;
		else if ((dblquoted % 2 == 0 && quoted % 2 == 0) && *s == c)
			words++;
		s++;
	}
	return (words);
}

void	check_quoted(int *quoted, char c)
{
	if (c == '\'' && (*quoted == 0 || *quoted == 1))
	{
		if (*quoted == 1)
			*quoted = 0;
		else
			*quoted = 1;
	}
	else if (c == '"' && (*quoted == 0 || *quoted == 2))
	{
		if (*quoted == 2)
			*quoted = 0;
		else
			*quoted = 2;
	}
}

static size_t	strlen_c(char const *s, char c)
{
	size_t	len;
	int		quoted;

	len = 0;
	quoted = 0;
	while (s[len] != '\0')
	{
		if (s[len] == '\'' || s[len] == '"')
			check_quoted(&quoted, s[len]);
		else if (quoted == 0 && s[len] == c)
			break ;
		len++;
	}
	return (len);
}

char	**get_arr(char const *s, char c, size_t words, char **arr)
{
	size_t	i;

	i = 0;
	while (words--)
	{
		while (*s == c || *s == '\0')
			s++;
		arr[i] = ft_substr(s, 0, strlen_c(s, c));
		if (arr[i] == NULL)
		{
			while (i > 0)
			{
				free(arr[i]);
				i--;
			}
			if (arr[i] != NULL)
				free(arr[i]);
			free(arr);
			return (NULL);
		}
		i++;
		s += strlen_c(s, c);
	}
	return (arr);
}

char	**minish_split(char const *s, char c)
{
	char	**arr;
	size_t	words;

	if (s == NULL)
		return (NULL);
	words = count_word(s, c);
	arr = x_malloc(sizeof(char *) * (words + 1));
	if (arr == NULL)
	{
		return (NULL);
	}
	arr[words] = 0;
	arr = get_arr(s, c, words, arr);
	return (arr);
}

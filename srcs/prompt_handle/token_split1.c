/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:54:11 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/23 08:54:02 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	split_alloc_count(char *str)
{
	int			count;
	static int	i;

	count = 0;
	while (is_space(str[i]) == 1)
		i++;
	while (((is_space(str[i]) == -1 && is_metachar(str[i]) == -1)
			|| is_quoted(str, &str[i]) == 1) && str[i])
	{
		i++;
		count++;
	}
	if (count == 0)
	{
		while (is_metachar(str[i]) == 1)
		{
			i++;
			count++;
		}
	}
	while (is_space(str[i]) == 1)
		i++;
	if (str[i] == '\0')
		i = 0;
	return (count);
}

static char	**split_alloc(char **strs, char *str, int end)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (i < end)
	{
		count = split_alloc_count(str);
		strs[i] = (char *)x_malloc(count + 1);
		if (strs[i] == NULL)
		{
			free_split_all(strs, i);
			return (NULL);
		}
		ft_memset(strs[i], 40, count + 1);
		strs[i][count] = '\0';
		i++;
	}
	strs[i] = NULL;
	return (strs);
}

static char	**split_help(char **strs, char *s)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (strs[i])
	{
		j = 0;
		while (s[k] == ' ' && is_quoted(s, &s[k]))
			k++;
		while (strs[i][j] != '\0')
			strs[i][j++] = s[k++];
		i++;
	}
	return (strs);
}

char	**token_split(char *s)
{
	char	**strs;

	if (s == NULL)
		return (NULL);
	strs = x_malloc(sizeof(char *) * (count_words(s) + 1));
	if (strs == NULL)
		return (NULL);
	strs = split_alloc(strs, (char *)s, count_words(s));
	if (strs == NULL)
		return (NULL);
	return (split_help(strs, (char *)s));
}
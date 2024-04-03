/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:45:20 by hosonu            #+#    #+#             */
/*   Updated: 2023/11/15 16:26:47 by hoyuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	gnl_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (*str++)
		len++;
	return (len);
}

char	*gnl_strjoin(char *s1, char *s2, size_t j)
{
	char	*str;
	size_t	i;
	size_t	len;

	i = 0;
	if (!s1)
		len = j;
	else
		len = gnl_strlen(s1) + j;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (s1 != NULL)
	{
		while (*s1)
			str[i++] = *s1++;
	}
	while (j > 0)
	{
		str[i++] = *s2++;
		j--;
	}
	str[len] = '\0';
	*s2 = '\0';
	return (str);
}

char	*gnl_strchr(char *s, int c)
{
	char	*str;

	str = (char *)s;
	if (s == NULL)
		return (NULL);
	while (*str)
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	if (c == '\0')
		return (str);
	return (NULL);
}

// char	*get_line(char *str)
// {
// 	char	*re_str;
// 	size_t	i;
// 	size_t	j;

// 	if (*str == '\0')
// 		return (NULL);
// 	i = 0;
// 	while (str[i] && str[i] != '\n')
// 		i++;
// 	if (str[i] == '\n')
// 		i++;
// 	re_str = (char *)malloc(sizeof(char) * (i + 1));
// 	if (!re_str)
// 		return (NULL);
// 	j = 0;
// 	while (j < i)
// 	{
// 		re_str[j] = str[j];
// 		j++;
// 	}
// 	re_str[j] = '\0';
// 	return (re_str);
// }

// char	*left_str(char *str)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*tmp;
// 	size_t	len;

// 	i = 0;
// 	if (*str == '\0')
// 	{
// 		free(str);
// 		return (NULL);
// 	}
// 	while (str[i] && str[i] != '\n')
// 		i++;
// 	tmp = (char *)malloc(sizeof(char) * (gnl_strlen(str) - i + 1));
// 	if (!tmp)
// 		return (NULL);
// 	j = 0;
// 	i++;
// 	len = i;
// 	while (gnl_strlen(str) > len && str[i])
// 		tmp[j++] = str[i++];
// 	tmp[j] = '\0';
// 	free(str);
// 	return (tmp);
// }

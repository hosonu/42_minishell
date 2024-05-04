/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_funcs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:43:08 by hoyuki            #+#    #+#             */
/*   Updated: 2024/04/19 14:43:08 by hoyuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	x_fork(void)
{
	pid_t	result;

	result = fork();
	if (result == -1)
		perror("fork");
	return (result);
}

void	*x_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
		perror("malloc");
	return (ret);
}

void	double_free(char **str)
{
	int		i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	x_sstrncmp(const char *s1, const char *s2, size_t len)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (len == 0)
		return (0);
	if (len != ft_strlen(s2))
		return (-1);
	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i] && i < len - 1)
		i++;
	return (str1[i] - str2[i]);
}

int	perfectly_match(char *s1, char *s2)
{
	char	*ret;

	ret = ft_strnstr(s1, s2, ft_strlen(s1));
	if (ret == NULL)
		return (-1);
	ret = ft_strnstr(s2, s1, ft_strlen(s2));
	if (ret == NULL)
		return (-1);
	return (1);
}

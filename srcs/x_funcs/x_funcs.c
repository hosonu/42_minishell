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
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
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

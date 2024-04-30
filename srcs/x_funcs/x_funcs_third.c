/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_funcs_third.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:43:00 by hoyuki            #+#    #+#             */
/*   Updated: 2024/04/19 14:43:00 by hoyuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	x_dup(int oldfd)
{
	int	newfd;

	newfd = dup(oldfd);
	if (newfd == -1)
	{
		perror("dup");
		exit(EXIT_FAILURE);
	}
	return (newfd);
}

int	x_dup2(int oldfd, int newfd)
{
	int	result;

	result = dup2(oldfd, newfd);
	if (result == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	return (result);
}

int	x_pipe(int pipefd[2])
{
	int	result;

	result = pipe(pipefd);
	if (result == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	return (result);
}

int	x_close(int fd)
{
	int	result;

	result = close(fd);
	if (result == -1)
	{
		perror("close");
	}
	return (result);
}

char	*x_getcwd(void)
{
	char	*buff;
	int		i;

	buff = x_malloc(100);
	i = 1;
	while (getcwd(buff, (100 * i) - 1) == NULL)
	{
		free(buff);
		i++;
		buff = x_malloc(100 * i);
	}
	return (buff);
}

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
		ft_putstr_fd("minish: ", STDERR_FILENO);
		perror("dup");
	}
	return (newfd);
}

int	x_dup2(int oldfd, int newfd)
{
	int	result;

	if (oldfd == -1)
		exit(EXIT_FAILURE);
	result = dup2(oldfd, newfd);
	if (result == -1)
	{
		ft_putstr_fd("minish: ", STDERR_FILENO);
		perror("dup2");
	}
	return (result);
}

int	x_pipe(int pipefd[2])
{
	int	result;

	result = pipe(pipefd);
	if (result == -1)
	{
		ft_putstr_fd("minish: ", STDERR_FILENO);
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
		ft_putstr_fd("minish: ", STDERR_FILENO);
		perror("close");
	}
	return (result);
}

char	*x_getcwd(void)
{
	char	*buff;
	int		i;

	buff = x_malloc(100);
	if (buff == NULL)
		return (NULL);
	i = 1;
	while (getcwd(buff, (100 * i) - 1) == NULL)
	{
		free(buff);
		if (errno == ENOENT)
			return (NULL);
		i++;
		buff = x_malloc(100 * i);
		if (buff == NULL)
			return (NULL);
	}
	return (buff);
}

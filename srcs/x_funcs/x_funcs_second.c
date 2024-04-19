/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_funcs_second.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:42:50 by hoyuki            #+#    #+#             */
/*   Updated: 2024/04/19 14:42:50 by hoyuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	x_execve(const char *filename, char *const argv[], char *const envp[])
{
	int	result;

	result = execve(filename, argv, envp);
	if (result == -1)
	{
		error_msg_for_cmd(argv[0]);
		exit(127);
	}
	return (result);
}

int	x_access(const char *pathname, int mode)
{
	int	result;

	result = access(pathname, mode);
	if (result == -1)
	{
		perror("access");
		exit(EXIT_FAILURE);
	}
	return (result);
}

int	x_unlink(const char *pathname)
{
	int	result;

	result = unlink(pathname);
	if (result == -1)
	{
		perror("unlink");
	}
	return (result);
}

int	x_open(const char *pathname, int flags, mode_t mode)
{
	int	result;

	result = open(pathname, flags, mode);
	if (result == -1)
	{
		write(2, "minish: ", 8);
		perror(pathname);
		exit(EXIT_FAILURE);
	}
	return (result);
}

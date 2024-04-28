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

char	*getenv_char(char *const envp[], const char *name)
{
	int		i;
	int		name_len;

	i = 0;
	name_len = strlen(name);
	if (envp == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		if (strncmp(envp[i], name, name_len) == 0 && envp[i][name_len] == '=')
			return (&envp[i][name_len + 1]);
		i++;
	}
	return (NULL);
}

int	x_execve(const char *filename, char *const argv[], char *const envp[])
{
	int		result;
	char	*path_check;

	result = execve(filename, argv, envp);
	if (result == -1)
	{
		path_check = getenv_char(envp, "PATH");
		if (path_check == NULL)
		{
			write(2, "minish: ", 8);
			write(2, argv[0], ft_strlen(argv[0]));
			write(2, ": Permission denied\n", 20);
			exit(EXIT_FAILURE);
		}
		error_msg_for_cmd(argv[0]);
	}
	return (result);
}

int	x_access(const char *pathname, int mode)
{
	int		result;

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
	int		result;

	result = unlink(pathname);
	if (result == -1)
	{
		perror("unlink");
	}
	return (result);
}

int	x_open(const char *pathname, int flags, mode_t mode)
{
	int		result;

	result = open(pathname, flags, mode);
	if (result == -1)
	{
		write(2, "minish: ", 8);
		perror(pathname);
	}
	return (result);
}

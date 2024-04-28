/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:42:33 by hoyuki            #+#    #+#             */
/*   Updated: 2024/04/19 14:42:33 by hoyuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_msg_for_cmd(const char *filename)
{
	write(2, "minish: ", 8);
	write(2, filename, ft_strlen(filename));
	write(2, ": ", 2);
	write(2, "command not found\n", 18);
}

void	err_msg_for_exit(char *str)
{
	write(2, "minish: exit: ", 14);
	write(2, str, ft_strlen(str));
	write(2, ": numeric argument required\n", 28);
}

void	error_and_exit(const char *filename, int exit_code, bool is_tilda)
{
	write(2, "minish: ", 8);
	if (is_tilda == true)
	{
		write(2, filename, ft_strlen(filename));
		ft_putstr_fd(": is a directory\n", 2);
	}
	else
		perror(filename);
	exit(exit_code);
}

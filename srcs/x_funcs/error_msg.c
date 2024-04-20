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
	write(2, filename, ft_strlen(filename));
	write(2, ": ", 2);
	write(2, "command not found\n", 18);
}

void	error_and_exit(const char *filename)
{
	write(2, "minish: ", 8);
	perror(filename);
	exit(EXIT_FAILURE);
}
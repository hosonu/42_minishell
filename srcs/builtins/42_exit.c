/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 08:31:21 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/23 08:31:22 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(char *av[], int num)
{
	if (av[0] == NULL)
	{
		write(1, "exit\n", 5);
		exit(num);
	}
	else
	{
		num = atoi(av[0]);
		exit(num);
	}
	return (0);
}

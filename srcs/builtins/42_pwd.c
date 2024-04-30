/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 08:32:25 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/23 08:44:13 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	*buff;

	buff = x_getcwd();
	ft_printf("%s\n", buff);
	free(buff);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 08:31:30 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/23 08:32:11 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(char *av[], t_env *env)
{
	int		i;
	t_env	*node;

	i = 0;
	while (av[i] != NULL)
	{
		node = getenv_node(env, av[i]);
		if (node != NULL)
			delone_env(env, node);
		i++;
	}
	return (0);
}

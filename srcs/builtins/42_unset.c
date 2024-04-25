/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 08:31:30 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/25 00:06:52 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	unset_util(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '\0')
	{
		if (is_special_char(av[i]) == 1)
		{
			ft_putstr_fd("minish: unset: not a valid identifier\n",
				STDERR_FILENO);
			return (-1);
		}
		i++;
	}
	return (1);
}

int	ft_unset(char *av[], t_env *env)
{
	int		i;
	int		ret;
	t_env	*node;

	i = 0;
	ret = 0;
	while (av[i] != NULL)
	{
		if (unset_util(av[i]) == -1 || varname_validate(av[i],
				"minish: unset") == -1)
			ret = 1;
		else
		{
			node = getenv_node(env, av[i]);
			if (node != NULL)
				delone_env(env, node);
		}
		i++;
	}
	return (ret);
}

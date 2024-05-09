/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 08:33:07 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/24 23:20:47 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	export_util(char *str, t_env *env)
{
	t_env	*new;
	char	*assignop;

	assignop = ft_strchr(str, '=');
	if (assignop == str)
	{
		ft_putstr_fd("minish: export: not a valid identifier\n", STDERR_FILENO);
		return (1);
	}
	new = new_env(str);
	if (new == NULL)
		return (1);
	addlast_env(env, new);
	return (0);
}

static	void	set_value(t_env *node, char *var)
{
	char	*value;
	char	*tmp;

	if (ft_strchr(var, '=') == NULL)
		return ;
	value = x_malloc(value_strlen(var) + 1);
	if (value == NULL)
		return ;
	value_cpy(value, var);
	if (ft_strchr(var, '+') != NULL
		&& ft_strchr(var, '+') < ft_strchr(var, '='))
	{
		tmp = value;
		value = ft_strjoin(node->value, value);
		if (value == NULL)
		{
			perror("malloc");
			return ;
		}
		free(tmp);
	}
	free(node->value);
	node->value = value;
}

static int	ft_export_util(char *av, int *ret, t_env *env)
{
	char	*key;
	t_env	*node;

	key = get_key(av);
	if (key == NULL)
		return (1);
	node = getenv_node(env, key);
	free(key);
	if (node != NULL)
		set_value(node, av);
	else
	{
		if (export_util(av, env) == 1)
			*ret = 1;
	}
	return (0);
}

int	ft_export(char *av[], t_env *env)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (av[0] == NULL)
		export_display(env);
	while (av[i] != NULL)
	{
		if (varname_validate(av[i], "minish: export") == -1)
		{
			ret = 1;
			i++;
			continue ;
		}
		if (ft_export_util(av[i], &ret, env) == 1)
			return (1);
		i++;
	}
	return (ret);
}

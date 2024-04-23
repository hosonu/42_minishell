/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 08:33:07 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/23 08:33:55 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_display(t_env *env)
{
	env = env->next;
	while (env != NULL)
	{
		ft_printf("declare -x ");
		ft_printf("%s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
}

static int	export_util(char *str, t_env *env)
{
	t_env	*new;
	char	*assignop;

	assignop = ft_strchr(str, '=');
	if (assignop == NULL)
		return (0);
	if (assignop == str)
	{
		ft_putstr_fd("export: not valid identifier\n", STDERR_FILENO);
		return (1);
	}
	new = new_env(str);
	if (new == NULL)
		return (1);
	addlast_env(env, new);
	return (0);
}

static	void	reset_value(t_env *node, char *var)
{
	char	*value;

	value = x_malloc(value_strlen(var) + 1);
	if (value == NULL)
		return ;
	value_cpy(value, var);
	free(node->value);
	node->value = value;
}

static char	*get_key(char *var)
{
	char	*key;
	int		count;

	count = key_strlen(var);
	key = x_malloc(count + 1);
	if (key == NULL)
		return (NULL);
	key_cpy(key, var);
	return (key);
}

int	ft_export(char *av[], t_env *env)
{
	int		i;
	char	*key;
	t_env	*node;

	i = 0;
	if (av[0] == NULL)
		export_display(env);
	while (av[i] != NULL)
	{
		key = get_key(av[i]);
		if (key == NULL)
			return (1);
		node = getenv_node(env, key);
		free(key);
		if (node != NULL)
			reset_value(node, av[i]);
		else
		{
			if (export_util(av[i], env) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

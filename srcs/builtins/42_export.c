/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosonu <hoyuki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 23:34:28 by hosonu            #+#    #+#             */
/*   Updated: 2024/04/22 23:34:32 by hosonu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	swap_nodes(t_env **env, t_env *prev, t_env *current, int *sorted)
{
	t_env	*next_node;

	next_node = current->next;
	*sorted = 0;
	if (prev == NULL)
		*env = next_node;
	else
		prev->next = next_node;
	current->next = next_node->next;
	next_node->next = current;
}

void	update_pointers(t_env **env, t_env **prev, t_env **tmp)
{
	if (*prev == NULL)
		*tmp = *env;
	else
		*tmp = (*prev)->next;
}

void	env_sort_ascii(t_env **env)
{
	int		sorted;
	t_env	*tmp;
	t_env	*prev;

	sorted = 0;
	while (sorted != 1)
	{
		sorted = 1;
		prev = NULL;
		tmp = *env;
		while (tmp && tmp->next)
		{
			if (strcmp(tmp->key, tmp->next->key) > 0)
			{
				swap_nodes(env, prev, tmp, &sorted);
				update_pointers(env, &prev, &tmp);
			}
			else
			{
				prev = tmp;
				tmp = tmp->next;
			}
		}
	}
}

void	export_display(t_env *env)
{
	t_env	*sorted_env;
	t_env	*tmp;

	if (env == NULL)
		return ;
	sorted_env = (env);
	env_sort_ascii(&sorted_env);
	tmp = sorted_env;
	while (tmp != NULL)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

int	ft_export(char *av[], t_env *env)
{
	int		i;
	t_env	*new;

	i = 0;
	if (av[0] == NULL)
		export_display(env);
	while (av[i] != NULL)
	{
		if (ft_strchr(av[i], '=') == NULL)
		{
			i++;
			continue ;
		}
		if (ft_strchr(av[i], ' ') == NULL)
			;
		else if (ft_strchr(av[i], '=') > ft_strchr(av[i], ' '))
		{
			printf("export: not valid identifier");
			i++;
			continue ;
		}
		new = new_env(av[i]);
		addlast_env(&env, new);
		i++;
	}
}

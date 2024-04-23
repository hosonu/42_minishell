/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:46:47 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/23 16:38:17 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_key(char *var)
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

static void	swap_nodes(t_env *prev, t_env *current, int *sorted)
{
	t_env	*next_node;

	next_node = current->next;
	*sorted = 0;
	prev->next = next_node;
	current->next = next_node->next;
	next_node->next = current;
}

static void	update_pointers(t_env *prev, t_env **tmp)
{
	*tmp = prev->next;
}

static void	env_sort_ascii(t_env *env)
{
	int		sorted;
	t_env	*tmp;
	t_env	*prev;

	sorted = 0;
	while (sorted != 1)
	{
		sorted = 1;
		tmp = env->next;
		prev = env;
		while (tmp && tmp->next)
		{
			if (strcmp(tmp->key, tmp->next->key) > 0)
			{
				swap_nodes(prev, tmp, &sorted);
				update_pointers(prev, &tmp);
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
	env_sort_ascii(sorted_env);
	tmp = sorted_env->next;
	while (tmp != NULL)
	{
		if (tmp->value != NULL)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
}

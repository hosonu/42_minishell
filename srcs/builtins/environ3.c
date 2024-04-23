/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 08:25:45 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/23 15:56:50 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_special_char(char c)
{
	if (ft_strchr("-+=;&()|^<>?*[]$`\'\"\\!{}\n\t ", c) != NULL)
		return (1);
	return (0);
}

int	varname_validate(char *var)
{
	int	i;

	i = 0;
	if ('0' <= var[0] && var[0] <= '9')
	{
		ft_printf("%c is not a valid identifier\n", var[i]);
		return (-1);
	}
	while (var[i] != '=' && var[i] != '\0')
	{
		if (is_special_char(var[i]) == 1)
		{
			if (var[i + 1] == '=' && var[i] == '+')
				return (1);
			else
			{
				ft_printf("%c is not a valid identifier\n", var[i]);
				return (-1);
			}
		}
		i++;
	}
	return (1);
}

int	key_strlen(char *var)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (is_special_char(var[i]) == 0 && var[i] != '\0')
	{
		i++;
		count++;
	}
	return (count + 1);
}

int	value_strlen(char *var)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (var[i] != '=' && var[i] != '\0')
		i++;
	while (var[i] != '\0')
	{
		i++;
		count++;
	}
	return (count + 1);
}

static char	**env_split_alloc(char **split, char *var)
{
	int	count;

	count = key_strlen(var);
	split[0] = x_malloc(count + 1);
	if (split[0] == NULL)
		return (NULL);
	count = value_strlen(var);
	if (ft_strchr(var, '=') == NULL)
		split[1] = NULL;
	else if (count == 0)
		split[1] = ft_strdup("");
	else
	{
		split[1] = x_malloc(value_strlen(var) + 1);
		if (split[1] == NULL)
		{
			free(split[0]);
			return (NULL);
		}
	}
	return (split);
}

static void	env_split_cpy(char **split, char *var)
{
	key_cpy(split[0], var);
	if (split[1] != NULL && split[1][0] != '\0')
		value_cpy(split[1], var);
}

char	**env_split(char *var)
{
	char	**split;

	split = x_malloc(sizeof(char *) * 2);
	if (split == NULL)
		return (NULL);
	split[1] = NULL;
	split = env_split_alloc(split, var);
	if (split == NULL)
	{
		free(split);
		return (NULL);
	}
	env_split_cpy(split, var);
	return (split);
}

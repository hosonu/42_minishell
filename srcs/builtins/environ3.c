/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 08:25:45 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/24 23:22:00 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_special_char(char c)
{
	if (ft_strchr("-+=;:&()|^<>?*[]$`\'\"\\!{}\n\t ", c) != NULL)
		return (1);
	return (0);
}

int	varname_validate(char *var, char *cmd)
{
	int	i;

	i = 0;
	if ('0' <= var[0] && var[0] <= '9')
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
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
				ft_putstr_fd(cmd, STDERR_FILENO);
				ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
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

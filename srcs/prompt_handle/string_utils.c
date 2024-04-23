/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:14:54 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/18 23:39:51 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_quoted_util(char *str, char *pnt)
{
	int		i;
	char	c;
	uint8_t	quotefg;

	i = 0;
	quotefg = false;
	while (str[i] != '\0')
	{
		if (is_quote(str[i]) > 0 && quotefg == false)
		{
			c = str[i];
			quotefg = true;
		}
		else if (c == str[i] && quotefg == true)
			quotefg = false;
		else if (&str[i] == pnt)
		{
			if (quotefg == true)
				return (1);
			else
				return (-1);
		}
		i++;
	}
	return (1);
}

int	is_quoted(char *str, char *pnt)
{
	if (pnt == NULL || str == NULL || *pnt == '\0')
		return (-1);
	return (is_quoted_util(str, pnt));
}

int	is_metachar(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (-1);
}

int	is_quote(char c)
{
	if (c == '\"')
		return (1);
	else if (c == '\'')
		return (2);
	else
		return (0);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (-1);
}

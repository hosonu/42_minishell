/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:14:54 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/04 01:09:36 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_quoted(char *str, char *pnt)
{
	int	i;
	char	c;
	uint8_t	quotefg;

	i = 0;
	quotefg = false;
	if (pnt == NULL)
		return (-1);
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
		return 0;
}

int	is_more_than_word(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' && is_quoted(str, &str[i]) == -1)
			return (1);
		i++;
	}
	return (-1);
}

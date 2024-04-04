/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:00:23 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/04 00:15:42 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	prompt_validate(char *prompt)
{
	if (quotation_validate(prompt) == -1)
	{
		ft_printf("Quotation Error: Not closed\n");
		return (-1);
	}
	if (redirect_validate(prompt) == -1)
	{
		ft_printf("REDIRECT Error: No redirect file\n");
		return (-1);
	}
	return (1);
}

int	redirect_validate(char *str)
{
	uint8_t	metafg;
	uint8_t	quotefg;
	int	i;
	char	c;

	metafg = false;
	quotefg = false;
	i = 0;
	while (str[i] != '\0')
	{
		if (is_quote(str[i] > 0))
		{
			if (quotefg == false)
			{
				c = str[i];
				quotefg = true;
			}
			else if (quotefg == true && c == str[i])
				quotefg = false;
		}
		if (is_metachar(str[i]) == 1 && quotefg == false)
			metafg = true;
		else if (str[i] != ' ')
			metafg = false;
		i++;
	}
	if (metafg == 1)
		return (-1);
	return (1);
}

int	quotation_validate(char *str)
{
	int	i;
	uint8_t	openfg;
	char	c;
	

	i = 0;
	openfg = false;
	while (str[i] != '\0')
	{
		if (is_quote(str[i]) > 0)
		{
			if (openfg == false)
			{
				c = str[i];
				openfg = true;
			}
			else if (openfg == true && c == str[i])
				openfg = false;
		}
		i++;
	}
	if (openfg == true)
		return (-1);
	return (1);
}

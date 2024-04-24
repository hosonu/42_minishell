/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:00:23 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/24 23:07:46 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	quotation_validate_util(char *str)
{
	int		i;
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

int	quotation_validate(char *prompt)
{
	if (quotation_validate_util(prompt) == -1)
	{
		ft_putstr_fd("minish: Quotation not closed\n", STDERR_FILENO);
		return (-1);
	}
	return (1);
}

static int	syntax_validate_util(t_token *token)
{
	uint8_t	metafg;

	metafg = false;
	if (token->type == METAPIPE)
		return (-1);
	while (token != NULL)
	{
		if (token->type < 0)
		{
			if (metafg == true)
				return (-1);
			metafg = true;
		}
		else
			metafg = false;
		token = token->next;
	}
	if (metafg == true)
		return (-1);
	return (1);
}

int	syntax_validate(t_token *token, t_status *status)
{
	if (syntax_validate_util(token) == -1)
	{
		status->exit_code = 258;
		ft_putstr_fd("minish: syntax error\n", STDERR_FILENO);
		return (-1);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:00:23 by kojwatan          #+#    #+#             */
/*   Updated: 2024/05/09 14:59:07 by hoyuki           ###   ########.fr       */
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

int	quotation_validate(char *prompt, t_status *status)
{
	if (quotation_validate_util(prompt) == -1)
	{
		ft_putstr_fd("minish: Quotation not closed\n", STDERR_FILENO);
		status->exit_code = 258;
		return (-1);
	}
	return (1);
}

static void	manage_flag(uint8_t *metafg, uint8_t *ppfg, int type)
{
	*metafg = true;
	if (type == METAPIPE)
		*ppfg = true;
	else
		*ppfg = false;
}

static int	syntax_validate_util(t_token *token)
{
	uint8_t	metafg;
	uint8_t	ppfg;

	metafg = false;
	ppfg = false;
	if (token->type == METAPIPE)
		return (-1);
	while (token != NULL)
	{
		if (token->type < 0)
		{
			if (metafg == true && ppfg == false)
				return (-1);
			manage_flag(&metafg, &ppfg, token->type);
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

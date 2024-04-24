/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_validate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 01:29:30 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/24 21:08:34 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	completly_match(char *s1, char *s2)
{
	char	*ret;

	ret = ft_strnstr(s1, s2, ft_strlen(s1));
	if (ret == NULL)
		return (-1);
	ret = ft_strnstr(s2, s1, ft_strlen(s2));
	if (ret == NULL)
		return (-1);
	return (1);
}

static int	metaout_check(char *token)
{
	if (completly_match(token, ">") == 1)
		return (1);
	if (completly_match(token, ">>") == 1)
		return (1);
	return (-1);
}

static int	metachar_validate_util(t_token node)
{
	int	ret;

	ret = 0;
	if (node.type == METAOUT)
		ret = metaout_check(node.token);
	else if (node.type == METAHEREDOC)
		ret = completly_match(node.token, "<<");
	else if (node.type == METAIN)
		ret = completly_match(node.token, "<");
	else if (node.type == METAPIPE)
		ret = completly_match(node.token, "|");
	return (ret);
}

int	metachar_validate(t_token *node, t_status *status)
{
	int	ret;

	ret = 0;
	while (node != NULL)
	{
		if (node->type < 0)
			ret = metachar_validate_util(*node);
		if (ret == -1)
			break ;
		node = node->next;
	}
	if (ret == -1)
	{
		status->exit_code = 258;
		ft_putstr_fd("minish: syntax error\n", STDOUT_FILENO);
	}
	return (ret);
}

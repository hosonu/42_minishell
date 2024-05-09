/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: watanabekoji <watanabekoji@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:21:07 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/30 18:22:01 by watanabekoj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	skip_space(char *s, int i)
{
	while ((is_space(s[i]) == -1 && is_metachar(s[i]) == -1 && s[i])
		|| is_quoted(s, &s[i]) == 1)
		i++;
	while (is_space(s[i]) == 1 && s[i])
		i++;
	return (i);
}

int	count_words(char *s)
{
	int	i;
	int	count;

	i = 0;
	if (s[i] == 0)
		return (0);
	while (is_space(s[i]) == 1)
		i++;
	count = (is_metachar(s[i]) != 1 && s[i] != '\0');
	while (s[i] != '\0')
	{
		i = skip_space(s, i);
		if (s[i])
		{
			count++;
			if (is_metachar(s[i]) == 1)
			{
				while (is_metachar(s[i]) == 1)
					i++;
				if (s[i] != '\0' && is_space(s[i]) == -1)
					count++;
			}
		}
	}
	return (count);
}

void	free_split_all(char **strs, int i)
{
	while (i > 0)
	{
		free(strs[i]);
		i--;
	}
	free(strs[i]);
	free(strs);
}

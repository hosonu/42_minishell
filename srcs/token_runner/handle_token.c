/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:41:33 by hoyuki            #+#    #+#             */
/*   Updated: 2024/04/19 14:41:33 by hoyuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_specific_quote(char *token, int *i, int *quote_status)
{
	char	*new_token;

	token[*i] = '\0';
	new_token = ft_strjoin(token, token + *i + 1);
	if (new_token == NULL)
		return (NULL);
	*i -= 1;
	*quote_status += 1;
	free(token);
	return (new_token);
}

char	*remove_quote(char *token)
{
	int	i;
	int	quoted;
	int	dblquoted;
	int	quote_type;

	i = 0;
	quoted = 0;
	dblquoted = 0;
	if (token == NULL)
		return (NULL);
	while (token[i] != '\0')
	{
		quote_type = is_quote(token[i]);
		if (quote_type == 1 && dblquoted % 2 == 0)
			token = remove_specific_quote(token, &i, &quoted);
		else if (quote_type == 2 && quoted % 2 == 0)
			token = remove_specific_quote(token, &i, &dblquoted);
		if (token == NULL)
			return (NULL);
		i++;
	}
	return (token);
}

char	**remove_empty_strings(char **arr, int count)
{
	int		i;
	char	**new_arr;
	char	**p;

	i = 0;
	new_arr = x_malloc(sizeof(char *) * (count + 1));
	if (new_arr == NULL)
	{
		double_free(arr);
		return (NULL);
	}
	p = new_arr;
	while (arr[i] != NULL)
	{
		if (arr[i][0] != '\0')
		{
			*p = strdup(arr[i]);
			p++;
		}
		i++;
	}
	*p = NULL;
	double_free(arr);
	return (new_arr);
}

char	**handle_token(char **splited_token, int exit_code, t_env *env)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (splited_token[i] != NULL)
	{
		splited_token[i] = expand_variable(splited_token[i], 0, exit_code,
				env);
		splited_token[i] = remove_quote(splited_token[i]);
		if (splited_token[i][0] != '\0')
			count++;
		i++;
	}
	return (remove_empty_strings(splited_token, count));
}

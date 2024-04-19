/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:43:52 by hoyuki            #+#    #+#             */
/*   Updated: 2024/04/19 14:43:52 by hoyuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_and_expand(int index, char *input, t_env *env)
{
	int		i;
	char	*trimmed_input;

	i = index;
	while (ft_isalnum(input[i + 1]) != 0)
		i++;
	trimmed_input = ft_substr(input, index + 1, i - index);
	trimmed_input = ft_getenv(env, trimmed_input);
	return (trimmed_input);
}

char	*change_input(char *expanded_in, char *original_in, int index)
{
	char	*after_symbol;
	char	*before_symbol;
	char	*change_in;

	before_symbol = ft_substr(original_in, 0, index);
	while (ft_isalnum(original_in[index + 1]) != 0)
		index++;
	if (original_in[index + 1] == '?')
		index++;
	after_symbol = ft_substr(original_in, index + 1, ft_strlen(original_in)
			- index + 1);
	change_in = ft_strjoin(before_symbol, expanded_in);
	change_in = ft_strjoin(change_in, after_symbol);
	return (change_in);
}

char	*expand_variable(char *input, int heredoc, int exit_code, t_env *env)
{
	char	*expanded_input;
	int		i;
	int		unexpand;

	i = 0;
	unexpand = 0;
	while (input[i] != '\0')
	{
		if (is_quote(input[i]) == 1 && heredoc == 0)
			unexpand += 2;
		if (is_quote(input[i]) == 2 && heredoc == 0 && unexpand != 2)
			unexpand += 1;
		if (input[i] == '$' && unexpand % 2 == 0 && input[i + 1] != '\0')
		{
			expanded_input = check_and_expand(i, input, env);
			if (input[i + 1] == '?')
				expanded_input = ft_itoa(exit_code);
			input = change_input(expanded_input, input, i);
			i += ft_strlen(expanded_input) - 1;
		}
		i++;
	}
	if(i == 1 && input[0] == '~')
		input = ft_getenv(env, "HOME");
	return (input);
}

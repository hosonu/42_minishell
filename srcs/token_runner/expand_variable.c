/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:43:52 by hoyuki            #+#    #+#             */
/*   Updated: 2024/04/24 18:22:38 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_and_expand(int index, char *input, t_env *env)
{
	int		i;
	char	*trimmed_input;
	char	*expanded_input;

	i = index;
	while (ft_isalnum(input[i + 1]) != 0)
		i++;
	trimmed_input = ft_substr(input, index + 1, i - index);
	expanded_input = ft_getenv(env, trimmed_input);
	free(trimmed_input);
	return (expanded_input);
}

char	*change_input(char *expanded_in, char *original_in, int index)
{
	char	*after_symbol;
	char	*before_symbol;
	char	*change_in;
	char	*tmp;

	before_symbol = ft_substr(original_in, 0, index);
	while (ft_isalnum(original_in[index + 1]) != 0)
		index++;
	if (original_in[index + 1] == '?')
		index++;
	after_symbol = ft_substr(original_in, index + 1, ft_strlen(original_in)
			- index + 1);
	change_in = ft_strjoin(before_symbol, expanded_in);
	tmp = change_in;
	change_in = ft_strjoin(change_in, after_symbol);
	free(tmp);
	free(before_symbol);
	free(after_symbol);
	return (change_in);
}

char	*process_expansion(int *i, char *input, int exit_code, t_env *env)
{
	char	*expanded_input;
	char	*tmp;

	expanded_input = check_and_expand(*i, input, env);
	if (input[*i + 1] == '?')
		expanded_input = ft_itoa(exit_code);
	tmp = change_input(expanded_input, input, *i);
	free(input);
	input = tmp;
	*i += ft_strlen(expanded_input) - 1;
	return (input);
}

char	*expand_home_directory(char *input, t_env *env)
{
	char	*tmp;

	tmp = ft_getenv(env, "HOME");
	if (tmp == NULL)
		tmp = ft_strdup(getenv("HOME"));
	free(input);
	input = tmp;
	return (input);
}

char	*expand_variable(char *input, int heredoc, int exit_code, t_env *env)
{
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
			input = process_expansion(&i, input, exit_code, env);
		i++;
	}
	if (i == 1 && input[0] == '~' && heredoc == 0)
		input = expand_home_directory(input, env);
	return (input);
}

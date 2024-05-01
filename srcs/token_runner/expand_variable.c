/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:43:52 by hoyuki            #+#    #+#             */
/*   Updated: 2024/04/24 18:25:16 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_and_expand(int index, char *input, t_env *env)
{
	int		i;
	char	*trimmed_input;
	char	*expanded_input;

	i = index;
	if (ft_isalpha(input[i + 1]) == 0)
	{
		while (ft_isalnum(input[i + 1]) == 1)
			i++;
		if (i - index > 0)
			trimmed_input = ft_substr(input, index + 2, i - index);
		else
			trimmed_input = ft_strdup("$");
		return (trimmed_input);
	}
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
	{
		tmp = expanded_input;
		expanded_input = ft_itoa(exit_code);
		free(tmp);
	}
	tmp = change_input(expanded_input, input, *i);
	free(input);
	input = tmp;
	*i += ft_strlen(expanded_input) - 1;
	free(expanded_input);
	return (input);
}

char	*expand_home_directory(char *input, t_env *env)
{
	char	*tmp;
	char	*after_tilda;

	tmp = ft_getenv(env, "HOME");
	if (tmp == NULL)
		tmp = ft_strdup(getenv("HOME"));
	if (input[1] == '/')
	{
		after_tilda = ft_substr(input, 1, ft_strlen(input) - 1);
		free(input);
		input = ft_strjoin(tmp, after_tilda);
		free(after_tilda);
		free(tmp);
	}
	else if (input[1] == '\0')
	{
		free(input);
		input = tmp;
	}
	else
		free(tmp);
	return (input);
}

char	*expand_variable(char *input, int heredoc, int exit_code, t_env *env)
{
	int		i;
	int		unexpand;

	i = 0;
	unexpand = 0;
	if (input[0] == '~' && heredoc == 0)
		input = expand_home_directory(input, env);
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
	return (input);
}

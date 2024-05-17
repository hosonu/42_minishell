/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: watanabekoji <watanabekoji@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:49:36 by kojwatan          #+#    #+#             */
/*   Updated: 2024/05/15 17:57:14 by watanabekoj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	token_count(t_token *top)
{
	int	count;

	count = 0;
	while (top != NULL)
	{
		count++;
		top = top->next;
	}
	return (count);
}

t_token	**linear_token_list(t_token *top)
{
	t_token	**list;
	int		i;

	list = x_malloc(sizeof(t_token *) * (token_count(top) + 1));
	if (list == NULL)
		return (NULL);
	i = 0;
	while (top != NULL)
	{
		list[i] = top;
		i++;
		top = top->next;
	}
	list[i] = NULL;
	return (list);
}

static char	*input_prompt(t_env *env, t_status *status)
{
	char	*input;
	char	*prompt;
	char	*pwd;

	pwd = x_getcwd();
	prompt = ft_strjoin(pwd, ": ");
	free(pwd);
	if (prompt == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	input = readline(prompt);
	free(prompt);
	if (input == NULL)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		free_env(env);
		exit(status->exit_code);
	}
	return (input);
}

t_token	**prompt_handle(t_env *env, t_status *status)
{
	t_token	**list;
	t_token	*tokens;
	char	*input;

	input = input_prompt(env, status);
	if (input == NULL)
		return (NULL);
	if (input[0] != '\0')
		add_history(input);
	else if (input[0] == '\0')
	{
		free(input);
		return (NULL);
	}
	if (quotation_validate(input, status) == -1)
	{
		free(input);
		return (NULL);
	}
	tokens = tokenize(input);
	free(input);
	if (tokens == NULL)
		return (NULL);
	list = token_list(tokens, status);
	return (list);
}

t_token	**token_list(t_token *tokens, t_status *status)
{
	t_token	**list;

	decide_type(tokens);
	if (syntax_validate(tokens, status) == -1
		|| metachar_validate(tokens, status) == -1)
	{
		free_chain_token_list(tokens);
		return (NULL);
	}
	sort_token(&tokens);
	if (token_join(tokens) == NULL)
	{
		free_chain_token_list(tokens);
		return (NULL);
	}
	list = linear_token_list(tokens);
	if (list == NULL)
	{
		free_chain_token_list(tokens);
		return (NULL);
	}
	token_type_revise(list);
	return (list);
}

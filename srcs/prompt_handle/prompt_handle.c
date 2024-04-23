/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:49:36 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/23 10:07:58 by kojwatan         ###   ########.fr       */
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

static char	*input_prompt(void)
{
	char	*input;
	char	*pwd;
	char	*prompt;
	char	buff[PATH_MAX];

	getcwd(buff, PATH_MAX);
	prompt = ft_strjoin(buff, ": ");
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
		exit(EXIT_SUCCESS);
	}
	if (input[0] != '\0')
		add_history(input);
	else if (input[0] == '\0')
		return (NULL);
	return (input);
}

t_token	**prompt_handle(void)
{
	t_token	**list;
	t_token	*tokens;
	char	*input;

	input = input_prompt();
	if (input == NULL)
		return (NULL);
	if (quotation_validate(input) == -1)
	{
		free(input);
		//g_sige = 248
		return (NULL);
	}
	tokens = tokenize(input);
	free(input);
	if (tokens == NULL)
		return (NULL);
	list = token_list(tokens);
	return (list);
}

t_token	**token_list(t_token *tokens)
{
	t_token	**list;

	decide_type(tokens);
	if (syntax_validate(tokens) == -1 || metachar_validate(tokens) == -1)
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcntl_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:44:00 by hoyuki            #+#    #+#             */
/*   Updated: 2024/04/19 14:44:00 by hoyuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	for_norminette(int fdin, char *input, bool is_error)
{
	x_close(fdin);
	free(input);
	if (is_error == 1)
		rl_event_hook = 0;
}

int	judge_quoted(t_token *list)
{
	int	i;
	int	is_quoted;

	i = 0;
	is_quoted = 0;
	while (list->token[i] != '\0')
	{
		if (list->token[i] == '"' || list->token[i] == '\'')
			is_quoted = 1;
		i++;
	}
	list->token = remove_quote(list->token);
	return (is_quoted);
}

void	execute_heredoc(int gfd[2], t_token *list, int exit_code, t_env *env)
{
	char	*input;
	int		is_quoted;

	heredoc_init(gfd);
	is_quoted = judge_quoted(list);
	while (gfd[0] != -1 && get_sigint_flag() == 0)
	{
		input = readline("> ");
		if (input == NULL || get_sigint_flag() == 1)
		{
			for_norminette(gfd[0], input, 1);
			break ;
		}
		if (perfectly_match(input, list->token) == 1)
		{
			for_norminette(gfd[0], input, 0);
			break ;
		}
		if (is_quoted != 1)
			input = expand_variable(input, 1, exit_code, env);
		write(gfd[0], input, ft_strlen(input));
		write(gfd[0], "\n", 1);
		free(input);
	}
}

int	fcntl_token(t_fdgs *fdgs, t_token *list, t_status *status, t_env *env)
{
	if (fdgs->gfd[0] != -2 && list->type == INFILE)
		x_close(fdgs->gfd[0]);
	if (fdgs->gfd[1] != -2 && (list->type == 10 || list->type == APNDOUTFILE))
		x_close(fdgs->gfd[1]);
	list->token = expand_variable(list->token, 0, status->exit_code, env);
	list->token = remove_quote(list->token);
	if (list->type == TRUNCOUTFILE)
		fdgs->gfd[1] = x_open(list->token, O_TRUNC | O_CREAT | O_RDWR, 0644);
	else if (list->type == APNDOUTFILE)
		fdgs->gfd[1] = x_open(list->token, O_APPEND | O_CREAT | O_RDWR, 0644);
	else if (list->type == INFILE)
		fdgs->gfd[0] = x_open(list->token, O_RDONLY, 0);
	if (list->type > 0 && (fdgs->gfd[0] == -1 || fdgs->gfd[1] == -1))
	{
		status->exit_code = 1;
		return (-1);
	}
	return (0);
}

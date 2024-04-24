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

void	execute_heredoc(int gfd[2], t_token *list, int exit_code, t_env *env)
{
	char	*input;

	heredoc_init(gfd);
	while (gfd[0] != -1 && get_sigint_flag() == 0)
	{
		input = readline("> ");
		if (input == NULL || get_sigint_flag() == 1)
		{
			x_close(gfd[0]);
			free(input);
			rl_event_hook = 0;
			break ;
		}
		if (ft_strncmp(input, list->token, ft_strlen(list->token)) == 0
			&& ft_strlen(input) == ft_strlen(list->token))
		{
			x_close(gfd[0]);
			free(input);
			break ;
		}
		input = expand_variable(input, 1, exit_code, env);
		write(gfd[0], input, ft_strlen(input));
		write(gfd[0], "\n", 1);
		free(input);
	}
}

int	fcntl_token(t_fdgs *fdgs, t_token *list, int exit_code, t_env *env)
{

	list->token = expand_variable(list->token, 0, exit_code, env);
	list->token = remove_quote(list->token);
	if (list->type == TRUNCOUTFILE)
	{
		fdgs->gfd[1] = x_open(list->token, O_TRUNC | O_CREAT | O_RDWR, 0644);
		return (1);
	}
	else if (list->type == APNDOUTFILE)
	{
		fdgs->gfd[1] = x_open(list->token, O_APPEND | O_CREAT | O_RDWR, 0644);
		return (1);
	}
	else if (list->type == INFILE)
	{
		fdgs->gfd[0] = x_open(list->token, O_RDONLY, 0);
		return (1);
	}
	else if (list->type == HEREDOC)
		return (1);
	return (0);
}

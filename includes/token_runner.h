/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_runner.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-20 11:10:59 by user              #+#    #+#             */
/*   Updated: 2024/04/24 21:15:25 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_RUNNER_H
# define TOKEN_RUNNER_H

# include "./minishell.h"

// dispatch_token.c
void	dispatch_token(t_token **list, t_env *env, t_status *status);
void	token_main_engine(t_token **list, t_fdgs *fdgs, t_status *status,
			t_env *env);

// dispatch_token_utlis.c
int		dispatch_token_help(t_token **list, t_fdgs *fdgs, t_status *status,
			t_env *env);
void	pre_manage_fd_parent(t_token *list, t_fdgs *fdgs);
void	post_manage_fd_parent(t_fdgs *fdgs, char **tokens_splited,
			t_token **list);
void	mange_fd_child(t_token **list, t_fdgs *fdgs);
void	child_help(char **tokens_splited, t_env *env);

// wait.c
void	wait_childs(t_status *status);

// execve_token.c
void	execve_token(char **tokens_splited, t_env *env);
char	*path_lookup(char *command, char **envi);
char	*join_path(char *command, char *path);

// manage_fd.c
void	manage_gfdin(int gfd[2], t_token *list, bool gene);
void	manage_gfdout(int gfd[2], t_token *list, bool gene);
void	manage_pipein(int pp[2], t_token *list);
void	manage_pipeout(int pp[2], t_token *list);

// fcntl_token.c
int		fcntl_token(t_fdgs *fdgs, t_token *list, t_status *status, t_env *env);
void	execute_heredoc(int gfd[2], t_token *list, int exit_code, t_env *env);

// expand_varivable.c
char	*expand_variable(char *input, int heredoc, int exit_code, t_env *env);
char	*change_input(char *expanded_in, char *original_in, int index);
char	*check_and_expand(int index, char *input, t_env *env);

// handle_token.c
char	**handle_token(char **splited_token, int exit_code, t_env *env);
char	*remove_quote(char *token);
char	*remove_specific_quote(char *token, int *i, int *quote_status);

// check_buiitins.c
int		check_builtins_parents(char **tokens_splited, t_env *env,
			t_status *status);
int		check_builtins_childs(char **tokens_splited, t_env *env);
int		check_argc(char **str);

#endif

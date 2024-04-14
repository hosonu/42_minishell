#ifndef TOKEN_RUNNER_H
#   define TOKEN_RUNNER_H

#include "./minishell.h"

//dispatch_token.c
void    dispatch_token(t_token **list);
void    dispatch_token_help(t_token *list, t_fdgs *fdgs, t_status *status, t_env *env);
int     check_builtins(char **tokens_splited, t_env *env);

//execve_token.c
void    execve_token(char **tokens_splited, t_env *env);

char    *path_lookup(char *command, char **envi);
char    *join_path(char *command, char *path);

//manage_fd.c
void    manage_gfdin(int gfd[2], t_token *list);
void    manage_gfdout(int gfd[2], t_token *list);
void    manage_pipein(int pp[2], t_token *list);
void    manage_pipeout(int pp[2], t_token *list);

//fcntl_token.c
void   fcntl_token(t_fdgs *fdgs, t_token *list, int exit_code, t_env *env);

// void    execute_heredoc(int gfd[2], t_token *list, int exit_code);
void execute_heredoc(int gfd[2], t_token *list, int exit_code, t_env *env);

//expand_varivable.c
char    *expand_variable(char *input, int heredoc, int exit_code, t_env *env);
char    *change_input(char *expanded_in, char *original_in, int index);
char    *check_and_expand(int index, char *input, t_env *env);

//handle_token.c
void    handle_token(char **splited_token, int exit_code, t_env *env);
char    *remove_quote(char *token);
char    *remove_specific_quote(char *token, int *i, int *quote_status);

#endif

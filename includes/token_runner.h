#ifndef TOKEN_RUNNER_H
#   define TOKEN_RUNNER_H

#include "./minishell.h"

//dispatch_token.c
void    dispatch_token(t_token **list);
void    dispatch_token_help(t_token **list, t_fdgs* fdgs, int i);

//execve_token.c
void    execve_token(t_token *list);
char    *path_lookup(char *comand, char **envi);
char    *join_path(char *comand, char *path);

//manage_fd.c
void    manage_gfdin(int gfd[2], t_token *list);
void    manage_gfdout(int gfd[2], t_token *list);
void    manage_pipein(int pp[2], t_token *list);
void    manage_pipeout(int pp[2], t_token *list);

//fctl_token.c
void   fctl_token(t_fdgs *fdgs, t_token *list);
void    execute_heredoc(int gfd[2], t_token *list);

//expand_varivable.c
char    *expand_variable(char *input, int heredoc);
char    *change_input(char *expanded_in, char *original_in, int index);
char    *check_and_expand(int index, char *input, char **envi);
size_t  get_len_env(char *envi);
char    *get_expanded_env(char *env);

//handle_token.c
void    handle_token(char **splited_token);
char    *remove_quote(char *token);
char    *remove_specific_quote(char *token, int *i, int *quote_status);

#endif

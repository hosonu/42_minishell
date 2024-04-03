#ifndef TOKEN_RUNNER_H
#   define TOKEN_RUNNER_H

#include "./minishell.h"

//dispatch_token.c
void dispatch_token(t_token **list);

//execve_token.c
void    execve_token(t_token *list);
char *path_lookup(char *comand, char **envi);
char *join_path(char *comand, char *path);


//fctl_token.c
void   fctl_token(int gfd[2], t_token *list);
void execute_heredoc(int gfd[2], t_token *list);

//manage_fd.c
void    manage_gfdin(int gfd[2], t_token *list);
void    manage_gfdout(int gfd[2], t_token *list);
void    manage_pipein(int pp[2], t_token *list);
void    manage_pipeout(int pp[2], t_token *list);

#endif

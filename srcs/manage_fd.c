#include "../includes/minishell.h"

void    manage_gfdin(int gfd[2], t_token *list)
{
    switch (list->type)
    {
    case REINCOMMAND:
    case REINOUTCOMMAND:
        dup2(gfd[0], STDIN_FILENO);
        close(gfd[0]);
        break;
    case HEREDOCCOMMAND:
    case REOUTHEREDOCCOMMAND:
        gfd[0] = open("/tmp/sh-thd-tekitou", O_RDONLY);
        dup2(gfd[0], STDIN_FILENO);
        close(gfd[0]);
        break;
    }
}

void    manage_gfdout(int gfd[2], t_token *list)
{
    switch (list->type)
    {
    case REOUTCOMMAND:
    case REINOUTCOMMAND:
    case REOUTHEREDOCCOMMAND:
        dup2(gfd[1], STDOUT_FILENO);
        close(gfd[1]);
        break;
    }
}

void    manage_pipein(int pp[2], t_token *list)
{
    if(list->pipein == true)
    {
        switch (list->type)
        {
        case COMMAND:
        case REOUTCOMMAND:
            dup2(pp[0], STDIN_FILENO);
            break;
        }
        close(pp[0]);
        close(pp[1]);
    }
    if(list->pipeout == true)
        pipe(pp);
}

void    manage_pipeout(int pp[2], t_token *list)
{
    if(list->pipeout == true)
    {
        switch (list->type)
        {
        case COMMAND:
        case REINCOMMAND:
        case HEREDOCCOMMAND:
            dup2(pp[1], STDOUT_FILENO);
            break;
        }
        close(pp[0]);
        close(pp[1]);
    }
}

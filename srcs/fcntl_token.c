#include "../includes/minishell.h"


// void    fdgs_init(t_fdgs *fdgs)
// {

// }

void execute_heredoc(int gfd[2], t_token *list, int exit_code, t_env *env)
{
    char *input;

    while(1)
    {
        input = readline("> ");
        if(input == NULL)
        {
            x_close(gfd[0]);
            free(input);
            break;
        }
        if(ft_strncmp(input, list->token, ft_strlen(list->token)) == 0
                && ft_strlen(input) == ft_strlen(list->token))
        {
            free(input);
            break;
        }
        input = expand_variable(input, 1, exit_code, env);
        write(gfd[0], input, ft_strlen(input));
        write(gfd[0], "\n", 1);
        free(input);
    }
}

void   fcntl_token(t_fdgs *fdgs, t_token *list, int exit_code, t_env *env)
{
    switch(list->type)
    {
        case TRUNCOUTFILE:
            fdgs->gfd[1] = x_open(list->token, O_TRUNC | O_CREAT | O_RDWR, 0644);
            break;
        case APNDOUTFILE:
            fdgs->gfd[1] = x_open(list->token, O_APPEND | O_CREAT | O_RDWR, 0644);
            break;
        case INFILE:
            fdgs->gfd[0] = x_open(list->token, O_RDONLY, 0);
            break;
        case HEREDOC:
            fdgs->gfd[0] = x_open("/tmp/sh-thd-tekitou", O_TRUNC | O_RDWR | O_CREAT, 0644);
            execute_heredoc(fdgs->gfd, list, exit_code, env);
            break;
        default:
            break;
    }
}

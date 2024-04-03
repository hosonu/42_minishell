#include "../includes/minishell.h"

void execute_heredoc(int gfd[2], t_token *list)
{
    char *input;

    input = NULL;
    while(1)
    {
        input = readline("> ");
        if(input == NULL)
        {
            close(gfd[0]);
            free(input);
            break;
        }
        if(ft_strncmp(input, list->token, ft_strlen(list->token)) == 0)
        {
            free(input);
            break;
        }
        input = expand_variable(input);
        write(gfd[0], input, ft_strlen(input));
        write(gfd[0], "\n", 1);
        free(input);
    }
}

void   fctl_token(int gfd[2], t_token *list)
{
    switch(list->type)
    {
        case TRUNCOUTFILE:
            gfd[1] = open(list->token, O_TRUNC | O_CREAT | O_RDWR, 0644);
            break;
        case APNDOUTFILE:
            gfd[1] = open(list->token, O_APPEND | O_CREAT | O_RDWR, 0644);
            break;
        case INFILE:
            gfd[0] = open(list->token, O_RDONLY);
            break;
        case HEREDOC:
            gfd[0] = open("/tmp/sh-thd-tekitou", O_RDWR | O_CREAT, 0644);
            execute_heredoc(gfd, list);
            break;
        default:
            break;
    }
}

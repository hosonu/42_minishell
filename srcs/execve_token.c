#include "../includes/minishell.h"

char *join_path(char *comand, char *path)
{
    path = ft_strjoin(path, "/");
    if(path == NULL)
        error_and_exit("malloc");
    path = ft_strjoin(path, comand);
    if(path == NULL)
        error_and_exit("malloc");
    return path;
}

char *path_lookup(char *comand, char **envi)
{
    int i;
    char **path;

    i = 0;
    while(envi[i] != NULL)
    {
        if(ft_strncmp(envi[i], "PATH=", 5) == 0)
        {
            path = ft_split(envi[i] + 5, ':');
            i = 0;
            while(path[i] != NULL)
            {
                path[i] = join_path(comand, path[i]);
                if(access(path[i], X_OK) == 0)
                    return path[i];
                free(path[i]);
                i++;
            }
        }
        i++;
    }
    return (NULL);
}

//TODO: error handling for access
// void    execve_token(t_token *list, t_status *status)
void    execve_token(char **tokens_splited)
{
    extern char **environ;
    // char **tokens_splited;
    char *comands;
    int i;

    i = 0;
    
    while(tokens_splited[i] != NULL)
    {
        if(access(tokens_splited[i], X_OK) == 0)
            x_execve(tokens_splited[i], tokens_splited, environ);
        else
        {
            comands = path_lookup(tokens_splited[i], environ);
            x_execve(comands, tokens_splited, environ);
        }
        i++;
    }
}

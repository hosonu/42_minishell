#include "../includes/minishell.h"

int    check_argc(char **str)
{
    int cnt;

    cnt = 0;
    while(str[cnt] != NULL)
    {
        cnt++;
    }
    return cnt;
}

//have a space to fix
int check_builtins(char **tokens_splited, t_env *env)
{
    if(ft_strncmp("echo", tokens_splited[0], ft_strlen(tokens_splited[0])) == 0)
    {
        ft_echo(check_argc(tokens_splited), tokens_splited);
        return 0;
    }
    else if(ft_strncmp("cd", tokens_splited[0], ft_strlen(tokens_splited[0])) == 0)
    {
        ft_cd(tokens_splited + 1, env);
        return 0;
    }
    else if(ft_strncmp("pwd", tokens_splited[0], ft_strlen(tokens_splited[0])) == 0)
    {
        ft_pwd(tokens_splited, env);
        return 0;
    }
    else if(ft_strncmp("export", tokens_splited[0], ft_strlen(tokens_splited[0])) == 0)
    {
        ft_export(tokens_splited + 1, env);
        return 0;
    }
    else if(ft_strncmp("unset", tokens_splited[0], ft_strlen(tokens_splited[0])) == 0)
    {
        ft_unset(tokens_splited + 1, env);
        return 0;
    }
    else if(ft_strncmp("env", tokens_splited[0], ft_strlen(tokens_splited[0])) == 0)
    {
        ft_env(env);
        return 0;
    }
    else if(ft_strncmp("exit", tokens_splited[0], ft_strlen(tokens_splited[0])) == 0)
        return 0;
    else
        return -1;
}

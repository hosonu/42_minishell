#include "../includes/minishell.h"

char    *get_expanded_env(char *env)
{
    int i;
    i = 0;
    while(env[i] != '=')
        i++;
    return env + i + 1;
}

size_t get_len_env(char *envi)
{
    size_t len;
    len = 0;
    while(envi[len] != '=')
        len++;
    return len;
}

//TODO: free trimed_input
char    *check_and_expand(int index, char *input, char **envi)
{
    int i;
    int j;
    char *trimmed_input;

    j = index;
    while(ft_isalnum(input[j + 1]) != 0)
        j++;
    trimmed_input = ft_substr(input, index + 1, j - index);
    i = 0;
    while(envi[i] != NULL)
    {
        if(ft_strncmp(envi[i], trimmed_input, ft_strlen(trimmed_input)) == 0 
            && ft_strlen(trimmed_input) == get_len_env(envi[i]))
            break;
        i++;
    }
    if(envi[i] != NULL)
        return (get_expanded_env(envi[i]));
    else
        return(NULL);
}

char *change_input(char *expanded_in, char *original_in, int index)
{
    char *after_symbol;
    char *before_symbol;
    char *change_in;

    before_symbol = ft_substr(original_in, 0, index);
    while(ft_isalnum(original_in[index + 1]) != 0)
        index++;
    after_symbol = ft_substr(original_in, index + 1, ft_strlen(original_in)- index + 1);
    change_in = ft_strjoin(before_symbol, expanded_in);
    change_in = ft_strjoin(change_in, after_symbol);
    return change_in;
}

char *expand_variable(char *input, int heredoc)
{
    extern char **environ;
    char *expanded_input;
    int i;
    int unexpand;

    i = 0;
    unexpand = 0;
    while(input[i] != '\0')
    {
        
        if(is_quote(input[i]) == 1 && unexpand == 0 && heredoc == 1)
            unexpand = 2;
        if(is_quote(input[i]) == 2 && unexpand == 0 && heredoc == 1)
            unexpand = 1;
        if(input[i] == '$' && unexpand != 1)
        {
            expanded_input = check_and_expand(i, input, environ);
            input = change_input(expanded_input, input, i);
            i += ft_strlen(expanded_input) - 1;
        }
        i++;
    }
    return input;
}

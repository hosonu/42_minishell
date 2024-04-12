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
// ft_substr func
char    *check_and_expand(int index, char *input, t_env *env)
{
    int i;
    int j;
    char *trimmed_input;

    j = index;
    while(ft_isalnum(input[j + 1]) != 0)
        j++;
    trimmed_input = ft_substr(input, index + 1, j - index);//TODO: error handling?
    i = 0;
    // while(envi[i] != NULL)
    // {
    //     if(ft_strncmp(envi[i], trimmed_input, ft_strlen(trimmed_input)) == 0 
    //         && ft_strlen(trimmed_input) == get_len_env(envi[i]))
    //         break;
    //     i++;
    // }
    // free(trimmed_input);//get_env
    // if(envi[i] != NULL)
    //     return (get_expanded_env(envi[i]));
    trimmed_input = ft_getenv(env, trimmed_input);
    return(trimmed_input);
}

char *change_input(char *expanded_in, char *original_in, int index)
{
    char *after_symbol;
    char *before_symbol;
    char *change_in;

    before_symbol = ft_substr(original_in, 0, index);
    while(ft_isalnum(original_in[index + 1]) != 0)
        index++;
    if(original_in[index + 1] == '?')
        index++;
    after_symbol = ft_substr(original_in, index + 1, ft_strlen(original_in)- index + 1);
    change_in = ft_strjoin(before_symbol, expanded_in);
    change_in = ft_strjoin(change_in, after_symbol);
    return change_in;
}

char *expand_variable(char *input, int heredoc, int exit_code, t_env *env)
{
    char *expanded_input;
    int i;
    int unexpand;

    i = 0;
    unexpand = 0;
    while(input[i] != '\0')
    {
        if(is_quote(input[i]) == 1 && heredoc == 0)
            unexpand += 2;
        if(is_quote(input[i]) == 2 && heredoc == 0  && unexpand != 2)
            unexpand += 1;
        if(input[i] == '$' && unexpand % 2 == 0 && input[i + 1] != '\0')
        {
            expanded_input = check_and_expand(i, input, env);
            if(input[i + 1] == '?')
            {
                expanded_input = ft_itoa(exit_code);
            }
            input = change_input(expanded_input, input, i);
            i += ft_strlen(expanded_input) - 1;
        }
        i++;
    }
    return input;
}

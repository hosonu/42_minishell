#include "../includes/minishell.h"

char *remove_specific_quote(char *token, int *i, int *quote_status)
{
    char *new_token;

    token[*i] = '\0';
    new_token = ft_strjoin(token, token + *i + 1);
    *i -= 1;
    *quote_status += 1;
    return new_token;
}

char *remove_quote(char *token)
{
    int i;
    int quoted;
    int dblquoted;
    int quote_type;

    i = 0;
    quoted = 0;
    dblquoted = 0;
    while (token[i] != '\0')
    {
        quote_type = is_quote(token[i]);
        if (quote_type == 1 && dblquoted % 2 == 0)
        {
            token = remove_specific_quote(token, &i, &quoted);
        }
        else if (quote_type == 2 && quoted % 2 == 0)
        {
            token = remove_specific_quote(token, &i, &dblquoted);
        }
        i++;
    }
    return token;
}

void    handle_token(char **splited_token)
{
    int i;

    i = 0;
    while(splited_token[i] != NULL)
    {
        splited_token[i] = expand_variable(splited_token[i], 0);
        splited_token[i] = remove_quote(splited_token[i]);
        i++;
    }
}

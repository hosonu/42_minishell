#include "../includes/minishell.h"

void    validate_token(char *token)
{
    int i;
    int dblquotation;
    
    i = 0;
    dblquotation = 0;
    while(token[i] != '\0')
    {
        if(is_quote(token[i]) == 1)
            dblquotation++;
        
    }
}


void    handle_token(char **splited_token)
{
    int i;

    i = 0;
    while(splited_token[i] != NULL)
    {
        if(is_quote(splited_token[i]) > 0)
            is_quote = 1;
        if(is_quote == 1)
        {
            if(splited_token[i] == '$')

        }
        i++;
    }
}
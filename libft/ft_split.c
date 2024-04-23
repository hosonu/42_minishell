/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan < kojwatan@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:45:37 by kojwatan          #+#    #+#             */
/*   Updated: 2023/09/28 20:22:52 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t count_words(const char *s, char c)
{
    size_t words;
    int quoted;
    int dblquoted;

    words = 1;
    quoted  = 0;
    dblquoted  = 0;
    while (*s)
    {
        if (*s == '"' && quoted % 2 == 0)
            dblquoted += 1;
        else if(*s == '\'' && dblquoted % 2 == 0)
            quoted += 1;
        else if ((dblquoted % 2 == 0 && quoted % 2 == 0) && *s == c)
            words++;
        s++;
    }
    return words;
}

static size_t strlen_c(char const *s, char c)
{
    size_t len;
    int quoted;

    len = 0;
    quoted = 0;
    while (s[len])
    {
        if (s[len] == '\'' && (quoted == 0 || quoted == 1))
        {
            if (quoted == 1)
                quoted = 0;
            else
                quoted = 1;
        }
        else if (s[len] == '"' && (quoted == 0 || quoted == 2))
        {
            if (quoted == 2)
                quoted = 0;
            else
                quoted = 2;
        }
        else if (quoted == 0 && s[len] == c)
            break;
        len++;
    }
    return len;
}

char     **get_arr(char const *s, char c, size_t words, char **arr)
{
        size_t  i;

        i = 0;
        while (words--)
        {
            while (*s == c || *s == '\0')
                s++;
            arr[i] = ft_substr(s, 0, strlen_c(s, c));
            if (arr[i] == NULL)
            {
                while (i > 0)
                {
                    free(arr[i]);
                    i--;
                }
                if (arr[i] != NULL)
                        free(arr[i]);
                free(arr);
                return (NULL);
            }
            i++;
            s += strlen_c(s, c);
        }
        return (arr);
}

char **ft_split(char const *s, char c)
{
    char **arr;
    size_t words;

    if (s == NULL)
        return NULL;
    words = count_words(s, c);
    arr = malloc(sizeof(char *) * (words + 1));
    if (arr == NULL)
	{
    	return NULL;
	}
	arr[words] = 0;
    arr = get_arr(s, c, words, arr);
	return arr;
}

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

// static int	count_words(char const *s, char c)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	if (s[i] == 0)
// 		return (0);
// 	while (s[i] == c)
// 		i++;
// 	count = s[i] != 0;
// 	while (s[i] != '\0')
// 	{
// 		while (s[i] != c && s[i])
// 			i++;
// 		while (s[i] == c && s[i])
// 			i++;
// 		if (s[i] != '\0')
// 		{
// 			i++;
// 			count++;
// 		}
// 	}
// 	ft_printf("%d\n", count);
// 	return (count);
// }

// static void	free_all(char **strs, int i)
// {
// 	while (i > 0)
// 	{
// 		free(strs[i]);
// 		i--;
// 	}
// 	free(strs[i]);
// }

// static char	**split_alloc(char **strs, char *str, char c, int end)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (i < end)
// 	{
// 		count = 0;
// 		while (*str == c)
// 			str++;
// 		while (*str != c && *str)
// 		{
// 			str++;
// 			count++;
// 		}
// 		strs[i] = (char *)malloc(count + 1);
// 		if (strs[i] == NULL)
// 		{
// 			free_all(strs, i);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	strs[i] = 0;
// 	return (strs);
// }

// char	**split_help(char **strs, char *s, char c)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (strs[i])
// 	{
// 		while (*s == c)
// 			s++;
// 		if (*s == 0)
// 			break ;
// 		while (*s != c && *s)
// 			strs[i][j++] = *(s++);
// 		strs[i++][j] = 0;
// 		j = 0;
// 	}
// 	return (strs);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**strs;

// 	if (s == NULL)
// 		return (NULL);
// 	strs = malloc(sizeof(char *) * (count_words(s, c) + 1));
// 	if (strs == NULL)
// 		return (NULL);
// 	strs = split_alloc(strs, (char *)s, c, count_words(s, c));
// 	if (strs == NULL)
// 		return (NULL);
// 	return (split_help(strs, (char *)s, c));
// }

// static size_t   separator(char s, char sep)
// {
//         if (s == sep)
//                 return (1);
//         if (s == '\0')
//                 return (1);
//         return (0);
// }

// static size_t   count_words(const char *s, char c)
// {
//         size_t  words;
//         size_t  i;
//         size_t quoted;
//         size_t doquoted;

//         i = 0;
//         words = 0;
//         quoted = 0;
// 		doquoted = 0;
//         while (s[i] != '\0')
//         {
//         	if(s[i] == '\"' && quoted == 0)
//             {
//                 doquoted++;
//                 if(doquoted % 2 == 0)
// 		        {
//                     words++;
// 					doquoted = 0;
// 				}
//             }
//             else if(s[i] == '\'' && doquoted == 0)
// 			{
// 				quoted++;
//                 if(quoted % 2 == 0)
// 				{
//                     words++;
// 					quoted = 0;
// 				}
// 			}
//             else if (separator(s[i], c) == 0 && separator(s[i + 1], c) == 1 && quoted % 2 == 0 && doquoted % 2 == 0)
//                 words++;
//             i++;
//         }
//         return (words);
// }

// static size_t   strlen_c(char const *s, char c)
// {
//         size_t  len;

//         len = 0;
//         if(s[len] == '"')
//         {
//             len++;
//             while(s[len] != '"')
//                 len++;
//             return len + 1;
//         }
//         else if(s[len] == '\'')
//         {
//             len++;
//             while(s[len] != '\'')
// 			    len++;
//             return len + 1;
//         }
//         else
//         {
//             while (separator(s[len], c) == 0)
//                 len++;
//         }
//         return (len);
// }

// static char     **get_arr(char const *s, char c, size_t words, char **arr)
// {
//         size_t  i;

//         i = 0;
//         while (words--)
//         {
//                 if(*s != '"' || *s != '\'')
//                 {
//                     while (separator(*s, c) == 1)
//                 	    s++;
//                 }
//                 arr[i] = ft_substr(s, 0, strlen_c(s, c));
//                 if (arr[i] == NULL)
//                 {
//                         while (i > 0)
//                         {
//                             free(arr[i]);
//                             i--;
//                         }
//                         if (arr[i] != NULL)
//                             free(arr[i]);
//                         free(arr);
//                         return (NULL);
//                 }
//                 i++;
//                 s += strlen_c(s, c);
//         }
//         return (arr);
// }

// char    **ft_split(char const *s, char c)
// {
//         char    **arr;
//         size_t  words;

//         if (s == NULL)
//                 return (NULL);
//         words = count_words(s, c);
//         if (words == SIZE_MAX)
//                 return (NULL);
//         arr = (char **)malloc(sizeof(char *) * (words + 1));
//         if (arr == NULL)
//                 return (NULL);
//         arr[words] = 0;
//         arr = get_arr(s, c, words, arr);
//         return (arr);
// }


static size_t count_words(const char *s, char c) {
    size_t words = 0;
    int in_word = 0;
    int quoted = 0;

    while (*s) {
        if (*s == '\'' || *s == '"')
            quoted = !quoted;
        else if (!quoted && *s == c)
            in_word = 0;
        else if (!in_word && *s != c) {
            in_word = 1;
            words++;
        }
        s++;
    }
    return words;
}

static size_t   strlen_c(char const *s, char c)
{
    size_t len = 0;
    int quoted = 0;

    while (s[len])
    {
        if (s[len] == '\'' || s[len] == '"')
            quoted = !quoted;
        else if (!quoted && s[len] == c)
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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>


size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	if (s == NULL || s[length] == 0)
		return (0);
	while (s[length])
		length++;
	return (length);
}

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		i;

	dest = malloc(ft_strlen((char *)s1) + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}



char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned char	*substr;
	size_t			i;

	i = 0;
	if (s == NULL || len == 0)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len < ft_strlen(&s[start]))
		substr = malloc(len + 1);
	else
		substr = malloc(ft_strlen(&s[start]) + 1);
	if (substr == NULL)
		return (NULL);
	while (i < len)
	{
		if (s[start])
			substr[i++] = s[start++];
		else
			break ;
	}
	substr[i] = 0;
	return ((char *)(substr));
}


// int	is_quote(char c)
// {
// 	if (c == '\"')
// 		return (1);
// 	else if (c == '\'')
// 		return (2);
// 	else
// 		return 0;
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

//         i = 0;
//         words = 0;
//         quoted = 0;
//         while (s[i] != '\0')
//         {
//                 if(is_quote(s[i]) > 0)
//                 {
//                     quoted++;
//                     if(quoted % 2 == 0)
//                         words++;
//                 }
//                 else if (separator(s[i], c) == 0 && separator(s[i + 1], c) == 1 && quoted % 2 == 0)
//                         words++;
//                 i++;
//         }
//         return (words);
// }


static size_t   separator(char s, char sep)
{
        if (s == sep)
                return (1);
        if (s == '\0')
                return (1);
        return (0);
}

// static size_t   count_words(const char *s, char c)
// {
//         size_t  words;
//         size_t  i;
//         size_t quoted;
//         size_t doquoted;

//         i = 0;
//         words = 0;
//         quoted = 0;
// 	doquoted = 0;
//         while (s[i] != '\0')
//         {
//                 if(s[i] == '\"' && quoted == 0)
//                 {
//                         doquoted++;
//                         if(doquoted % 2 == 0)
// 		        {
//                                 words++;
// 				doquoted = 0;
// 			}
//                 }
//                 else if(s[i] == '\'' && doquoted == 0)
// 		{
// 			quoted++;
//                         if(quoted % 2 == 0)
// 			{
//                                 words++;
// 				quoted = 0;
// 			}
// 		}
//                 else if (separator(s[i], c) == 0 && separator(s[i + 1], c) == 1 && quoted % 2 == 0 && doquoted % 2 == 0)
//                 {
//                         words++;
//                 }
//                 i++;
//         }
//         printf("%ld\n", words);
//         return (words);
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
        // size_t  len;
        // int is_quoted = 0;

        // len = 0;
        // if(s[len] == '"')
        // {
        //         len++;
        //         while(s[len] != '"')
        //                 len++;
        //         return len + 1;
        // }
        // else if(s[len] == '\'')
        // {
        //         len++;
        //         while(s[len] != '\'')
        //                 len++;
        //         return len + 1;
        // }
        // else
        // {
        //         while (s[len] != '\0')
        //         {
        //                 if (s[len] == '\'' || s[len] == '"')
        //                         is_quoted = !is_quoted;
        //                 if(s[len] == c && is_quoted == 0)
        //                         break;
        //                 len++;
        //         }
        // }
        // static size_t strlen_c(const char *s, char c) {
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

static char     **get_arr(char const *s, char c, size_t words, char **arr)
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

char    **ft_split(char const *s, char c)
{
        char    **arr;
        size_t  words;

        if (s == NULL)
                return (NULL);
        words = count_words(s, c);
        if (words == SIZE_MAX)
                return (NULL);
        arr = (char **)malloc(sizeof(char *) * (words + 1));
        if (arr == NULL)
                return (NULL);
        arr[words] = 0;
        arr = get_arr(s, c, words, arr);
        return (arr);
}

int main()
{
    char **str;

    str = ft_split("echo jsa\"$    PATH      \"sda  ada ", ' ');
    str = ft_split("echo jsa\"$\'PA\'TH\"sda", ' ');
    str = ft_split("echo \"fakdja     \"", ' ');
    str = ft_split("echo \"dajkla   \'daskl\'\"", ' ');

}

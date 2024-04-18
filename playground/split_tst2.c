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


int main() {
    char **str;
    // str = ft_split("echo jsa\"$    PATH      \"sda  ada ", ' ');
    str = ft_split("echo \"fak\'  dja\'     \"", ' ');
    int i = 0;
    while (str[i] != NULL)
        {
        printf("str[%d] = %s\n", i, str[i]);
        i++;
    }
    // str[0] = "echo"
    // str[1] = "jsa\"$PATH\"sda"
    // str[2] = NULL
    return 0;
}
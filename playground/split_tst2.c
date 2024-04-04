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


static int is_quote(char c)
{
    return (c == '\'' || c == '"');
}

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
    printf("%ld\n", words);
    return words;
}

static size_t strlen_c(const char *s, char c) {
    size_t len = 0;
    int quoted = 0;

    while (*s) {
        if (*s == '\'' || *s == '"')
            quoted = !quoted;
        else if (!quoted && *s == c)
            break;
        len++;
        s++;
    }
    return len;
}

static char **get_arr(char const *s, char c, size_t words, char **arr) {
    size_t i = 0;
    int quoted = 0;

    while (words--) {
        while (*s == c)
            s++;
        if (*s == '\'' || *s == '"')
            quoted = !quoted;
        arr[i] = malloc(strlen_c(s, c) + 1);
        if (arr[i] == NULL) {
            while (i > 0) {
                free(arr[i - 1]);
                i--;
            }
            free(arr);
            return NULL;
        }
        size_t j = 0;
        while (*s && (*s != c || quoted)) {
            if (*s == '\'' || *s == '"')
                quoted = !quoted;
            arr[i][j++] = *s++;
        }
        arr[i][j] = '\0';
        printf("%s\n", arr[i]);
        i++;
    }
    arr[i] = NULL;
    return arr;
}

char **ft_split(char const *s, char c) {
    char **arr;
    size_t words;

    if (s == NULL)
        return NULL;
    words = count_words(s, c);
    arr = malloc(sizeof(char *) * (words + 1));
    if (arr == NULL)
        return NULL;
    arr = get_arr(s, c, words, arr);
    return arr;
}

int main() {
    char **str;
    str = ft_split("echo jsa\"$    PATH      \"sda  ada ", ' ');
    str = ft_split("echo \"fakdja     \"", ' ');
    // str[0] = "echo"
    // str[1] = "jsa\"$PATH\"sda"
    // str[2] = NULL
    return 0;
}
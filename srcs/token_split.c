#include "../includes/minishell.h"

static int	count_words(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	if (s[i] == 0)
		return (0);
	while (s[i] == c)
		i++;
	count = (is_metachar(s[i]) != 1);
	while (s[i])
	{
		while ((s[i] != c && is_metachar(s[i]) == -1 && s[i]) || is_quoted(s, &s[i]) == 1)
			i++;
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			count++;
			if (is_metachar(s[i]) == 1)
			{
				while (is_metachar(s[i]) == 1)
					i++;
				if (s[i] != '\0' && s[i] != ' ')
					count++;
			}
		}
	}
	return (count);
}

static void	free_all(char **strs, int i)
{
	while (i > 0)
	{
		free(strs[i]);
		i--;
	}
	free(strs[i]);
}

static char	**split_alloc(char **strs, char *str, char c, int end)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (i < end)
	{
		count = 0;
		while (str[j] == c)
			j++;
		while (((str[j] != c && is_metachar(str[j]) == -1) || is_quoted(str, &str[j]) == 1 )&& str[j])
		{
			j++;
			count++;
		}
		if (count == 0)
		{
			while (is_metachar(str[j]) == 1)
			{
				j++;
				count++;
			}
		}
//		printf("split_alloc count %d\n", count);
		strs[i] = (char *)malloc(count + 1);
		ft_memset(strs[i], 40, count + 1);
		if (strs[i] == NULL)
		{
			free_all(strs, i);
			return (NULL);
		}
		strs[i][count] = '\0';
		i++;
	}
//	printf("split_alloc end\n");
	strs[i] = NULL;
	return (strs);
}

static char	**split_help(char **strs, char *s)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (strs[i])
	{
		j = 0;
		while (s[k] == ' ' && is_quoted(s, &s[k]))
			k++;
		while (strs[i][j] != '\0')
			strs[i][j++] = s[k++];
		i++;
	}
	return (strs);
}

char	**token_split(char *s, char c)
{
	char	**strs;

	if (s == NULL)
		return (NULL);
	strs = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (strs == NULL)
		return (NULL);
	strs = split_alloc(strs, (char *)s, c, count_words(s, c));
	if (strs == NULL)
		return (NULL);
	return (split_help(strs, (char *)s));
}

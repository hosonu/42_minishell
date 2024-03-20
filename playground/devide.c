#include "../minishell.h"

t_token	*new_token(char *content)
{
	t_token	*new;

	if (content == NULL)
		return (NULL);
	new = malloc(sizeof(t_token));
	new->token = content;
	new->type = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*devide_file(char *str)
{
	int	len;
	int	start;
	char	*token;
	t_token	*new;

	len = 0;
	start = 0;
	while (str[start] == ' ')
		start++;
	while (str[start + len] != ' ')
		len++;
	token = ft_substr(str, start, len);
	new = new_token(token);
	return (new);
}

t_token	*devide_cmd(char *str)
{
	int	len;
	int	start;
	char	*token;
	t_token	*new;

	len = 0;
	start = 0;
	while (str[start] == ' ')
		start++;
	while (str[start] != ' ')
		start++;
	while (str[start] == ' ')
		start++;
	while (str[start + len] != '\0')
		len++;
	token = ft_substr(str, start, len);
	new = new_token(token);
	return (new);
}

int	main(int ac, char *av[])
{
	t_token	*file;
	t_token	*cmd;

	if (ac < 2)
		return 0;
	file = devide_file(av[1]);
	cmd = devide_cmd(av[1]);
	printf("%s\n", file->token);
	printf("%s\n", cmd->token);
}

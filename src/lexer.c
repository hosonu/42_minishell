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

t_token	*new_metatoken(char *str)
{
	int	start;
	int	len;
	t_token	*new;

	start = token_len(str);
	len = 0;
	if (start == (int)ft_strlen(str))
		return (NULL);
	while (str[start] == ' ')
		start++;
	while (is_metachar(str[start + len]) == 1)
		len++;
	new = new_token(ft_substr(str, start, len));
	return (new);
}

t_token	*lexer(char *str)
{
	char	*left;
	t_token	*top;
	t_token	*new;


	new = NULL;
	quotation_validate(str);
	top = new_token(tokenizer(str));
	if (top == NULL)
		top = new_metatoken(str);
	else
		new = new_metatoken(str);
	if (new != NULL)
		token_addlast(top, new);
	left = strdup_right(str);
	while (left != NULL)
	{
		new = new_token(tokenizer(left));
		if (new != NULL)
			token_addlast(top, new);
		new = new_metatoken(left);
		if (new != NULL)
			token_addlast(top, new);
		left = strdup_right(left);
	}
	return (top);
}

void	token_addlast(t_token *top, t_token *new)
{
	t_token	*lst;

	lst = top;
	while (lst->next != NULL)
		lst = lst->next;
	lst->next = new;
	new->prev = lst;
}

void	token_insert(t_token *node, t_token *new)
{
	new->next = node->next;
	node->next = new;
	new->prev = node;
}

void	token_destroy(t_token *node)
{
	node->next->prev = node->prev;
	node->prev->next = node->next;
	free(node->token);
	free(node);
}

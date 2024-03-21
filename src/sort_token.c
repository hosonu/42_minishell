#include "../minishell.h"

void	print_to(t_token **top)
{
	int	i;

	i = 0;
	while (top[i])
	{
		printf("%s\n", top[i]->token);
		i++;
	}
}

int	token_count(t_token *top)
{
	int	count;

	count = 0;
	while (top != NULL)
	{
		count++;
		top = top->next;
	}
	return (count);
}

t_token	**linear_token_list(t_token *top)
{
	t_token	**list;
	int	i;

	list = malloc(sizeof(t_token *) * (token_count(top) + 1));
	i = 0;
	while (top != NULL)
	{
		list[i] = top;
		i++;
		top = top->next;
	}
	list[i] = NULL;
	//print_to(list);
	return (list);
}

void	sort_token(t_token **list)
{
	int	i;
	t_token	*tmp;

	i = 0;
	while (list[i] != NULL)
	{
		//printf("AA\n");
		if (list[i + 1] != NULL)
		{
			//printf("BB\n");
			if (list[i]->type >= COMMAND && list[i + 1]->type < COMMAND && list[i + 1]->type != METAPIPE)
			{
				//printf("CC\n");
				tmp = list[i];
				list[i] = list[i + 1];
				list[i + 1] = tmp;
			}
		}
		i++;
	}
}

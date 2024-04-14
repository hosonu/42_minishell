#include "../../includes/minishell.h"

int	ft_exit(char *av[], int num)
{
	if (av[0] == NULL)
	{
		write(1, "exit\n", 5);
		exit(num);
	}
	else
	{
		num = atoi(av[0]);
		exit(num);
	}
	return (0);
}

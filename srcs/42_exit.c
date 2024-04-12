#include "../includes/minishell.h"


int	ft_exit(char *av[], int num)
{
	// uint8_t	num;

	if (av[0] == NULL)
		exit(num);
	else
	{
		num = atoi(av[0]);
		exit(num);
	}
	return (0);
}
/*
int	main(int ac, char *av[])
{
	uint8_t	num;

	if (ac < 2)
		return 1;
	num = atoi(av[1]);
	printf("%d\n", num);
	return 0;
}*/

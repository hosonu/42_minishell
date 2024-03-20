#include <stdio.h>

int	count_word(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		count++;
		while (str[i] != ' ' && str[i] != '\0')
			i++;
		while (str[i] == ' ' && str[i] != '\0')
			i++;
	}
	return (count);
}

int	main(int ac, char *av[])
{
	int	i;
	
	if (ac < 1)
		return 0;
	i = count_word(av[1]);
	printf("%d\n", i);
	return 0;
}

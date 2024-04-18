#include "../../includes/minishell.h"

pid_t x_fork(void)
{
    pid_t result;
    
    result = fork();
    if (result == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    return result;
}

void	*x_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
		perror("malloc");
	return (ret);
}

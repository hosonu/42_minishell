#include "../includes/minishell.h"

void    error_msg_for_cmd(const char *filename)
{
    write(2, filename, ft_strlen(filename));
    write(2, ": ", 2);
    write(2, "command not found\n", 18);
}

void    error_and_exit(const char *filename)
{
    perror(filename);
    exit(EXIT_FAILURE);
}

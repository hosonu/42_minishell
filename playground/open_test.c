#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int fd;

    fd = open("file",O_RDONLY, 0);
    if(fd == -1)
    {
        perror("open");
    }
    dup2(fd, STDIN_FILENO);
    // execve()
    
}
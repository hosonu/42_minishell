#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // $BASH_VERSION
    char *bash_version = getenv("BASH_VERSION");
    if (bash_version) {
        printf("BASH_VERSION: %s\n", bash_version);
    } else {
        printf("BASH_VERSION is not set\n");
    }

    // $1, $2, ...
    printf("Arguments:");
    for (int i = 1; i < argc; i++) {
        printf(" %s", argv[i]);
    }
    printf("\n");

    // $?
    int status;
    waitpid(-1, &status, 0);
    printf("Exit status: %d\n", status);
    printf("Exit status: %d\n", WEXITSTATUS(status));

    // $$
    printf("PID: %d\n", getpid());

    // $#
    printf("Argument count: %d\n", argc - 1);

    // $@
    printf("All arguments:");
    for (int i = 1; i < argc; i++) {
        printf(" %s", argv[i]);
    }
    printf("\n");

    return 0;
}
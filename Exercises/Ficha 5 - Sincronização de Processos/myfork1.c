#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    int v;
    printf("Initial process: %d\n", getpid());

    /* fork a child process */
    v = fork();
    if (v == 0) printf("Child: %d\n", getpid());

    /* fork another child process */
    v = fork();
    if (v == 0) printf("Child: %d\n", getpid());

    /* and fork another */
    v = fork();
    if (v == 0) printf("Child: %d\n", getpid());

    return EXIT_SUCCESS;
}
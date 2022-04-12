#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    /* fork a child process */
    fork();

    /* fork another child process */
    fork();

    /* and fork another */
    fork();
    
    return EXIT_SUCCESS;
}
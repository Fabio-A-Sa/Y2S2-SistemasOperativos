#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
 
int main(int argc, char* argv[]) {

    int v;
    printf("Initial process: %d\n", getpid());

    for (int i = 0; i < 4; i++) {
        v = fork();
        if (v == 0) printf("New process %d: %d\n", i, getpid());
    }

    // Total = 16 processes (2^4)
    return EXIT_SUCCESS;
}
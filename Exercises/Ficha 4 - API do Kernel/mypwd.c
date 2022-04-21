#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_SIZE 1024

int main (int args, char* argv[]) {

    char buffer[MAX_SIZE];
    getcwd(buffer, MAX_SIZE);
    printf("Current Directory: %s\n", buffer);

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>

void singleFile(char* argv[]) {

    char* file = argv[1];
    printf("Single file called %s!\n", file);
}

void twoFiles(char* argv[]) {

    char* file1 = argv[1];
    char* file2 = argv[2];
    printf("Double file called %s and %s!\n", file1, file2);
}


int main (int argc, char* argv[]) {

    if (argv[2] != NULL) twoFiles(argv); else singleFile(argv);
    return 0;
}
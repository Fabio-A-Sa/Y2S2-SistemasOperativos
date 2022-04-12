#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEW_PERMISSION 644 // rw,r,r

void touch(char* fileName) {

    FILE* file = fopen(fileName, "w");
    if (chmod(fileName, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        printf("unable to change permissions in %s file!\n", fileName);
    }
    fclose(file);
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "usage: %s <FILENAME>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int i = 1;
    while (argv[i] != NULL) {
        touch(argv[i]);
        i++;
    }

    return EXIT_SUCCESS;
}
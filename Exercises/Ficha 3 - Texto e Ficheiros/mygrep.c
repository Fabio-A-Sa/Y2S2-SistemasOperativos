#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 1024

int main (int args, char* argv[]) {

    char* word = argv[1];
    char* fileName = argv[2];

    if (word == NULL || fileName == NULL) {
        printf("Invalid input!\n");
        return -1;
    }

    

    return 0;
}
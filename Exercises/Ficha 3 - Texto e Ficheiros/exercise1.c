#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_SIZE  64

int main(int argc, char* argv[]) {
    
    char* string = (char*)malloc(MAX_STR_SIZE * sizeof(char));
    strcpy(string, argv[1]);

    printf("String %s\n", string);

    return 0;
}
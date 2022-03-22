#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STR_SIZE  64

int main(int argc, char* argv[]) {
    
    char* string = (char*)malloc(MAX_STR_SIZE * sizeof(char));
    strcpy(string, argv[1]);

    printf("Initial string: %s\n", string);

    for (char i = 0 ; i < strlen(string) ; i++) {
        *(string + i) = tolower( (unsigned char) *(string+i));
    }

    printf("Lower letters: %s\n", string);

    return 0;
}
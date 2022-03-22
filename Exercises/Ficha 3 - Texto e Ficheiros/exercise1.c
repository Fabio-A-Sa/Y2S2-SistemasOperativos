#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STR_SIZE  64

void toLowerCase(char* argv[]) {

    char* string = (char*)malloc(MAX_STR_SIZE * sizeof(char));
    strcpy(string, argv[1]);

    printf("Initial string: %s\n", string);

    for (char i = 0 ; i < strlen(string) ; i++) {
        *(string + i) = tolower( (unsigned char) *(string+i));
    }

    printf("Lower letters: %s\n", string);
}

void ocorre(char* argv[]) {

    char *string1 = (char*)malloc(MAX_STR_SIZE * sizeof(char));
    char *string2 = (char*)malloc(MAX_STR_SIZE * sizeof(char));
    strcpy(string1, argv[1]);
    strcpy(string2, argv[2]);

    printf("Initial strings: '%s' and '%s'\n", string1, string2);

    char* result = strstr(string2, string1);

    if (result == NULL) {
        printf("Not found!\n");
    } else {
        printf("Found!\n");
    }
}

int main(int argc, char* argv[]) {
    
    toLowerCase(argv);
    ocorre(argv);

    return 0;
}
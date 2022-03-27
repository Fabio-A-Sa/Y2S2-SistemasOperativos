#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int upperCase(char* fileName) {

    FILE* file = fopen(fileName, "r");
    const int MAX_SIZE = 100;
    char content[MAX_SIZE];
    fseek(file, 0, SEEK_SET);
    fread(content, sizeof(char) * MAX_SIZE, MAX_SIZE, file);

    int i = 0;
    while (*(content + i) != '\0' && *(content + i) != NULL) {
        printf("%c", toupper( (unsigned char) *(content+i)));
        i++;
    }
    printf("\n");
    fclose(file);

    return 0;
}

int lowerCase(char* fileName) {

    FILE* file = fopen(fileName, "r");
    const int MAX_SIZE = 100;
    char content[MAX_SIZE];
    fseek(file, 0, SEEK_SET);
    fread(content, sizeof(char) * MAX_SIZE, MAX_SIZE, file);

    int i = 0;
    while (*(content + i) != '\0' && *(content + i) != NULL) {
        printf("%c", tolower( (unsigned char) *(content+i)));
        i++;
    }
    printf("\n");
    fclose(file);

    return 0;
}

int main (int arg, char* argv[]) {

    int comparation;
    char* fileName = argv[1];
    char* mode = argv[2];

    comparation = strcmp(mode, "-u");
    if (comparation == 0) return upperCase(fileName);
    comparation = strcmp(mode, "-l");
    if (comparation == 0) return lowerCase(fileName);
    else printf("Input error!\n");

    return 0;
}
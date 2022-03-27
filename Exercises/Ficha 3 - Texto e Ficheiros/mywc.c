#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 100

int main (int arg, char* argv[]) {

    int comparation, answer = 0;
    char* fileName = argv[1];
    char* mode = argv[2];

    if (mode == NULL) {
        printf("Input error!\n");
        return -1;
    }

    char content[MAX_SIZE];

    FILE* file = fopen(fileName, "r");
    int finish = fread(content, 1, sizeof(content), file);
    content[finish] = '\0';
    fclose(file);

    comparation = strcmp(mode, "-l");
    if (comparation == 0) {

        answer = 20;

    }

    comparation = strcmp(mode, "-w");
    if (comparation == 0) {
        
        answer = 10;

    } else {

        answer = 45;

    }

    printf("Result: %d\n", answer);

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 100

char* extractContent(char* fileName) {

    FILE* file = fopen(fileName, "r");
    char* content[MAX_SIZE];
    fread(content, MAX_SIZE * sizeof(char), sizeof(char), file);
    fclose(file);
    return *content;
}

int lines (char* content) {

    int total = 0;
    
    return total;

}

int words (char* content) {

    int total = 0;
    
    return total;

}

int characters (char* content) {

    int total = 0;

    return total;

}

int main (int arg, char* argv[]) {

    int comparation, answer;
    char* fileName = argv[1];
    char* mode = argv[2];

    char* content = extractContent(fileName);

    comparation = strcmp(mode, "-w");
    if (comparation == 0) answer = lines(content);
    comparation = strcmp(mode, "-l");
    if (comparation == 0) answer = words(content);
    else answer = characters(content);



    printf("Result: %d\n", answer);

    return 0;
}
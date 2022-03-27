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

    char content[MAX_SIZE];
    FILE* file = fopen(fileName, "r");
    int finish = fread(content, sizeof(char), MAX_SIZE, file);
    fclose(file);
    content[finish] = '\0';

    printf("Finish: %d\n", finish);

    int index = 0, line = 0;
    while (index != finish) {
        
        char currentLine[MAX_SIZE]; 
        while (content[index] != '\n' && index <= finish) {
            currentLine[index] = content[index];
            index++;
            printf("Index counter: %d\n", index);
        }
        currentLine[index] = '\0';

        if (strstr(word, currentLine) != NULL) {
            printf("Ocorre na linha %d\n", line);
        } else printf("Não ocorre na linha %d\n", line);

        line++;
    }

    return 0;
}
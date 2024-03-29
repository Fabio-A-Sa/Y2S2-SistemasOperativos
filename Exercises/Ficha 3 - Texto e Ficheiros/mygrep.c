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

    /* Output
    printf("Finish: %d\n", finish);
    printf("Content: %s\n", content);
    */

    char currentLine[MAX_SIZE];
    int i = 0, line = 0;

    for (int index = 0 ; index <= finish ; index++) {

        if (content[index] == '\n') {

            currentLine[i] = '\0';
            i = 0;
            char* result = strstr(currentLine, word);

            /* Output
            printf("Linha %d: %s\n", line, currentLine);
            if (result != NULL) {
                printf("%s ocorre na linha %d\n\n", word, line);
            } else printf("%s não ocorre na linha %d\n\n", word, line);
            */

            if (result != NULL) {
                printf("[%d:%d]\n", line, index);
            }

            line++;

        } else {
            currentLine[i] = content[index];
            i++;
        }
    }

    return 0;
}
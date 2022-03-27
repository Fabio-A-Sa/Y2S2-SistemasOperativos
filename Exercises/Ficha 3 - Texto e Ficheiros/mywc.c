#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 1024

int main (int arg, char* argv[]) {

    int answer = 0, index = 0;
    char* fileName = argv[1];
    char* mode = argv[2];

    if (mode == NULL) {
        printf("Input error!\n");
        return -1;
    }

    char content[MAX_SIZE];

    FILE* file = fopen(fileName, "r");
    int finish = fread(content, 1, sizeof(content), file);
    fclose(file);

    if (strcmp(mode, "-l") == 0) {

        while (index != finish) {
            if (content[index] == '\n') answer++;
            index++;
        }

    } else if (strcmp(mode, "-w") == 0) {
        
        while (index != finish) {
            if (content[index] == ' ' || content[index] == '\n') answer++;
            index++;
        } answer++;

    } else {
        answer = finish;
    }

    printf("Content: %s\n", content);
    printf("Result: %d\n", answer);

    return 0;
}
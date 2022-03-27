#include <stdio.h>
#include <stdlib.h>

void showFile(char* fileName) {

    FILE* file = fopen(fileName, "r");
    const int MAX_SIZE = 100;
    char content[MAX_SIZE];
    fseek(file, 0, SEEK_SET);
    int finish = fread(content, sizeof(char) * MAX_SIZE, MAX_SIZE, file);
    content[finish] = '\0';

    int i = 0;
    while (*(content + i) != '\0') {
        printf("%c", *(content + i));
        i++;
    } printf("\n");
    
    fclose(file);
}

int main (int argc, char* argv[]) {

    int i = 1;
    while (argv[i] != NULL) {
        showFile(argv[i]);
        i++;
    }

    return 0;
}
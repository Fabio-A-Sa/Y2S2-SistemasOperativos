#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void createFile (char* fileName) {
    FILE* file = fopen(fileName, "w");
    fclose(file);
}

void copyFiles (char* fileName1, char* fileName2) {

    FILE* file1 = fopen(fileName1, "a");
    FILE* file2 = fopen(fileName2, "r");

    char* content[100];
    fread(content, sizeof(content), sizeof(char), file1);
    fwrite(content, sizeof(content), sizeof(char), file2);

    fclose(file1);
    fclose(file2);
}

int main (int arg, char* argv[]) {

    char* file1 = argv[1];
    char* file2 = argv[2];

    if (file1 == NULL) {
        printf(" $ ./a.out <file1> [file2]\n");
    } else if (file2 == NULL) {
        char* newName = "copy.txt";
        createFile(newName);
        file2 = newName;
    }

    copyFiles(file1, file2);

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 100

void createFile (char* fileName) {
    FILE* file = fopen(fileName, "w");
    fclose(file);
}

void copyFiles (char* fileName1, char* fileName2) {

    FILE* file1 = fopen(fileName1, "r");
    FILE* file2 = fopen(fileName2, "a");

    char content[MAX_SIZE];
    int final = fread(content, sizeof(char), MAX_SIZE, file1);
    char toWrite[final];
    
    fwrite(content, final, sizeof(char), file2);

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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define CYPHER "cypher.txt"
#define MAX_BUFFER_SIZE 1024
#define MAX_WORD_SIZE 30
#define MAX_WORDS_PER_LINE 10
#define READ 0
#define WRITE 1

size_t size = MAX_BUFFER_SIZE + MAX_WORD_SIZE * MAX_WORDS_PER_LINE;

char* replace (char* string, char* oldWord, char* newWord) {

    char* begin = strstr(string, oldWord);

    // The oldWord does not occur in the string
    if (begin == NULL) { 
        return NULL;
    }

    // Size of string does not allow replacement
    if (size < strlen(string) + (strlen(newWord) - strlen(oldWord)) +  1) {
        printf("Buffer size is too small for the convertion!\n");
        return NULL;
    }

    // Move string content after oldWord to correct position
    memmove(    begin + strlen(newWord), 
                begin + strlen(oldWord), 
                strlen(begin) - strlen(oldWord) + 1      );

    // Copy newWord content to correct position
    memcpy(begin, newWord, strlen(newWord));

    return begin + strlen(newWord);
}

int main(int argc, char* argv[]) {

    // Read file to obtain pairs
    FILE *cypherFile = fopen(CYPHER, "r");
    unsigned numWords = 0;
    char words[100][MAX_WORD_SIZE];

    while (fscanf(cypherFile, "%s", words[numWords]) == 1) {
        numWords++;
    }

    // Create pipes
    int pipeParentChild[2], pipeChildParent[2];

    if (pipe(pipeChildParent) < 0) {
        perror("Error: pipe parent-child!\n");
        return EXIT_FAILURE;
    }

    if (pipe(pipeParentChild) < 0) {
        perror("Error: pipe child-parent!\n");
        return EXIT_FAILURE;
    }

    // Create child process
    int process = fork();

    if (process == 0) {

        // Child Process work

        char buffer_child[size];
        close(pipeParentChild[READ]);
        close(pipeChildParent[WRITE]);

        while (1) {

            if (read(pipeChildParent[READ], buffer_child, size-1) < 0) {
                perror("Error: Unable to read from pipe parent-child!\n");
                break;
            }

            // Replacing all occurrences in the buffer based on words array
            for (int i = 0 ; i < numWords ; i+=2) {
                if (replace(buffer_child, words[i], words[i+1]) == NULL) {
                    while(replace(buffer_child, words[i+1], words[i]));
                } else {
                    while(replace(buffer_child, words[i], words[i+1]));
                }
            }

            if (write(pipeParentChild[WRITE], buffer_child, size-1) < 0) {
                perror("Error: Unable to write to pipe child-parent!\n");
                return EXIT_FAILURE;
            }
        }

        close(pipeParentChild[WRITE]);
        close(pipeChildParent[READ]);
        exit(process);

    } else {

        // Parent process work

        char buffer_parent[size];
        close(pipeParentChild[WRITE]);
        close(pipeChildParent[READ]);  

        while (1) {

            if (!fgets(buffer_parent, size, stdin)) break;

            if (write(pipeChildParent[WRITE], buffer_parent, size-1) < 0) {
                perror("Error: Unable to write to pipe parent-child!\n");
                return EXIT_FAILURE;
            }

            if (read(pipeParentChild[READ], buffer_parent, size-1) < 0) {
                perror("Error: Unable to read from pipe child-parent!\n");
                break;
            }

            printf("%s", buffer_parent);
        }

        close(pipeParentChild[READ]);
        close(pipeChildParent[WRITE]);
        wait(NULL); // Wait for child process
    }

    printf("\n");
    return EXIT_SUCCESS;
}
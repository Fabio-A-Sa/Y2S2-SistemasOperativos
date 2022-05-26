#include <stdio.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

int next_block_size(int count, int buffer_size) {
    return (count >= buffer_size) ? buffer_size: count;
}

void printLineCount(int count){
    (count == 1) ? (printf("[%d] ",count)) : (printf("\n[%d]",count));
}

int phrases(char *filename, bool printLines) {

    // check if file exists
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Cannot open file '%s'\n", filename);
        return EXIT_FAILURE;
    }

    // print lines
    int counter = 1;
    char buffer[BUFFER_SIZE+1];
    int r = fread(buffer, sizeof(char), BUFFER_SIZE, file);
    
    //check if file is not empty
    if(!r){
        printf("Error: file '%s' is empty\n", filename);
        return EXIT_FAILURE; 
    }

    bool printNewLine = true;
    bool EllipsisStart = false;
    bool spaceStart = false;
    while (r) {
        
        for (int index = 0 ; index < r ; index++) {

            //print lines on the beginning
            if(printNewLine && printLines && buffer[index] != EOF){
                printLineCount(counter);
                printNewLine = false;
            }
        
            //end a phrase if all conditions are met
            if( !(buffer[index] == '.' || buffer[index] == '!' || buffer[index] == '?' || buffer[index] == ' ' || buffer[index] == '\n') && EllipsisStart) {
                if( buffer[index] != EOF) counter++;
                EllipsisStart = false;
                if(printLines){
                    printLineCount(counter);
                    if(buffer[index] != '\n' && buffer[index] != ' ') {
                        printf(" ");
                        spaceStart = true;
                    }
                } 
            }
            //start pontuations
            else if ( (buffer[index] == '.' || buffer[index] == '!' || buffer[index] == '?') && !EllipsisStart) {
                EllipsisStart = true;
            }
            //start space (only print one)
            if( buffer[index] == ' ' && !spaceStart && printLines){
                printf(" ");
                spaceStart = true;
            }
            else if(buffer[index] != ' ' && buffer[index] != '\n' && spaceStart){
                spaceStart = false;
            }
            //detect new line on file
            if (buffer[index] == '\n' && printLines && !spaceStart) {
                printf(" ");
                spaceStart = true;
                continue;
            }
            //print chars
            if (buffer[index] != '\n' && buffer[index] != ' ' && printLines) {
                printf("%c", buffer[index]);
            }

        
        }

        r = fread(buffer, sizeof(char), BUFFER_SIZE, file);
        buffer[r] = '\0';
    }

    if (!printLines) printf("%d", counter);

    // good practice
	fclose(file);
    printf("\n");
    return EXIT_SUCCESS;
}


int main(int argc, char* argv[]) {

    // check if number of arguments is correct
    if (argc < 2 || argc > 3){
        printf("usage: phrase [-l] file\n");
        return EXIT_FAILURE;
    }
    // if argument number is 2 dont print lines
    else if(argc == 2){
        return phrases(argv[1], false);
    }

    // if argument number is 3 print lines
    else {
        if(strcmp(argv[1], "-l") == 0){
            return phrases(argv[2], true);
        }
        else{
            printf("./phrases %s %s: Command not found\n", argv[1], argv[2]);
            return EXIT_FAILURE;
        }
    }
    
    return EXIT_SUCCESS;
}
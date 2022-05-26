#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define MAX_MATRIX_SIZE 100

void printMatrix(int* matrix, int lines, int columns) {

    printf("%dx%d\n", lines, columns);
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d ", *(matrix + i*columns + j));
        }
        printf("\n");
    }
}

void fillMatrix(FILE* matrix, int* buffer) {

    unsigned index = 0; 
    int currentNumber;
    while (fscanf(matrix, "%d", &currentNumber) == 1) {
        buffer[index] = currentNumber;
        index++;
    }
}

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("usage: addmx file1 file2\n");
        return EXIT_FAILURE;
    }

    FILE* matrix1 = fopen(argv[1], "r");
    FILE* matrix2 = fopen(argv[2], "r");

    // Check if files exist
    if (matrix1 == NULL || matrix2 == NULL) {
        printf("Error: file not found!\n");
        return EXIT_FAILURE;
    }

    int n1, m1, n2, m2; 
    char div;

    // Take the parameters of the first line
    fscanf(matrix1, "%d", &n1);
    fscanf(matrix1, "%c", &div);
    fscanf(matrix1, "%d", &m1);
    fscanf(matrix2, "%d", &n2); 
    fscanf(matrix2, "%c", &div);
    fscanf(matrix2, "%d", &m2);

    // You can only add matrices if they have the same size
    if (n1 != n2 || m1 != m2) {
        printf("Error: sizes don't match!\n");
        return EXIT_FAILURE;
    }

    // Creates shared memory buffers
    const int MATRIX_SIZE = n1 * m1 * sizeof(int);
    int *matrix1Buffer = mmap(NULL, MATRIX_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    if (matrix1Buffer == MAP_FAILED) {
        perror("Error: mmap() for matrix 1 failed!\n");
        return EXIT_FAILURE;
    }

    int *matrix2Buffer = mmap(NULL, MATRIX_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    if (matrix2Buffer == MAP_FAILED) {
        perror("Error: mmap() for matrix 2 failed!\n");
        return EXIT_FAILURE;
    }

    int *finalMatrixBuffer = mmap(NULL, MATRIX_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    if (finalMatrixBuffer == MAP_FAILED) {
        perror("Error: mmap() for final matrix failed!\n");
        return EXIT_FAILURE;
    }

    // Get data from open files to created buffers
    fillMatrix(matrix1, matrix1Buffer); fclose(matrix1);
    fillMatrix(matrix2, matrix2Buffer); fclose(matrix2);
    
    int status;
    for (int column = 0; column < m1; column++) {
        int process = fork();
        if (process == 0) { // Child process
            for (int line = 0; line < n1; line++) {
                *(finalMatrixBuffer + line*m1 + column) = *(matrix1Buffer + line*m1 + column) + *(matrix2Buffer + line*m1 + column);
            }
            exit(process);
        }
    }

    // Parent process waits all child processes to end and prints the final result
    while (wait(&status) > 0);
    printMatrix(finalMatrixBuffer, n1, m1);

    return EXIT_SUCCESS;
}
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

void getFileStatus(char *fileName) {

    struct stat info;

    if (lstat(fileName, &info) == -1) {
        fprintf(stderr, "fsize: Can’t stat %s\n", fileName);
        return;
    }

    printf("%s size: %d bytes, disk_blocks: %d\n",
            fileName, (int)info.st_size, (int)info.st_blocks);
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        fprintf(stderr, "usage: %s file\n", argv[0]);
        return EXIT_FAILURE;
    }

    int i = 1;
    while (argv[i] != NULL) {
        getFileStatus(argv[i]);
        i++;
    }

    return EXIT_SUCCESS;
}
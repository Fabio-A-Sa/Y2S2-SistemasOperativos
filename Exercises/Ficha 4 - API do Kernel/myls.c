#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>

void printFile(char* fileName) {

    struct stat info;

    if (lstat(fileName, &info) == -1) {
        printf("Error!\n");
        return;
    }

    mode_t m = info.st_mode;

    putchar('d');
    putchar( m & S_IRUSR ? 'r' : '-');
    putchar( m & S_IWUSR ? 'w' : '-');
    putchar( m & S_IXUSR ? 'x' : '-');
    putchar( m & S_IRGRP ? 'r' : '-');
    putchar( m & S_IWGRP ? 'w' : '-');
    putchar( m & S_IXGRP ? 'x' : '-');
    putchar( m & S_IROTH ? 'r' : '-');
    putchar( m & S_IWOTH ? 'w' : '-');
    putchar( m & S_IXOTH ? 'x' : '-');

    printf(" 1 %d\t%s\t%s", info.st_gid, fileName, ctime(&info.st_mtime));
}

int main (int argc, char** argv) {

    if (argc != 2) {
        fprintf (stderr, "usage: %s dirname\n", argv[0]);
        return EXIT_FAILURE;
    }

    DIR *q = opendir (argv[1]);
    if (q == NULL) {
        fprintf (stderr, "%s: Cannot open directory ’%s’\n", argv[0], argv[1]);
        return EXIT_FAILURE;
    }

    printf ("%s/\n", argv[1]);
    struct dirent *p = readdir(q);
    while (p != NULL) {
        printFile(p->d_name);
        p = readdir(q);
    }

    closedir (q);

    return EXIT_SUCCESS;
}
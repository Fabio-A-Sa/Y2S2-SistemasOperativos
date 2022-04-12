#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

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
        printf ("\t%s\n", p->d_name);
        p = readdir(q);
    }

    closedir (q);

    return EXIT_SUCCESS;
}
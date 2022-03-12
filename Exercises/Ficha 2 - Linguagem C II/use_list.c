#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, char** argv) {

    list* l = list_new_random(20, 100);
    list_print(l);

    printf("First: %d\n", list_get_first(l));
    printf("Last: %d\n", list_get_last(l));

    printf("Remove first: ");
    list_remove_first(l); list_print(l);
    printf("Remove last: ");
    list_remove_last(l); list_print(l);

    return 0;
}
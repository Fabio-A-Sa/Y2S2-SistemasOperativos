#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, char** argv) {

    list* l = list_new_random(2, 10);
    list_print(l);

    return 0;
}
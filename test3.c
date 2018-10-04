#include "darryl.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void clean(char * str) {
    free(str);
}

int main(void) {
    Darryl d = create_darryl_cat(clean);

    char * merde = calloc(1, 2 * sizeof(char));
    strncpy(merde, "A", 2);
    add_at(d, 0, merde);

    char * merde2 = calloc(1, 2 * sizeof(char));
    strncpy(merde2, "B", 2);
    add_at(d, 1, merde2);

    char * merde3 = calloc(1, 2 * sizeof(char));
    strncpy(merde3, "C", 2);
    add_at(d, 2, merde3);

    for(int i = 0; i < 3; ++i) {
        printf("Darryl index[%d] = %s\n", i, (char *) get(d, i));
    }

    destroy_darryl(d);
    return EXIT_SUCCESS;
}

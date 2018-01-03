// test.c
// @author Cody Burrows <dcodyburrows@gmail.com>
//
// Testing 123
// is this thing on?
// This program is used to test the functionality of darryl.
//
// ////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include "darryl.h"

int main() {

    Darryl d = create_darryl();

    printf("Darryl's size: %d\n", get_allocated_size(d));

    int jared = 17;
    int sylvia = 21;

    int * jared_pointer = NULL;
    jared_pointer = &jared;

    add_at(d, 0, jared_pointer);
    add_at(d, 6, &sylvia);

    int * jp = (int *) get(d, 0);
    printf("Jared is %d\n", *jp);

    printf("Darryl's size: %d\n", get_allocated_size(d));

    int * sp = NULL;
    sp = (int *) get(d, 4);

    if(!sp) {
        printf("Yep, an invalid index returns null\n");
    }

    sp = (int *) get(d, 6);
    printf("Sylvia is %d\n", *sp);

    sp = (int *) get(d, 12);

    if(!sp) {
        printf("Yep, an invalid index returns null\n");
    }

    smaller(d, 3);
    printf("Darryl's size: %d\n", get_allocated_size(d));

    sp = (int *) get(d, 6);
    printf("Sylvia is %d\n", *sp);

    destroy_darryl(d);

    return 0;
}

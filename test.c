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

    printf("darryl's size: %d\n", get_allocated_size(d));

    int lasagna = 1030;
    int * davd = &lasagna;

    int las2 = 1040;
    int * davd2 = &las2;

    int las3 = 1050;
    int * davd3 = &las3;

    add_at(d, 0, davd);
    printf("darryl's size: %d\n", get_allocated_size(d));
    printf("Here's davd: %d\n", *((int *) get(d, 0)));
    add_at(d, 1, davd2);
    printf("darryl's size: %d\n", get_allocated_size(d));
    printf("Here's davd: %d\n", *((int *) get(d, 0)));
    add_at(d, 2, davd3);
    printf("darryl's size: %d\n", get_allocated_size(d));
    printf("Here's davd: %d\n", *((int *) get(d, 0)));

    printf("Here's davd2: %d\n", *((int *) get(d, 1)));
    printf("Here's davd3: %d\n", *((int *) get(d, 2)));

    printf("where's davd? %d\n", index_of(d, davd));
    printf("where's davd2? %d\n", index_of(d, davd2));
    printf("where's davd3? %d\n", index_of(d, davd3));

    destroy_darryl(d);

    return 0;
}

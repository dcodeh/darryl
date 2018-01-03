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

    int * dave = NULL;
    int val = 68;
    dave = &val;

    for(int i = 0; i < 12; ++i) {
        add_at(d, i, dave);
        printf("darryl's size: %d\n", get_allocated_size(d));
    }

    int * got = (int *) get(d, 0);
    printf("zero: %d\n", *got);

    int diane = 1000343;
    int * dp = &diane;

    replace(d, 0, dp);

    got = (int *) get(d, 0);
    printf("zero: %d\n", *got);

    got = (int *) get(d, 4);
    printf("four: %d\n", *got);

    destroy_darryl(d);

    return 0;
}

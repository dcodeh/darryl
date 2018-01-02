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

    add_at(d, 0, &jared);
    add_at(d, 4, &sylvia);

    destroy_darryl(d);

    return 0;
}

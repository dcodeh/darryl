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

    destroy_darryl(d);

    return 0;
}

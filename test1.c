// test1.c
// @author Cody Burrows <cxb2114@rit.edu>
// 
// Testing 1 2 3 
// Ahem. Hellow? Is this thing on?
// Oh...Yes, hi. This file demonstrates how simple strings can be used with
// darryl. 
// 
// Usage: make test1
//        ./test1
// //////////////////////////////////////////////////////////////////
#include "darryl.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
  * A simple cleanup function that frees memory taken up by a char *
  */
void clean(char * str) {
    // this cleanup function might be more complicated if you're
    // throwing complex datatypes into darryl
    
    // do a backflip
    free(str);
}

/**
  * A simple demonstration of throwing strings into darryl, and being a good 
  * user and cleaning up after yourself.
  */
int main(void) {
    // Creates a new dynamic array list, and specifies that the clean() method
    // above knows how to correctly deallocate memory belonging to whatever
    // you're throwing in there
    Darryl d = create_darryl_cat(clean); // it's a cat because it's self-cleaning

    char * davd = calloc(1, 2 * sizeof(char));
    strncpy(davd, "A", 2); // make a nice null terminated string...
    add_at(d, 0, davd); // in you go

    char * davd2 = calloc(1, 2 * sizeof(char));
    strncpy(davd2, "B", 2); // another nice string
    add_at(d, 1, davd2); // jam that puppy in

    char * davd3 = calloc(1, 2 * sizeof(char));
    strncpy(davd3, "C", 2); // wow such a great null terminated string
    add_at(d, 2, davd3); // sianara

    for(int i = 0; i < 3; ++i) {
        // just print each string on a separate line
        printf("Darryl index[%d] = %s\n", i, (char *) get(d, i));
    }

    // clean stuff up, we're done here
    // darryl handles all of the freeing of the data put in (yay!)
    destroy_darryl(d);
    return EXIT_SUCCESS;
}

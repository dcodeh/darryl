// darryl.c
// @author Cody Burrows <dcodyburrows@gmail.com>
//
// This file provides functionality for a Data Type loosely based on the Java 
// ArrayList. 
//
// TODO add more descriptions about how to use this thing
// 
// ////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_SZ 5

struct darrylStruct {
    void * elements;
    int size;
    int num_elements;
};

typedef struct darrylStruct *Darryl;

#define _DARRYL_IMPL_
#include "darryl.h"

/**
  * Creates and initializes an empty dynamic array list
  */
Darryl create_darryl() {

    Darryl d = (Darryl) malloc(sizeof(struct darrylStruct));
    void * elements = calloc(DEFAULT_SZ, sizeof(void*));
    d -> elements = elements;
    d -> size = DEFAULT_SZ;
    d -> num_elements = 0;

    return d;
}

/**
  * Frees resources used by the data structure, and leaks any data
  * left over in the structure all over the place.
  */ 
void destroy_darryl(Darryl d) {

    free(d -> elements);

    free(d);
}

/**
  * Returns the number indexes currently allocated in the array.
  */
int get_allocated_size(Darryl d) {
    return d -> size;
}

/**
  * Manually increase the size of the underlying array. This function is 
  * accessible to the user in case they want to make one reallocation
  * before adding many elements.
  *
  * Returns the new size of the array, which is guaranteed to be
  * greater than or equal to the original size, depending on whether
  * realloc works or not.
  */
int bigger(Darryl d, int size) {

    void * old = d -> elements;
    void * new = 0;
    int new_size = 0;

    switch(size) {
        case 0:
            new_size = get_allocated_size(d) + DEFAULT_SZ;
            break;

        default:
            new_size = get_allocated_size(d) + size;
            break;
    }

    new = realloc(old, (size_t) new_size);

    if(new) {
        d -> elements = new;
        d -> size = new_size;
    } 
    
    return d -> size;

}

/**
  * Manually decrease the size of the array. This function is accessible to
  * the user so that space can be saved when it is not needed.
  *
  * If 0 is used for the size to shrink the array, the DEFAULT_SZ will be used.
  *
  * Be careful, because Darryl will shrink to the size that is passed in,
  * potentially leaking data all over the place with no remorse.
  *
  * Returns the new (smaller) size of the array.
  */
int smaller(Darryl d, int size) {

    void * old = d -> elements;
    void * new = 0;
    int new_size = 0;

    switch(size) {
        case 0:
            new_size = get_allocated_size(d) - DEFAULT_SZ;
            break;

        default:
            new_size = get_allocated_size(d) - size;
            break;
    }

    if(new_size < 0) {
        new_size = 0;
    }

    new = realloc(old, (size_t) new_size);

    if(new) {
        d -> elements = new;
        d -> size = new_size;
    }

    return new_size;

    

}

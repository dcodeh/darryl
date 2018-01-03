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
    void ** elements;
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

    Darryl d = (Darryl) calloc(1, sizeof(struct darrylStruct));
    d -> elements = NULL;
    d -> size = 0;
    d -> num_elements = 0;

    return d;
}

/**
  * Frees resources used by the data structure, and leaks any data
  * left over in the structure all over the place.
  */ 
void destroy_darryl(Darryl d) {

    if(d -> elements) {
        free(d -> elements);
    } 

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

    void * old = NULL;
    old = d -> elements;
    void * new = NULL;
    int new_size = 0;

    switch(size) {
        case 0:
            new_size = get_allocated_size(d) + DEFAULT_SZ;
            break;

        default:
            new_size = get_allocated_size(d) + size;
            break;
    }

    new = (void *) realloc(old, (size_t) new_size * sizeof(void *));

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

    void * old = 0;
    old = d -> elements;
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

    new = (void *) realloc(old, (size_t) new_size * sizeof(void *));

    if(new) {
        d -> elements = new;
        d -> size = new_size;
    }

    return new_size;

}

/**
  * Returns the number of elements stored in the array list
  */ 
int get_size(Darryl d) {
    return d -> num_elements;
}

/**
  * Returns true if there are no elements in the array.
  */ 
bool is_empty(Darryl d) {
    return get_size(d) == 0;
}

/**
  * Inserts an element into a specific place in the array.
  *
  * Returns true if the operation completed successfully. 
  *
  * Takes O(n) time in the worst case :(
  */
bool add_at(Darryl d, int index, void * data) {
    
    int size = d -> size;

    if(index >= 0) {

        // check if we need to resize
        // if index outside allocated range
        // array is full (no more room)
        
        if(index >= size) {
            
            // guaranteed to be positive or zero
            int diff = size - index;

            if(diff > DEFAULT_SZ) {
                bigger(d, diff);
            } else {
                bigger(d, DEFAULT_SZ);
            }

            // insert and fix all of the other elements
            void * dest = NULL;
            dest = d -> elements[index];
            
            if(dest) {
                void * removed = replace(d, index, data);

                for(int i = index + 1; i < size; ++i) {
                    
                    if(removed) {
                        removed = replace(d, i, removed);
                    }

                }
            }

        }

        // put the thing in
        d -> elements[index] = data;

        int num = d -> num_elements;
        num++;
        d -> num_elements = num;
        return true;
    } else {
        return false;
    }


}

/**
  * Yanks out an element, and puts something else in its place. 
  * 
  * Returns the yanked element
  */ 
void * replace(Darryl d, int index, void * data) {
    
    if(index < (d -> size)) {
        void * removed = remove_data(d, index);
        add_at(d, index, data);
        return removed;
    } else {
        return 0;
    }
}

/**
  * Removes a specified entry from the array list
  */
void * remove_data(Darryl d, int index) {

    if(index < (d -> size)) {

        void * data = d -> elements[index];
        d -> elements[index] = NULL;
        
        return data;
    } else {
        return 0;
    }
}

/**
  * Returns the data at a specific index.
  */
void * get(Darryl d, int index) {

    if(index >= 0 && index < (d -> size)) {
        return d->elements[index];
    } else {
        return 0;
    }

}

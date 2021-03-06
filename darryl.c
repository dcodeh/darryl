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
#include <string.h>

#define DEFAULT_SZ 5

struct darrylStruct {
    void ** elements;
    int size;
    int num_elements;
    void (*cleanup)(); // any function that returns void
};

typedef struct darrylStruct *Darryl;

#define _DARRYL_IMPL_
#include "darryl.h"

/**
  * Creates and initializes an empty dynamic array list
  * without a cleanup function
  */
Darryl create_darryl() {

    return create_darryl_cat(NULL);

}

/**
  * Creates and initializes an empty dynamic array list with a cleanup
  * function. It's a cat because it's self cleaning, and knows how to
  * use a litter box (free())
  */
Darryl create_darryl_cat(void (*f)()) {
    
    Darryl d = (Darryl) calloc(1, sizeof(struct darrylStruct));
    d -> elements = NULL;
    d -> size = 0;
    d -> num_elements = 0;
    d -> cleanup = f;

    return d;
}

/**
  * Frees resources used by the data structure, and leaks any data
  * left over in the structure all over the place if a cleanup function
  * isn't passed in at construction time.
  */ 
void destroy_darryl(Darryl d) {

    if(d -> elements) {
        clear(d);
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
    int old_size = d -> size;
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
        // make sure there isn't any junk in the new part of the array
        d -> elements = new;
        d -> size = new_size;

        size_t null_offset = (size_t) old_size * sizeof(void *);
        size_t new_data_size = ((size_t) new_size * sizeof(void *)) - null_offset;
        memset(new + null_offset, 0, new_data_size);
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
            void * dest = d -> elements[index];
            
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

        int old_num = 0;
        old_num = d -> num_elements;

        if(data) {
            old_num--;
        }

        d -> num_elements = old_num;
        
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

/**
  * Return the location of the specified element if it exists
  */
int index_of(Darryl d, void * data) {

    int index = -1;
    for(int i = 0; i < (d -> size); ++i) {

        if(d -> elements[i] == data) {
            index = i;
            break;
        }

    }

    return index;

}

/**
  * Return true if the specified element exists
  */ 
bool contains(Darryl d, void * data) {

    return index_of(d, data) != -1;

}

/**
  * Removes a range of elements from the array from
  * [start_index, end_index] (inclusive).
  */ 
void remove_range(Darryl d, int start_index, int end_index) {

    for(int i = start_index; i <= end_index; ++i) {
        void * data = remove_data(d, i);
        if(data && (d -> cleanup)) {
            (*(d -> cleanup))(data);
        }
    }
    
}

/**
  * Remove all of the data in the structure.
  * If there is a cleanup function passed in, data will automatically be 
  * cleaned up. Otherwise, data will leak all over the place.
  *
  * If a cleanup function was used, true will be returned. Otherwise
  * false will be returned.
  */
bool clear(Darryl d) {
    for(int i = 0; i < (d -> size); ++i) {
        void * data = remove_data(d, i);
        if(data && (d -> cleanup)) {
            (*(d -> cleanup))(data);
        }

    }

    d -> num_elements = 0;
    return (d -> cleanup) != NULL;
}

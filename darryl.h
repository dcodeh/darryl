// darryl.h 
// @author Cody Burrows <dcodyburrows@gmail.com>
//
// This file provides function definitions for the Darryl data structure.
// Its design is loosely based on the Java ArrayList, and is set up such that
// the underlying data type is hidden from the user. Just don't worry about it.
//
// TODO add some text describing how to use this thing
//
// ////////////////////////////////////////////////////////////////////////////
#ifndef DARRYL_H
#define DARRYL_H

#include <stdbool.h>
#include <stdlib.h>

#ifndef _DARRYL_IMPL_
typedef struct { } *Darryl;
#endif

// TODO in the future consider allowing the user to pass a function pointer
// for making custom logic to control reallocating, and for data cleanup
/// Initialize an empty dynamic array list
Darryl create_darryl();

// TODO decide if this should be private (i.e. not in the header file)
/// return the allocated size of this dynamic array list
int get_allocated_size(Darryl d);

/// return the number of elements in the list
int get_size(Darryl d);

/// add data to a specific place in the array, then return true if successful
bool add_at(Darryl d, int index, void * data);

/// append the data to the array, then return true if successful
bool add(Darryl d, void * data);

/// remove all of the data from the array, then return true if successful
bool clear(Darryl d);

/// return true if the array d contains data as one of its elements
bool contains(Darryl d, void * data);

/// return the data at a specific location in the array
void * get(Darryl d, int index);

/// return the location of an element in the data structure, if it exists.
int index_of(Darryl d, void * data);

/// return true if the data structure holds 0 elements
bool is_empty(Darryl d);

/// return the data stored at a location, then remove it from the array
void * remove_data(Darryl d, int index);

/// remove a whole region of data from the data structure
void remove_range(Darryl d, int start_index, int end_index);

/// swap some data out of the data structure
void * replace(Darryl d, int index, void * data);

/// return a pointer to a static snapshot of the data stored in the structure
void * to_array(Darryl d);

/// free all of the resources used by the data structure
void destroy_darryl(Darryl d);

/// manually increase the allocated size of the array by the specified amount
int bigger(Darryl d, int size);

/// manually decrease the allocated size of the array by the specified amount
int smaller(Darryl d, int size);

#endif

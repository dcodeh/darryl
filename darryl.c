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
    void (*cleanup)(void * data);
};

typedef struct darrylStruct *Darryl;

#define _DARRYL_IMPL_
#include "darryl.h"

/**
  * Creates and initializes an empty dynamic array list
  */
Darryl create_darryl(void (*cleanup)()) {

    Darryl d = malloc(sizeof(struct darrylStruct));
    d -> elements = malloc(DEFAULT_SZ * sizeof(void*));
    d -> size = DEFAULT_SZ;
    d -> cleanup = cleanup;

    return d;
}

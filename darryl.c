#include <stdio.h>

#define DEFAULT_SZ 5

struct darrylStruct {
    void * elements[DEFAULT_SZ];
    int size;
    void (*cleanup)(void * data);
};

typedef struct darrylStruct *Darryl;

#define _DARRYL_IMPL_
#include "darryl.h"

/*
 * Add functions and such here
 */

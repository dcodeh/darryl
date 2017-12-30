#include <stdlib.h>

#define DEFAULT_SZ 5

struct darrylStruct {
    void * elements[DEFAULT_SZ];
    size_t size;
};

typedef struct darrylStruct *Darryl;

#define _DARRYL_IMPL_
#include "darryl.h"

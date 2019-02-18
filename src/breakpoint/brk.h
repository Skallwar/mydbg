#ifndef BRKP_H
#define BRKP_H

#include <stddef.h>

#include "htab/htab.h"

struct brkp {
    size_t id;
    void *addr;
    // TODO store original code
};

typedef struct brkp brkp_t;

/* Create a new struct representing a breakpoint */
brkp_t *brkp_new(size_t id, void *addr);
/* Set the brkp in the memory of the tracee */
void brkp_set(brkp_t *brkp);
/* Replace interupt by real code of brkp in the memory of the tracee */
void brkp_unset(brkp_t *brkp);
/* Insert a new break point in a htab */
void brkp_add(htab_t *htab, brkp_t *brkp);
/* Remove a breakpoint in a htab */
/* void brkp_set(htab_t *htab); */

#endif

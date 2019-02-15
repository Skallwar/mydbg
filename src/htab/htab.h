#ifndef HTAB_H
#define HTAB_H

#include <stddef.h>
#include <stdbool.h>

#include "intrlist/intrlist.h"

/* An htab need an hash function given by the user */
struct bucket {
    void *key;
    void *elm;
    intrlist_t list;
};

struct htab {
    size_t cap;
    size_t size;
    size_t nb_elm;
    size_t (*hfunc)(void *);
    bool (*cmpfunc)(void *, void *);
    struct bucket *tab;
};

typedef struct htab htab_t;

/* Create a new htab */
htab_t *htab_new(size_t (*hfunc)(void *), bool (*cmpfunc)(void *, void *));
/* Delete the htab */
void htab_free(htab_t *htab);

/* Add a new element in the htab */
void htab_add(htab_t *htab, void *key, void *elm);
/* Find a match in the htab */
void *htab_find(htab_t *htab, void *key);
/* Remove an element of the htab */
void *htab_del(htab_t *htab, void *rey);

#endif

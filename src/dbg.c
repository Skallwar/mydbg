#include <sys/types.h>
#include <stdlib.h>
#include <stdint.h>

#include "dbg.h"

static size_t hfunc(void *);
static bool cmpfunc(void *key1, void *key2);

ctx_t *ctx_new(pid_t pid)
{
    ctx_t *ctx = malloc(sizeof(*ctx));
    if (!ctx) {
        return NULL;
    }

    ctx->pid = pid;
    ctx->onbrk = false;
    ctx->brktab = htab_new(hfunc, cmpfunc);
    if (!ctx->brktab) {
        return NULL;
    }

    return ctx;
}

void ctx_free(ctx_t *ctx)
{
    htab_free(ctx->brktab);
    free(ctx);
}

static size_t hfunc(void *key)
{
    size_t hash = (size_t)key;
    hash = (~hash) + (hash << 21); // key = (key << 21) - key - 1;
    hash = hash    ^ (hash >> 24);
    hash = (hash   + (hash << 3)) + (hash << 8); // key * 265
    hash = hash    ^ (hash >> 14);
    hash = (hash   + (hash << 2)) + (hash << 4); // key * 21
    hash = hash    ^ (hash >> 28);
    hash = hash    + (hash << 31);

    return hash;
}

static bool cmpfunc(void *key1, void *key2)
{
    return key1 == key2;
}

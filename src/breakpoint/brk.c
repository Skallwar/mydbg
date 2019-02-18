#include <stdlib.h>
#include <stdint.h>

#include "brk.h"
#include "dbg.h"
#include "memory/mem.h"

#define INT3 0xCC

brkp_t *brkp_new(ctx_t *ctx, size_t id, void *addr)
{
    brkp_t *brkp = malloc(sizeof(*brkp));
    if (!brkp) {
        return NULL;
    }

    brkp->id = id;
    brkp->addr = addr;

    htab_add(ctx->brktab, brkp->addr, brkp);

    return brkp;
}

int brkp_set(ctx_t *ctx, brkp_t *brkp)
{
    uint8_t byte = INT3;
    int err = write_mem(ctx->pid, brkp->addr, &byte, 1);

    return err;
}

int brkp_unset(ctx_t *ctx, brkp_t *brkp)
{
    int err = write_mem(ctx->pid, brkp->addr, &brkp->code, 1);

    return err;
}

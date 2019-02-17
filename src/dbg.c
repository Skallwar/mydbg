#include <sys/types.h>
#include <stdlib.h>

#include "dbg.h"

ctx_t *ctx_new(pid_t pid)
{
    ctx_t *ctx = malloc(sizeof(*ctx));
    if (!ctx) {
        return NULL;
    }

    ctx->pid = pid;
    ctx->onbrk = false;
    /* ctx->brktab = htab_new() */
    /* if (!ctx->brktab) { */
    /*     return NULL; */
    /* } */

    return ctx;
}

void ctx_free(ctx_t *ctx)
{
    htab_free(ctx->brktab);
    free(ctx);
}

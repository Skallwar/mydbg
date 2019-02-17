#ifndef DBG_H
#define DBG_H

#include <sys/types.h>
#include <stdbool.h>

#include "htab/htab.h"

struct dbg_ctx {
    pid_t pid;
    bool onbrk;
    htab_t *brktab;
};

typedef struct dbg_ctx ctx_t;

ctx_t *ctx_new(pid_t pid);
void ctx_free(ctx_t *ctx);

#endif

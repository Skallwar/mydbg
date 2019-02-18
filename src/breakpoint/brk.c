#include <stdlib.h>
#include <stdint.h>

#include "brk.h"
#include "dbg.h"
#include "memory/mem.h"

#define INT3 0xCC

brkp_t *brkp_new(ctx_t *ctx, uint64_t *addr)
{
    brkp_t *brkp = malloc(sizeof(*brkp));
    if (!brkp) {
        return NULL;
    }

    brkp->id = ctx->brktab->nb_elm;
    brkp->addr = addr;

    htab_add(ctx->brktab, brkp->addr, brkp);

    return brkp;
}

int brkp_set(ctx_t *ctx, brkp_t *brkp)
{
    uint64_t instr = 0;

    int err = ptrace_read_mem(ctx->pid, brkp->addr, &instr, 1);
    if (err < 0) {
        return err;
    }

    /* Remove first byte and replace it with INT3 */
    instr = (instr & 0x00) | INT3;

    err = ptrace_write_mem(ctx->pid, brkp->addr, &instr, 1);

    return err;
}

int brkp_unset(ctx_t *ctx, brkp_t *brkp)
{
    //TODO use ptrace_write_mem
    /* int err = write_mem(ctx->pid, brkp->addr, &brkp->code, 1); */

    /* return err; */
    return 0;
}

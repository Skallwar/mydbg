#include <stdlib.h>
#include <stdint.h>

#include "brk.h"
#include "dbg.h"
#include "memory/mem.h"

#define INT3 0xCC

static uint64_t read_instr(pid_t pid, uint64_t *addr, uint64_t *instr);
static uint64_t write_instr(pid_t pid, uint64_t *addr, uint64_t *instr);
static inline uint64_t instr_mod(uint64_t base, uint8_t fbyte);

brkp_t *brkp_new(ctx_t *ctx, uint64_t *addr)
{
    brkp_t *brkp = malloc(sizeof(*brkp));
    if (!brkp) {
        return NULL;
    }


    brkp->id = ctx->brktab->nb_elm;
    brkp->addr = addr;

    /* Read the byte */
    int err = read_instr(ctx->pid, brkp->addr, &brkp->instr);
    if (err < 0) {
        return NULL;
    }

    htab_add(ctx->brktab, brkp->addr, brkp);

    return brkp;
}

int brkp_set(ctx_t *ctx, brkp_t *brkp)
{
    /* Remove first byte and replace it with INT3 */
    uint64_t instr = instr_mod(brkp->instr, INT3);

    return write_instr(ctx->pid, brkp->addr, &instr);
}

int brkp_unset(ctx_t *ctx, brkp_t *brkp)
{
    /* Remove first byte and replace it with original byte*/
    return write_instr(ctx->pid, brkp->addr, &brkp->instr);
}

static uint64_t read_instr(pid_t pid, uint64_t *addr, uint64_t *instr)
{
    return ptrace_read_mem(pid, addr, instr, 1);
}

static uint64_t write_instr(pid_t pid, uint64_t *addr, uint64_t *instr)
{
    return ptrace_write_mem(pid, addr, instr, 1);
}

/* Replace the first byte of an instruction */
static inline uint64_t instr_mod(uint64_t base, uint8_t fbyte)
{
    return (base & 0x00) | fbyte;
}

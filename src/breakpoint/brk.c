#include <stdlib.h>
#include <stdint.h>

#include "brk.h"
#include "dbg.h"
#include "memory/mem.h"

#define INT3 0xCC

static uint64_t read_instr(pid_t pid, uint64_t *addr, uint64_t *instr);
static uint64_t write_instr(pid_t pid, uint64_t *addr, uint64_t *instr);
static inline uint64_t instr_mod(uint64_t base, uint8_t fbyte);
static inline uint8_t read_fbyte(uint64_t instr);

brkp_t *brkp_new(ctx_t *ctx, uint64_t *addr)
{
    brkp_t *brkp = malloc(sizeof(*brkp));
    if (!brkp) {
        return NULL;
    }


    brkp->id = ctx->brktab->nb_elm;
    brkp->addr = addr;

    /* Read the byte */
    uint64_t instr = 0;
    int err = read_instr(ctx->pid, brkp->addr, &instr);
    if (err < 0) {
        return NULL;
    }

    brkp->byte = read_fbyte(instr);

    htab_add(ctx->brktab, brkp->addr, brkp);

    return brkp;
}

int brkp_set(ctx_t *ctx, brkp_t *brkp)
{
    uint64_t instr = 0;

    int err = read_instr(ctx->pid, brkp->addr, &instr);
    if (err < 0) {
        return err;
    }

    /* Remove first byte and replace it with INT3 */
    instr = instr_mod(instr, INT3);

    err = write_instr(ctx->pid, brkp->addr, &instr);

    return err;
}

int brkp_unset(ctx_t *ctx, brkp_t *brkp)
{
    uint64_t instr = 0;

    int err = read_instr(ctx->pid, brkp->addr, &instr);
    if (err < 0) {
        return err;
    }

    /* Remove first byte and replace it with original byte*/
    instr = instr_mod(instr, brkp->byte);

    err = write_instr(ctx->pid, brkp->addr, &instr);

    return err;
}

static uint64_t read_instr(pid_t pid, uint64_t *addr, uint64_t *instr)
{
    int err = ptrace_read_mem(pid, addr, instr, 1);
    return err;
}

static uint64_t write_instr(pid_t pid, uint64_t *addr, uint64_t *instr)
{
    int err = ptrace_write_mem(pid, addr, instr, 1);
    return err;
}

/* Replace the first byte of an instruction */
static inline uint64_t instr_mod(uint64_t base, uint8_t fbyte)
{
    return (base & 0x00) | fbyte;
}

/* Read the first byte of an instruction */
static inline uint8_t read_fbyte(uint64_t instr)
{
    return instr & 0x00000000000000FF;
}

#ifndef CMDS_H
#define CMDS_H

#include <unistd.h>

#include "dbg.h"

struct cmd {
    const char *name;
    /* const char *help; */
    int (*fn)(ctx_t *, char *);
};

#define UNUSED __attribute__((unused))

#define shell_cmd(namestr, func) \
    static struct cmd __cmd_ ## namestr \
    __attribute__ ((section("cmds"), used)) = \
    {.name = #namestr, .fn = func}

extern struct cmd __start_cmds[];
extern struct cmd __stop_cmds[];

int help_cmd(ctx_t *ctx, char *arg);

int exit_cmd(ctx_t *ctx, char *arg);

int continue_cmd(ctx_t *ctx, char *arg);
int next_cmd(ctx_t *ctx, char *arg);
int next_instr_cmd(ctx_t *ctx, char *arg);

int info_regs_cmd(ctx_t *ctx, char *arg);
int info_mem_cmd(ctx_t *ctx, char *arg);

int examine_cmd(ctx_t *ctx, char *arg);

int break_cmd(ctx_t *ctx, char *arg);
int tbreak_cmd (ctx_t *ctx, char *arg);

#endif

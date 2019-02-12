#ifndef CMDS_H
#define CMDS_H

#include <unistd.h>

struct dbg_ctx {
    pid_t pid;
};

typedef struct dbg_ctx ctx_t;

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

int help(ctx_t *ctx, char *arg);
int quit(ctx_t *ctx, char *arg);
int resume(ctx_t *ctx, char *arg);
int info_regs(ctx_t *ctx, char *arg);
int info_mem(ctx_t *ctx, char *arg);

#endif

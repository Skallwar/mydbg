#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <err.h>

#include "shell/shell.h"
#include "cmds/cmds.h"
#include "htab/htab.h"

#define NAME "mydbg> "

static ctx_t *dbg_init(char *argv[]);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        errx(1, "No program to debug\n");
    }
    ctx_t *ctx = dbg_init(argv);
    shell_start(NAME, ctx);
}

static ctx_t *dbg_init(char *argv[])
{
    ctx_t *ctx = calloc(1, sizeof(*ctx));
    if (!ctx) {
        return NULL;
    }

    ctx->pid = fork();
    /* ctx->brktab = htab_new(); */

    if (ctx->pid == 0) {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        execvp(argv[1], argv + 1);
    }

    waitpid(ctx->pid, NULL, 0);
    /* we now have our debugged program in a stopped state */

    return ctx;
}

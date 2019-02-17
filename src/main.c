#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <err.h>

#include "shell/shell.h"
#include "cmds/cmds.h"
#include "dbg.h"

#define NAME "mydbg> "

static pid_t dbg_init(char *argv[]);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        errx(1, "No program to debug\n");
    }

    pid_t traceepid = dbg_init(argv);

    ctx_t *ctx = ctx_new(traceepid);

    shell_start(NAME, ctx);
}

static pid_t dbg_init(char *argv[])
{
    pid_t pid = fork();
    /* ctx->brktab = htab_new(); */

    if (pid == 0) {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        execvp(argv[1], argv + 1);
    }

    waitpid(pid, NULL, 0);
    /* we now have our debugged program in a stopped state */

    return pid;
}

#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "cmds.h"

static void sig_catch(int sig);

int resume(ctx_t *ctx, char *arg UNUSED)
{
    ptrace(PTRACE_CONT, ctx->pid, 0, 0);

    int wstatus;
    waitpid(ctx->pid, &wstatus, 0);

    if (WIFEXITED(wstatus)) {
        printf("Debugged program exited normally\n");
    }
    else if (WIFSTOPPED(wstatus)) {
        int sig = WSTOPSIG(wstatus);
        sig_catch(sig);
    }

    return 0;
}

static void sig_catch(int sig)
{
    switch (sig) {
    default :
        printf("A signal has been caught but no action has been implemented\n");
    }
}

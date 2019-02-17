#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>

#include "cmds.h"
#include "sig/sig.h"

int resume(ctx_t *ctx, char *arg UNUSED)
{
    ptrace(PTRACE_CONT, ctx->pid, 0, 0);

    int sig = sig_catch(ctx->pid);
    int err = sig_handler(sig);

    if (err < 0) {
        printf("A signal has been caught but no action has been implemented\n");
        return -1;
    }

    return 0;
}
shell_cmd(continue, resume);

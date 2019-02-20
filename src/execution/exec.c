#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/signal.h>

#include "exec.h"
#include "signal/sig.h"

int exec_resume(ctx_t *ctx)
{
    ptrace(PTRACE_CONT, ctx->pid, 0, 0);

    int err = 0;
    if (ctx->onbrk) {
        err = exec_singlestep(ctx);
    }

    int sig = sig_catch(ctx->pid);
    int err2 = sig_handler(ctx, sig);

    err = err < 0 ? err : err2;

    /* Return error status of sig_handler() */
    return err;
}

int exec_singlestep(ctx_t *ctx)
{
    ptrace(PTRACE_SINGLESTEP, ctx->pid, 0, 0);

    int sig = sig_catch(ctx->pid);
    int err = sig_handler(ctx, sig);

    return err;
}

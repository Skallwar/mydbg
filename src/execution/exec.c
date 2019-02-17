#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/signal.h>

#include "exec.h"
#include "signal/sig.h"

int resume(ctx_t *ctx)
{
    ptrace(PTRACE_CONT, ctx->pid, 0, 0);

    int sig = sig_catch(ctx->pid);
    int err = sig_handler(sig);

    /* Return error status of sig_handler() */
    return err;
}

int singlestep(ctx_t *ctx)
{
    ptrace(PTRACE_SINGLESTEP, ctx->pid, 0, 0);

    int sig = sig_catch(ctx->pid);

    int err = 0;
    // TODO Fix sig_handler
    /* if (sig != SIGTRAP) { */
    /*    err = sig_handler(sig); */
    /* } */

    return err;
}

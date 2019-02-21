#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/signal.h>

#include "exec.h"
#include "signal/sig.h"

int exec_resume(ctx_t *ctx)
{
    if (ctx->onbrk) {
        int err = exec_singlestep(ctx);
        if (err < 0) {
            return -1;
        }
    }

    ptrace(PTRACE_CONT, ctx->pid, 0, 0);

    int sig = sig_catch(ctx->pid);
    int err = sig_handler(ctx, sig);

    return err;
}

int exec_singlestep(ctx_t *ctx)
{
    ptrace(PTRACE_SINGLESTEP, ctx->pid, 0, 0);

    int sig = sig_catch(ctx->pid);
    int err = sig_handler(ctx, sig);

    return err;
}

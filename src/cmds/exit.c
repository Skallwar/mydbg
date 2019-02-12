#include <signal.h>

#include "cmds.h"

int quit(ctx_t *ctx, char *arg UNUSED)
{
    kill(ctx->pid, SIGKILL);
    _exit(0);
}
shell_cmd(exit, quit);

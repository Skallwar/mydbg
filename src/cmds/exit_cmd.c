#define _POSIX_C_SOURCE 1
#include <signal.h>

#include "cmds.h"
#include "shell/shell.h"

int exit_cmd(ctx_t *ctx, char *arg UNUSED)
{
    shell_stop();

    return kill(ctx->pid, SIGKILL);
}
shell_cmd(exit, exit_cmd);

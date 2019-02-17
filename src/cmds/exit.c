#include <signal.h>

#include "cmds.h"
#include "shell/shell.h"

int quit(ctx_t *ctx, char *arg UNUSED)
{
    kill(ctx->pid, SIGKILL);
    shell_stop();
}
shell_cmd(exit, quit);

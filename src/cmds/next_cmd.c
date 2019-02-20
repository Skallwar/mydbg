#include "cmds.h"
#include "execution/exec.h"

int next_cmd(ctx_t *ctx, char *arg UNUSED)
{
    return exec_singlestep(ctx);
}
shell_cmd(next, next_cmd);

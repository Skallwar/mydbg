#include "cmds.h"
#include "execution/exec.h"

int singlestep_cmd(ctx_t *ctx, char *arg UNUSED)
{
    return singlestep(ctx);
}
shell_cmd(singlestep, singlestep_cmd);

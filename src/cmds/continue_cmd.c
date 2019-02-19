#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>

#include "cmds.h"
#include "execution/exec.h"

int continue_cmd(ctx_t *ctx, char *arg UNUSED)
{
    return resume(ctx);
}
shell_cmd(continue, continue_cmd);

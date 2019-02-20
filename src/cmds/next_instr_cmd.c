#include <string.h>

#include "cmds.h"
#include "execution/exec.h"
#include "register/regs.h"
#include "capstone/caprock.h"
#include "breakpoint/brkp.h"

int next_instr_cmd(ctx_t *ctx, char *arg UNUSED)
{
    return -1;
}
shell_cmd(next_instr, next_instr_cmd);

#include <string.h>

#include "cmds.h"
#include "register/regs.h"
#include "execution/exec.h"
#include "capstone/caprock.h"
#include "breakpoint/brkp.h"

int next_instr_cmd(ctx_t *ctx, char *arg UNUSED)
{
    struct user_regs_struct regs;
    regs_get(ctx->pid, &regs);
    uint64_t rip = reg_get(&regs, rip);

    cs_insn *instr = next_instr(ctx, rip);

    if (strstr(instr->mnemonic, "call")) {
        rip += instr->size;

        brkp_t *brkp = brkp_new(ctx, (uint64_t *)rip, true);
        brkp_set(ctx, brkp);

        return exec_resume(ctx);
    }
    else {
        return exec_singlestep(ctx);
    }
}
shell_cmd(next_instr, next_instr_cmd);

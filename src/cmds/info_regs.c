#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/user.h>

#include "cmds.h"

#define print_reg(regs, name) printf("%s: 0x%llx\n", #name, regs.name)

int info_regs(ctx_t *ctx, char *arg UNUSED)
{
    struct user_regs_struct regs;
    ptrace(PTRACE_GETREGS, ctx->pid, NULL, &regs);

    print_reg(regs, rip);
    print_reg(regs, rsp);
    print_reg(regs, rbp);
    print_reg(regs, eflags);
    print_reg(regs, orig_rax);
    print_reg(regs, rax);
    print_reg(regs, rbx);
    print_reg(regs, rcx);
    print_reg(regs, rdx);
    print_reg(regs, rdi);
    print_reg(regs, rsi);
    print_reg(regs, r8);
    print_reg(regs, r9);
    print_reg(regs, r10);
    print_reg(regs, r11);
    print_reg(regs, r12);
    print_reg(regs, r13);
    print_reg(regs, r14);
    print_reg(regs, r15);
    print_reg(regs, cs);
    print_reg(regs, ds);
    print_reg(regs, es);
    print_reg(regs, fs);
    print_reg(regs, gs);
    print_reg(regs, ss);
    print_reg(regs, fs_base);
    print_reg(regs, gs_base);

    return 0;
}
shell_cmd(info_regs, info_regs);

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/stat.h>
#include <signal.h>

#include "cmds.h"
#include "shell/shell.h"

#define UNUSED __attribute__((unused))

#define print_reg(regs, name) printf("%s: 0x%llx\n", #name, regs.name)

/* int help(void *ctx, char *arg) */
/* { */
/*     for (int64_t i = 0; i < __stop_cmds - __stop_cmds; ++i) { */
/*         struct cmd *cmd = __stop_cmds + i; */
/*         printf("%s : %s\n", cmd->name, cmd->help); */
/*     } */

/*     return 0; */
/* } */
/* shell_cmd(help, help, "Display this message"); */

static void sig_catch(int sig);

int quit(ctx_t *ctx, char *arg UNUSED)
{
    kill(ctx->pid, SIGKILL);
    _exit(0);
}
shell_cmd(exit, quit);

int resume(ctx_t *ctx, char *arg UNUSED)
{
    ptrace(PTRACE_CONT, ctx->pid, 0, 0);

    int wstatus;
    waitpid(ctx->pid, &wstatus, 0);

    if (WIFEXITED(wstatus)) {
        printf("Debugged program exited normally\n");
    }
    else if (WIFSTOPPED(wstatus)) {
        int sig = WSTOPSIG(wstatus);
        sig_catch(sig);
    }

    return 0;
}
shell_cmd(continue, resume);

static void sig_catch(int sig)
{
    switch (sig) {
    default :
        printf("A signal has been caught but no action has been implemented\n");
    }
}

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

int info_mem(ctx_t *ctx, char *arg)
{
    char path[64];
    sprintf(path, "/proc/%i/maps", ctx->pid);

    FILE *map = fopen(path, "r");
    if (!map) {
        return -1;
    }

    char c;
    while((c = fgetc(map)) != EOF) {
        printf("%c", c);
    }

    fclose(map);

    return 0;
}
shell_cmd(info_mem, info_mem);

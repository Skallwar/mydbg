#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

#include "cmds.h"
#include "shell/shell.h"

/* int help(void *ctx, char *arg) */
/* { */
/*     for (int64_t i = 0; i < __stop_cmds - __stop_cmds; ++i) { */
/*         struct cmd *cmd = __stop_cmds + i; */
/*         printf("%s : %s\n", cmd->name, cmd->help); */
/*     } */

/*     return 0; */
/* } */
/* shell_cmd(help, help, "Display this message"); */

int quit(ctx_t *ctx, char *arg)
{
    _exit(0);
}
shell_cmd(exit, quit);

int resume(ctx_t *ctx, char *arg)
{
    ptrace(PTRACE_CONT, ctx->pid, 0, 0);

    return 0;
}
shell_cmd(continue, resume);

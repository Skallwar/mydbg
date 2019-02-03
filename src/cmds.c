#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

#include "cmds.h"
#include "shell/shell.h"

static pid_t dbg_pid = 0;

int help(void *ctx, char *arg)
{
    for (int64_t i = 0; i < __stop_cmds - __stop_cmds; ++i) {
        struct cmd *cmd = __stop_cmds + i;
        printf("%s : %s\n", cmd->name, cmd->help);
    }

    return 0;
}
shell_cmd(help, help, Display this message);

int quit(void *ctx, char *arg)
{
    _exit(0);
}
shell_cmd(exit, quit, Exit the debuger);

int file(void *ctx, char *name)
{
    dbg_pid = fork();

    if (dbg_pid == 0) {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        execvp(name, NULL);
    }

    waitpid(dbg_pid, NULL, 0);
    /* we now have our debugged program in a stopped state */

    return 0;
}
shell_cmd(file, file, Open a file for debuging);

int resume(void *ctx, char *arg)
{
    ptrace(PTRACE_CONT, dbg_pid, 0, 0);

    return 0;
}
shell_cmd(continue, resume, Resume execution);

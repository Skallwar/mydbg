#define _POSIX_C_SOURCE
#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <signal.h>

/* int help(void *ctx, char *arg) */
/* { */
/*     for (int64_t i = 0; i < __stop_cmds - __stop_cmds; ++i) { */
/*         struct cmd *cmd = __stop_cmds + i; */
/*         printf("%s : %s\n", cmd->name, cmd->help); */
/*     } */

/*     return 0; */
/* } */
/* shell_cmd(help, help, "Display this message"); */



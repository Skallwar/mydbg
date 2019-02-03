#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <assert.h>

#include "shell.h"


static struct cmd *find_cmd(const char *buf);
static int exec_cmd(struct cmd *cmd, char *buf);
static char **readline_cmd_complete(const char *str, int start, int end);
static char *readline_cmd_generator(const char *str, int);

void shell_start(const char *name)
{
    assert(name);

    rl_attempted_completion_function = readline_cmd_complete;

    while (1) {
        char *buf = readline(name);

        if (buf) {
            add_history(buf);

            char *name = strtok(buf, " ");
            char *arg = strtok(NULL, " ");

            /* printf("Name : %s, Arg : %s\n", name, arg); */

            struct cmd *cmd = find_cmd(name);
            if (cmd) {
                exec_cmd(cmd, arg);
            }

        }

        free(buf);
    }
}

static struct cmd *find_cmd(const char *buf)
{
    assert(buf);

    for (int64_t i = 0; i < __stop_cmds - __start_cmds; ++i) {
        struct cmd *cmd = __start_cmds + i;
        if (!strcmp(buf, cmd->name)) {
            return cmd;
        }
    }

    return NULL;
}

static int exec_cmd(struct cmd *cmd, char *buf)
{
    assert(cmd);

    return cmd->fn(NULL, buf);
}

static char **readline_cmd_complete(const char *buf, int start, int end)
{
    rl_attempted_completion_over = 1;

    char **match = rl_completion_matches(buf, readline_cmd_generator);

    return match;
}

static char *readline_cmd_generator(const char *buf, int state)
{
    static int cmds_index, len;

    if (!state) {
        cmds_index = 0;
        len = strlen(buf);
    }

    while (cmds_index < __stop_cmds - __start_cmds) {
        struct cmd *cmd = __start_cmds + cmds_index++;
        if (strncmp(cmd->name, buf, len) == 0) {
            return strdup(cmd->name);
        }
    }

    return NULL;
}

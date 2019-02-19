#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <assert.h>

#include "shell.h"
#include "cmds/cmds.h"

static struct cmd *find_cmd(const char *buf);
static int exec_cmd(struct cmd *cmd, void *ctx, char *buf);
static char **readline_cmd_complete(const char *str, int start, int end);
static char *readline_cmd_generator(const char *str, int);

static bool shell_status = true;

void shell_start(const char *name, void *ctx)
{
    assert(name);

    rl_attempted_completion_function = readline_cmd_complete;

    while (shell_status) {
        char *buf = readline(name);

        if (buf) {
            add_history(buf);

            char *arg = buf;
            while (*arg != '\0' && *arg != ' ') {
                ++arg;
            }
            *arg++ = '\0';

            struct cmd *cmd = find_cmd(buf);
            if (!cmd) {
                printf("No command found\n");
            }
            else {
                int ret = exec_cmd(cmd, ctx, arg);
                if (ret < 0) {
                    printf("An error occured in the last command\n");
                }
            }
        }

        free(buf);
    }
}

void shell_stop()
{
    shell_status = false;
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

static int exec_cmd(struct cmd *cmd, void *ctx, char *buf)
{
    assert(cmd);

    return cmd->fn(ctx, buf);
}

static char **readline_cmd_complete(const char *buf,
                                    int start UNUSED,
                                    int end UNUSED)
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

char **shell_tokenize(char *buf, size_t size)
{
    char **args = malloc(size * sizeof(*args));
    if (!args) {
        return NULL;
    }

    args[0] = strtok(buf, " ");
    if (!args[0]) {
        free(args);
        return NULL;
    }

    for (size_t i = 1; i < size; ++i) {
        char *token = strtok(NULL, " ");
        if (!token) {
            free(args);
            return NULL;
        }

        args[i] = token;
    }

    return args;
}

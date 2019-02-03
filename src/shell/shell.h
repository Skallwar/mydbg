#ifndef SHELL_H
#define SHELL_H

struct cmd {
    const char *name;
    int (*fn)(void *, char *);
};

#define shell_cmd(cmd_name, func) \
    static struct cmd __cmd_ ## cmd_name \
    __attribute__ ((section("cmds"), used)) = \
    {.name = #cmd_name, .fn = func}

extern struct cmd __start_cmds[];
extern struct cmd __stop_cmds[];

void shell_start(const char *name);
void shell_end(void);

#endif

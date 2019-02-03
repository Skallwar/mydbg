#ifndef SHELL_H
#define SHELL_H

struct cmd {
    const char *name;
    const char *help;
    int (*fn)(void *, char *);
};

#define shell_cmd(namestr, func, helpstr) \
    static struct cmd __cmd_ ## namestr \
    __attribute__ ((section("cmds"), used)) = \
    {.name = #namestr, .fn = func, .help = #helpstr}

extern struct cmd __start_cmds[];
extern struct cmd __stop_cmds[];

void shell_start(const char *name);
void shell_end(void);

#endif

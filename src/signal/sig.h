#ifndef SIG_H
#define SIG_H

#include <sys/types.h>

#include "dbg.h"

int sig_catch(pid_t pid);
int sig_handler(ctx_t *ctx, int sig);

#endif

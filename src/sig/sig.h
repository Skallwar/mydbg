#ifndef SIG_H
#define SIG_H

#include <sys/types.h>

int sig_catch(pid_t pid);
int sig_handler(int sig);

#endif

#ifndef REGS_H
#define REGS_H

#include <sys/types.h>
#include <sys/user.h>

void regs_get(pid_t pid, struct user_regs_struct *regs);
void regs_set(pid_t pid, struct user_regs_struct *regs);

#endif

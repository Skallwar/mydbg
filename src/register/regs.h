#ifndef REGS_H
#define REGS_H

#include <sys/types.h>
#include <sys/user.h>

#define print_reg(regs, name) printf("%s: 0x%llx\n", #name, (regs).name)
#define reg_get(regs, name) (regs)->name
#define reg_set(regs, name, val) (regs)->name = val

void regs_get(pid_t pid, struct user_regs_struct *regs);
void regs_set(pid_t pid, struct user_regs_struct *regs);

#endif

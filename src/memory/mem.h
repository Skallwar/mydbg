#ifndef MEM_H
#define MEM_H

#include <sys/types.h>
#include <stdint.h>

int read_mem(pid_t pid, uint64_t *addr, uint8_t *buf, size_t size);
int ptrace_write_mem(pid_t pid, uint64_t *addr, uint64_t *buf, size_t size);
int ptrace_read_mem(pid_t pid, uint64_t *addr, uint64_t *buf, size_t size);

#endif

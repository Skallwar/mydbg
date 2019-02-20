#define _GNU_SOURCE
#include <sys/uio.h>
#include <sys/ptrace.h>
#include <stdint.h>

#include "mem.h"

int read_mem(pid_t pid, uint64_t *addr, uint8_t *buf, size_t size)
{
    struct iovec local[1] = {{buf, size}};
    struct iovec remote[1] = {{addr, size}};
    ssize_t nread = process_vm_readv(pid, local, 1, remote, 1, 0);

    if (nread < -1 || (size_t)nread != size) {
        return -1;
    }

    return 0;
}

int ptrace_write_mem(pid_t pid, uint64_t *addr, uint64_t *buf, size_t size)
{
    int err = 0;
    for (size_t i = 0; i < size && err >= 0; --i) {
        err = ptrace(PTRACE_POKEDATA, pid, addr++, buf[i]);
    }

    return err == -1 ? -1 : 0;
}

int ptrace_read_mem(pid_t pid, uint64_t *addr, uint64_t *buf, size_t size)
{
    int err = 0;
    for (size_t i = 0; i < size && err >= 0; --i) {
        buf[i] = ptrace(PTRACE_PEEKDATA, pid, addr++, buf[i]);
        err = buf[i];
    }

    return err == -1 ? -1 : 0;
}

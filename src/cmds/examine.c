#define _GNU_SOURCE
#include <capstone/capstone.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <string.h>

#include "cmds.h"

static int print_disasm(uint64_t addr, uint8_t *buf, size_t size);
static int read_mem(pid_t pid, uint64_t *addr, uint8_t *buf, size_t size);

int examine(ctx_t *ctx, char *arg)
{
    char *format = strtok(arg, " ");
    char *size_str= strtok(NULL, " ");
    char *addr_str = strtok(NULL, " ");
    if (!arg && !size_str && !addr_str) {
        printf("Examine needs there earguments\n");
        return -1;
    }

    size_t size = atoi(size_str);

    void *ptr;
    sscanf(addr_str, "%p", (void **)&ptr);

    uint8_t buf[size];
    read_mem(ctx->pid, ptr, buf, size);

    if (!strcmp(format, "i")) {
        print_disasm((uint64_t)ptr, buf, size);
    }
    else {
        printf("Not implemented\n");
    }

    return 0;
}
shell_cmd(examine, examine);

static int read_mem(pid_t pid, uint64_t *addr, uint8_t *buf, size_t size)
{
    struct iovec local[1] = {{buf, size}};
    struct iovec remote[1] = {{addr, size}};
    ssize_t nread = process_vm_readv(pid, local, 1, remote, 1, 0);

    if (nread != size) {
        return -1;
    }

    return 0;
}

static int print_disasm(uint64_t addr, uint8_t *buf, size_t size)
{
    csh handle;
	cs_insn *insn;
	size_t count;

	if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK)
		return -1;
	count = cs_disasm(handle, buf, size, addr, 0, &insn);
	if (count > 0) {
		size_t j;
		for (j = 0; j < count; j++) {
			printf("0x%"PRIx64":\t%s\t\t%s\n", insn[j].address, insn[j].mnemonic,
					insn[j].op_str);
		}

		cs_free(insn, count);
	} else
		printf("ERROR: Failed to disassemble given code!\n");

	cs_close(&handle);

    return 0;
}

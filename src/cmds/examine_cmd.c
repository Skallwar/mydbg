#define _GNU_SOURCE
#include <capstone/capstone.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <string.h>

#include "cmds.h"
#include "memory/mem.h"
#include "shell/shell.h"

static int print_disasm(uint64_t addr, uint8_t *buf, size_t size);
static void print_hex(uint8_t *buf, char *addr, size_t size);

int examine_cmd(ctx_t *ctx, char *arg)
{
    /* Get token and parse them */
    char **args = shell_tokenize(arg, 3);
    if (!args) {
        return -1;
    }

    /* Format args */
    char format = *args[0];
    size_t size = atoi(args[1]);
    char *addr_str = args[2];
    void *addr;
    sscanf(addr_str, "%p", (void **)&addr);
    free(args);

    uint8_t buf[size];
    read_mem(ctx->pid, addr, buf, size);

    switch (format) {
    case 'i':
        if (print_disasm((uint64_t)addr, buf, size) < 0) {
            return -1;
        }
        break;
    case 'x':
        print_hex(buf, addr_str, size);
        break;
    default :
        printf("Format specified is not valid\n");
        return -1;
    }

    return 0;
}
shell_cmd(examine, examine_cmd);

static void print_hex(uint8_t *buf, char *addr, size_t size)
{
    printf("%s = 0x", addr);
    for (size_t i = 0; i < size; ++i) {
        printf("%X", buf[i]);
    }
    printf("\n");
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
	} else {
		printf("ERROR: Failed to disassemble given code!\n");
        cs_close(&handle);
        return -1;
    }

	cs_close(&handle);

    return 0;
}

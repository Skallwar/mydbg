#include <capstone/capstone.h>
#include <stdio.h>

#include "caprock.h"
#include "memory/mem.h"

int print_disasm(uint64_t addr, uint8_t *buf, size_t size)
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

int instr_size(ctx_t *ctx, uint64_t addr)
{
    csh handle;
	cs_insn *insn;

	if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK)
		return -1;

    size_t size = 0;
    for (int count = -1; count != 1; ++size) {
        uint8_t buf[size];
        read_mem(ctx->pid, (uint64_t *)addr, buf, size);

        count = cs_disasm(handle, buf, size, addr, 0, &insn);
    }

    cs_free(insn, 1);
    cs_close(&handle);

    return size;
}

#include "exec/helper.h"
#include "cpu/modrm.h"
#include "ui/ui.h"
#include "ui/breakpoint.h"
#include "nemu.h"
#include <setjmp.h>
extern uint8_t current_sreg;
extern jmp_buf jbuf;
void raise_inst(uint8_t NO);

make_helper(inv) {
	/* invalid opcode */

	uint8_t temp[8];
	((uint32_t *)temp)[0] = instr_fetch(eip, 4);
	((uint32_t *)temp)[1] = instr_fetch(eip + 4, 4);
	printf("invalid opcode(eip = 0x%08x): %02x %02x %02x %02x %02x %02x %02x %02x ...\n", 
			eip, temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7]);

	assert(0);
}

make_helper(int3) {
	/* A breakpoint is hit! Do something here! */
    nemu_state=INT;

	return 1;
}

make_helper(nemu_trap) {
	if(cpu.eax == 0x2)
	{
		printf("hello world\n");
		return 1;
		
	}
	printf("nemu: HIT \33[1;31m%s\33[0m TRAP at eip = 0x%08x\n\n", (cpu.eax == 0 ? "GOOD" : "BAD"), cpu.eip);
	nemu_state = END;

	print_asm("nemu trap");
	return 1;
}

make_helper(int_imm)
{
	current_sreg = SS;
	cpu.esp -= 4;
	swaddr_write(cpu.esp , 4 , cpu.EFLAGS);
	cpu.esp -= 2;
	swaddr_write(cpu.esp ,2 , cpu.cs);
	cpu.esp -= 4;
	swaddr_write(cpu.esp , 4 ,cpu.eip);
	uint8_t NO = instr_fetch(eip + 1 , 1);
	raise_inst(NO);
	return 2;
}



void raise_inst(uint8_t NO)
{
	uint32_t idt_index = cpu.idtr.base + NO * 8;
	uint32_t val1 = swaddr_read(idt_index , 4);
	uint32_t val2 = swaddr_read(idt_index + 4 , 4);
	cpu.cs = val1 >> 16;
	uint32_t offset = (val1 & 0x0000ffff) + (val2 & 0xffff0000);
	uint16_t index = cpu.cs;
	uint32_t gdt_index = cpu.gdtr.base + (index & 0xfff8);
	uint32_t val3 = swaddr_read(gdt_index , 4);
	uint32_t val4 = swaddr_read(gdt_index + 4 , 4);
	cpu.sreg_discribe[CS].base = (val3 >> 16) | ((val4 & 0x000000ff) << 16) | (val4 & 0xff000000);
	cpu.eip = cpu.sreg_discribe[CS].base + offset;
	longjmp(jbuf , 1);
}

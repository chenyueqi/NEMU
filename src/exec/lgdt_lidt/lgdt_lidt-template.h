#include "exec/helper.h"
#include "cpu/modrm.h"
#include "exec/template-start.h"

make_helper(concat(lgdt_lidt_,SUFFIX))
{
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	if(m.reg == 0x02)
	{
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		if(DATA_BYTE == 2)
		{
			uint16_t limit = swaddr_read(addr , 2);
			uint32_t base = swaddr_read(addr + 1, 4);
			cpu.gdtr.limit = limit;
			cpu.gdtr.base = base & 0x00ffffff;
			
		}
		else if(DATA_BYTE == 4)
		{
			uint16_t limit = swaddr_read(addr, 2);
			uint32_t base = swaddr_read(addr + 2, 4);
			cpu.gdtr.limit = limit;
			cpu.gdtr.base = base;
		}
		print_asm("lgdt" str(SUFFIX)  " %s" , ModR_M_asm);
		return len + 1; 
	}
	else if(m.reg == 3)
	{
		swaddr_t addr;
		int len = read_ModR_M(eip + 1 , &addr);
		if(DATA_BYTE == 2)
		{
			uint16_t limit = swaddr_read(addr  , 2);
			uint32_t base = swaddr_read(addr + 1 , 4);
			cpu.idtr.limit = limit;
			cpu.idtr.base = base & 0x00ffffff;
		}
		else if(DATA_BYTE == 4)
		{
			uint16_t limit = swaddr_read(addr , 2);
			uint32_t base = swaddr_read(addr + 2 , 4);
			cpu.idtr.limit = limit;
			cpu.idtr.base = base;
		}
		print_asm("lidt" str(SUFFIX) " %s" , ModR_M_asm);
		return len + 1;
	}
	else
	{
		print_asm("fuck !!");
		return 0;
	}
}

#include "exec/template-end.h"

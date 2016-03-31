#include "exec/helper.h"
#include "cpu/modrm.h"
#include "cpu/reg.h"
void init_tlb();
make_helper(mov_cr2r_l)
{
	ModR_M m;
	m.val = instr_fetch(eip + 1 , 1);
	if(m.R_M == 0)
	{
		reg_l(m.reg) = cpu.cr0;
		print_asm("movl	%%cr0,%%%s",regsl[m.R_M]);
	}
	else if(m.R_M == 3)
	{
		reg_l(m.reg) = cpu.cr3;
		print_asm("movl	%%cr3,%%%s",regsl[m.R_M]);
	}
	return 2 ; 

}

make_helper(mov_r2cr_l)
{
	ModR_M m;
	m.val = instr_fetch(eip + 1 , 1);
	if(m.reg == 0)
	{
		cpu.cr0 = reg_l(m.R_M);
		print_asm("movl %%%s, %%cr0" , regsl[m.R_M]);
	}
	else if(m.reg == 3)
	{
		init_tlb();
		cpu.cr3 = reg_l(m.R_M);
		print_asm("movl %%%s, %%cr3" , regsl[m.R_M]);
	}
	return 2 ;

}

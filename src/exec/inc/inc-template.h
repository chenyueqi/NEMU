#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "../flag/flag.h"

make_helper(concat(concat(Operator,_rm_),SUFFIX))
{
    	ModR_M m;
    	m.val=instr_fetch(eip+1,1);
    	if(m.mod==3)
    	{
        	DATA_TYPE add=REG(m.R_M);
        	if(sign)
			REG(m.R_M)+=1;
		else
			REG(m.R_M)-=1;
        	DATA_TYPE result=REG(m.R_M);
        	bool cf=cpu.CF;
        	if(sign)
		{
        		add_flags(MSB(add),0,MSB(result), (uint32_t) result);
			print_asm("inc"str(SUFFIX) " %%%s",REG_NAME(m.R_M));
		}
		else
		{
        		sub_flags(MSB(add),1,MSB(result), (uint32_t) result);
			print_asm("dec"str(SUFFIX) " %%%s",REG_NAME(m.R_M));
		}
        	cpu.CF=cf;
        	return 2;
    	}
    	else
    	{
        	swaddr_t addr;
        	int len = read_ModR_M(eip+1,&addr);
        	DATA_TYPE add=MEM_R(addr);
		if(sign)
        		MEM_W(addr,MEM_R(addr)+1);
		else
        		MEM_W(addr,MEM_R(addr)-1);
        	DATA_TYPE result=MEM_R(addr);
        	bool cf=cpu.CF;
		if(sign)
		{
        		add_flags(MSB(add),0,MSB(result), (uint32_t) result);
        		print_asm("inc"str(SUFFIX) " %s",ModR_M_asm);
		}
		else
		{
        		sub_flags(MSB(add),1,MSB(result), (uint32_t) result);
        		print_asm("dec"str(SUFFIX) " %s",ModR_M_asm);
		}
        	cpu.CF=cf;
        	return len + 1;
    	}
}

make_helper(concat(concat(Operator,_r_),SUFFIX))
{
    	int reg_code = instr_fetch(eip,1)&0x7;
    	DATA_TYPE add=REG(reg_code); 
    	if(sign)
    		REG(reg_code)+=1;
    	else
    		REG(reg_code)-=1;

    	DATA_TYPE result=REG(reg_code);
    	bool cf=cpu.CF;
	if(sign)
	{
    		add_flags(MSB(add),0,MSB(result), (uint32_t) result);
    		print_asm("inc" str(SUFFIX) " %%%s",REG_NAME(reg_code));
	}
	else
	{
    		sub_flags(MSB(add),1,MSB(result), (uint32_t) result);
    		print_asm("dec" str(SUFFIX) " %%%s",REG_NAME(reg_code));

	}
    	cpu.CF=cf;
    	return 1;
}
#include "exec/template-end.h"

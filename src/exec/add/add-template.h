#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "../flag/flag.h"

make_helper(concat(concat(Operator,_i2a_),SUFFIX))
{
    	DATA_TYPE add = REG(R_EAX);
    	DATA_TYPE imm = instr_fetch(eip+1,DATA_BYTE);
    	switch(sign)
	{
		case 1:REG(R_EAX)=REG(R_EAX)+imm;break;
		case 0:REG(R_EAX)=REG(R_EAX)+imm+cpu.CF;break;
		case 3:REG(R_EAX)=REG(R_EAX)-imm;break;
		case 2:REG(R_EAX)=REG(R_EAX)-imm-cpu.CF;break;
	}
	DATA_TYPE result = REG(R_EAX);
	switch(sign)
	{	
		case 1:add_flags(MSB(add), MSB(imm), MSB(result), (uint32_t) result);
		print_asm("add"str(SUFFIX)" $0x%x,%s",imm,REG_NAME(R_EAX));break;
		case 0:add_flags(MSB(add), MSB(imm+cpu.CF), MSB(result), (uint32_t) result);
		print_asm("adc"str(SUFFIX)" $0x%x,%s",imm,REG_NAME(R_EAX));break;
		case 3:sub_flags(MSB(add), !MSB(imm), MSB(result), (uint32_t) result);
		print_asm("sub"str(SUFFIX)" $0x%x,%s",imm,REG_NAME(R_EAX));break;
		case 2:sub_flags(MSB(add), !MSB(imm+cpu.CF), MSB(result), (uint32_t) result);
		print_asm("sbb"str(SUFFIX)" $0x%x,%s",imm,REG_NAME(R_EAX));break;
	}
	return DATA_BYTE+1;
}

make_helper(concat(concat(Operator,_r2rm_),SUFFIX))
{
	 ModR_M m;
	 m.val = instr_fetch(eip + 1,1);
	 if(m.mod==3)
	 {
        	DATA_TYPE add = REG(m.R_M);
        	DATA_TYPE add2 = REG(m.reg);
		switch(sign)
		{
			case 1:REG(m.R_M)=REG(m.R_M)+REG(m.reg);break;
			case 0:REG(m.R_M)=REG(m.R_M)+REG(m.reg)+cpu.CF;break;
			case 3:REG(m.R_M)=REG(m.R_M)-REG(m.reg);break;
			case 2:REG(m.R_M)=REG(m.R_M)-REG(m.reg)-cpu.CF;break;
		}
		DATA_TYPE result=REG(m.R_M);
		switch(sign)
		{
			case 1:add_flags(MSB(add), MSB(add2), MSB(result), (uint32_t) result);
			print_asm("add"str(SUFFIX) " %%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));break;	
			case 0:add_flags(MSB(add), MSB(add2+cpu.CF), MSB(result), (uint32_t) result);
			print_asm("adc"str(SUFFIX) " %%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));break;
			case 3:sub_flags(MSB(add), !MSB(add2), MSB(result), (uint32_t) result);
			print_asm("sub"str(SUFFIX) " %%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));break;	
			case 2:sub_flags(MSB(add), !MSB(add2+cpu.CF), MSB(result), (uint32_t) result);
			print_asm("sbb"str(SUFFIX) " %%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));break;
		}
        	return 2;
    	}
    	else
    	{
    	    	swaddr_t addr;
	    	int len=read_ModR_M(eip+1,&addr);
	    	DATA_TYPE add=MEM_R(addr);
	    	DATA_TYPE add2 = REG(m.reg);
	   	switch(sign)
		{
			case 1: MEM_W(addr,MEM_R(addr)+REG(m.reg));break;
			case 0: MEM_W(addr,MEM_R(addr)+REG(m.reg)+cpu.CF);break;
			case 3: MEM_W(addr,MEM_R(addr)-REG(m.reg));break;
			case 2: MEM_W(addr,MEM_R(addr)-REG(m.reg)-cpu.CF);break;
		}
		DATA_TYPE result=MEM_R(addr);
	    	switch(sign)
	    	{
			case 1:add_flags(MSB(add), MSB(add2), MSB(result), (uint32_t) result);
		    	print_asm("add"str(SUFFIX) " %%%s,%s",REG_NAME(m.reg), ModR_M_asm);break;
			case 0:add_flags(MSB(add), MSB(add2+cpu.CF), MSB(result), (uint32_t) result);
		    	print_asm("adc"str(SUFFIX) " %%%s,%s",REG_NAME(m.reg), ModR_M_asm);break;
			case 3:sub_flags(MSB(add), !MSB(add2), MSB(result), (uint32_t) result);
		    	print_asm("sub"str(SUFFIX) " %%%s,%s",REG_NAME(m.reg), ModR_M_asm);break;
			case 2:sub_flags(MSB(add), !MSB(add2+cpu.CF), MSB(result), (uint32_t) result);
		    	print_asm("sbb"str(SUFFIX) " %%%s,%s",REG_NAME(m.reg), ModR_M_asm);break;
	    }
        	return len+1;
    }
}

make_helper(concat(concat(Operator,_rm2r_),SUFFIX))
{
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	if(m.mod==3)
    	{
        	DATA_TYPE add=REG(m.reg);
        	DATA_TYPE add2=REG(m.R_M);
		switch(sign)
		{
			case 1:REG(m.reg)=REG(m.reg)+REG(m.R_M);break;
			case 0:REG(m.reg)=REG(m.reg)+REG(m.R_M)+cpu.CF;break;
			case 3:REG(m.reg)=REG(m.reg)-REG(m.R_M);break;
			case 2:REG(m.reg)=REG(m.reg)-REG(m.R_M)-cpu.CF;break;
		}
		DATA_TYPE result=REG(m.reg);
		switch(sign)
		{
			case 1:add_flags(MSB(add), MSB(add2), MSB(result), (uint32_t) result);
        		print_asm("add"str(SUFFIX) " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));break;
			case 0:add_flags(MSB(add), MSB(add2+cpu.CF), MSB(result), (uint32_t) result);
        		print_asm("adc"str(SUFFIX) " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));break;
			case 3:sub_flags(MSB(add), !MSB(add2), MSB(result), (uint32_t) result);
        		print_asm("sub"str(SUFFIX) " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));break;
			case 2:sub_flags(MSB(add), !MSB(add2+cpu.CF), MSB(result), (uint32_t) result);
        		print_asm("sbb"str(SUFFIX) " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));break;

		}
        	return 2;
    	}
    	else
    	{
        	swaddr_t addr;
	        int len=read_ModR_M(eip+1,&addr);
        	DATA_TYPE add=REG(m.reg);
      		DATA_TYPE add2=MEM_R(addr);
		switch(sign)
		{
			case 1:REG(m.reg)=REG(m.reg)+MEM_R(addr);break;
			case 0:REG(m.reg)=REG(m.reg)+MEM_R(addr)+cpu.CF;break;
			case 3:REG(m.reg)=REG(m.reg)-MEM_R(addr);break;
			case 2:REG(m.reg)=REG(m.reg)-MEM_R(addr)-cpu.CF;break;
		}
		DATA_TYPE result=REG(m.reg);
		switch(sign)
		{
			case 1:add_flags(MSB(add), MSB(add2), MSB(result), (uint32_t) result);
        		print_asm("add"str(SUFFIX) " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));break;
			case 0:add_flags(MSB(add), MSB(add2+cpu.CF), MSB(result), (uint32_t) result);
        		print_asm("adc"str(SUFFIX) " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));break;
			case 3:sub_flags(MSB(add), !MSB(add2), MSB(result), (uint32_t) result);
        		print_asm("sub"str(SUFFIX) " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));break;
			case 2:sub_flags(MSB(add), !MSB(add2+cpu.CF), MSB(result), (uint32_t) result);
        		print_asm("sbb"str(SUFFIX) " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));break;
		}
        	return len+1;
    	}
}

make_helper(concat(concat(Operator,_ib2rm_),SUFFIX))
{
    	ModR_M m;
    	m.val = instr_fetch(eip + 1,1);
    	if(m.mod==3)
    	{
        	int8_t instr=instr_fetch(eip+2,1);
        	DATA_TYPE_S imm_temp=instr;
        	DATA_TYPE imm=imm_temp;
        	DATA_TYPE add=REG(m.R_M);
		switch(sign)
		{
			case 1:REG(m.R_M)=REG(m.R_M)+imm;break;
			case 0:REG(m.R_M)=REG(m.R_M)+imm+cpu.CF;break;
			case 3:REG(m.R_M)=REG(m.R_M)-imm;break;
			case 2:REG(m.R_M)=REG(m.R_M)-imm-cpu.CF;break;
		}
		DATA_TYPE result=REG(m.R_M);
		switch(sign)
		{
			case 1:add_flags(MSB(add), MSB(imm), MSB(result), (uint32_t) result);
        		print_asm("add"str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));break;
			case 0:add_flags(MSB(add), MSB(imm + cpu.CF), MSB(result), (uint32_t) result);
        		print_asm("adc"str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));break;
			case 3:sub_flags(MSB(add), !MSB(imm), MSB(result), (uint32_t) result);
        		print_asm("sub"str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));break;
			case 2:sub_flags(MSB(add), !MSB(imm + cpu.CF), MSB(result), (uint32_t) result);
        		print_asm("sbb"str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));break;
		}
        	return 3;
    }
    else
    {
        	swaddr_t addr;
	        int len=read_ModR_M(eip+1,&addr);
       		int8_t instr=instr_fetch(eip+len+1,1);
        	DATA_TYPE_S imm_temp=instr;
        	DATA_TYPE imm=imm_temp;
        	DATA_TYPE add=MEM_R(addr);
		switch(sign)
		{
        		case 1:MEM_W(addr,MEM_R(addr)+imm);break;
			case 0:MEM_W(addr,MEM_R(addr)+imm+cpu.CF);break;
        		case 3:MEM_W(addr,MEM_R(addr)-imm);break;
			case 2:MEM_W(addr,MEM_R(addr)-imm-cpu.CF);break;
		}
	        DATA_TYPE result=MEM_R(addr);
		switch(sign)
		{
			case 1:add_flags(MSB(add), MSB(imm), MSB(result), (uint32_t) result);
    			print_asm("add"str(SUFFIX) " $0x%x,%s",imm, ModR_M_asm);break;
			case 0:add_flags(MSB(add), MSB(imm+cpu.CF), MSB(result), (uint32_t) result);
    			print_asm("adc"str(SUFFIX) " $0x%x,%s",imm, ModR_M_asm);break;
			case 3:sub_flags(MSB(add), !MSB(imm), MSB(result), (uint32_t) result);
    			print_asm("sub"str(SUFFIX) " $0x%x,%s",imm, ModR_M_asm);break;
			case 2:sub_flags(MSB(add), !MSB(imm+cpu.CF), MSB(result), (uint32_t) result);
    			print_asm("sbb"str(SUFFIX) " $0x%x,%s",imm, ModR_M_asm);break;
		}
        	return len+2;
    }
}

make_helper(concat(concat(Operator,_i2rm_),SUFFIX))
{
    	ModR_M m;
    	m.val = instr_fetch(eip + 1,1);
    	if(m.mod==3)
    	{
       		DATA_TYPE imm=instr_fetch(eip+2,DATA_BYTE);
        	DATA_TYPE add=REG(m.R_M);
		switch(sign)
		{
			case 1:REG(m.R_M)=REG(m.R_M)+imm;break;
			case 0:REG(m.R_M)=REG(m.R_M)+imm+cpu.CF;break;
			case 3:REG(m.R_M)=REG(m.R_M)-imm;break;
			case 2:REG(m.R_M)=REG(m.R_M)-imm-cpu.CF;break;
		}
	       	DATA_TYPE result=REG(m.R_M);
		switch(sign)
		{
			case 1:add_flags(MSB(add), MSB(imm), MSB(result), (uint32_t) result);
        		print_asm("add"str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));break;
			case 0:add_flags(MSB(add), MSB(imm+cpu.CF), MSB(result), (uint32_t) result);
        		print_asm("adc"str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));break;  
			case 3:sub_flags(MSB(add), !MSB(imm), MSB(result), (uint32_t) result);
        		print_asm("add"str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));break;
			case 2:sub_flags(MSB(add), !MSB(imm+cpu.CF), MSB(result), (uint32_t) result);
        		print_asm("adc"str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));break;  
		}
        	return DATA_BYTE+2;
    	}
    	else
    	{
        	swaddr_t addr;
        	int len=read_ModR_M(eip+1,&addr);
        	DATA_TYPE imm=instr_fetch(eip+len+1,DATA_BYTE);
        	DATA_TYPE add=MEM_R(addr);
		switch(sign)
		{
			case 1:MEM_W(addr,MEM_R(addr)+imm);break;
			case 0:MEM_W(addr,MEM_R(addr)+cpu.CF+imm);break;
			case 3:MEM_W(addr,MEM_R(addr)-imm);break;
			case 2:MEM_W(addr,MEM_R(addr)-cpu.CF-imm);break;
		}
	        DATA_TYPE result=MEM_R(addr);
		switch(sign)
		{
			case 1:add_flags(MSB(add), MSB(imm), MSB(result), (uint32_t) result);
        		print_asm("add"str(SUFFIX) " $0x%x,%s",imm, ModR_M_asm);break;
			case 0:add_flags(MSB(add), MSB(imm+cpu.CF), MSB(result), (uint32_t) result);
        		print_asm("adc"str(SUFFIX) " $0x%x,%s",imm, ModR_M_asm);break;
			case 3:sub_flags(MSB(add), !MSB(imm), MSB(result), (uint32_t) result);
        		print_asm("sub"str(SUFFIX) " $0x%x,%s",imm, ModR_M_asm);break;
			case 2:sub_flags(MSB(add), !MSB(imm+cpu.CF), MSB(result), (uint32_t) result);
        		print_asm("sbb"str(SUFFIX) " $0x%x,%s",imm, ModR_M_asm);break;

		}
        	return len+1+DATA_BYTE;
    }
}

#include "exec/template-end.h"

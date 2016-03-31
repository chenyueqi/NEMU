#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "../flag/flag.h"

make_helper(concat(concat(Operator,_i2a_),SUFFIX))
{
    DATA_TYPE and1 = REG(R_EAX);
    DATA_TYPE imm = instr_fetch(eip+1,DATA_BYTE);
    switch(sign)
    {
	    case 0:REG(R_EAX)=REG(R_EAX) & imm;
	    print_asm("and"str(SUFFIX)" $0x%x,%s",imm,REG_NAME(R_EAX));break;
	    case 1:REG(R_EAX)=REG(R_EAX) | imm;
	    print_asm("or"str(SUFFIX)" $0x%x,%s",imm,REG_NAME(R_EAX));break;
	    case 2:REG(R_EAX)=REG(R_EAX) ^ imm;
	    print_asm("xor"str(SUFFIX)" $0x%x,%s",imm,REG_NAME(R_EAX));break;
    }
    DATA_TYPE result = REG(R_EAX);
    add_flags(MSB(and1), MSB(imm), MSB(result), (uint32_t) result);
    cpu.CF=0;
    cpu.OF=0;
    return DATA_BYTE+1;
}

make_helper(concat(concat(Operator,_r2rm_),SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    if(m.mod==3)
    {
        DATA_TYPE and1 = REG(m.R_M);
        DATA_TYPE and2 = REG(m.reg);
        switch(sign)
	{
		case 0:REG(m.R_M) = REG(m.reg) & REG(m.R_M);
        	print_asm("and"str(SUFFIX) " %%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));break;
		case 1:REG(m.R_M) = REG(m.reg) | REG(m.R_M);
        	print_asm("or"str(SUFFIX) " %%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));break;
		case 2:REG(m.R_M) = REG(m.reg) ^ REG(m.R_M);
        	print_asm("xor"str(SUFFIX) " %%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));break;
	}
	DATA_TYPE result=REG(m.R_M);
        add_flags(MSB(and1), MSB(and2), MSB(result), (uint32_t) result);
        cpu.CF = 0;
        cpu.OF = 0;
        return 2;
    }
    else
    {
        swaddr_t addr;
        int len=read_ModR_M(eip+1,&addr);
        DATA_TYPE and1=MEM_R(addr);
        DATA_TYPE and2 = REG(m.reg);
	switch(sign)
	{
		case 0:MEM_W(addr,REG(m.reg) & MEM_R(addr));
        	print_asm("and"str(SUFFIX) " %%%s,%s",REG_NAME(m.reg), ModR_M_asm);break;
		case 1:MEM_W(addr,REG(m.reg) | MEM_R(addr));
        	print_asm("or"str(SUFFIX) " %%%s,%s",REG_NAME(m.reg), ModR_M_asm);break;
		case 2:MEM_W(addr,REG(m.reg) ^ MEM_R(addr));
        	print_asm("xor"str(SUFFIX) " %%%s,%s",REG_NAME(m.reg), ModR_M_asm);break;
	}
        DATA_TYPE result=MEM_R(addr);
        add_flags(MSB(and1), MSB(and2), MSB(result), (uint32_t) result);
        cpu.CF = 0;
        cpu.OF = 0;
        return len+1;
    }
}

make_helper(concat(concat(Operator,_rm2r_),SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip+1,1);
    if(m.mod==3)
    {
        DATA_TYPE and1=REG(m.reg);
        DATA_TYPE and2=REG(m.R_M);
	switch(sign)
	{
		case 0:REG(m.reg)=REG(m.R_M) & REG(m.reg);
        	print_asm("and"str(SUFFIX) " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));break;
		case 1:REG(m.reg)=REG(m.R_M) | REG(m.reg);
        	print_asm("or"str(SUFFIX) " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));break;
		case 2:REG(m.reg)=REG(m.R_M) ^ REG(m.reg);
        	print_asm("xor"str(SUFFIX) " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));break;
	}
	DATA_TYPE result=REG(m.reg);
        add_flags(MSB(and1), MSB(and2), MSB(result), (uint32_t) result);
        cpu.CF = 0;
        cpu.OF = 0;
        return 2;
    }
    else
    {
        swaddr_t addr;
        int len=read_ModR_M(eip+1,&addr);
        DATA_TYPE and1=REG(m.reg);
        DATA_TYPE and2=MEM_R(addr);
	switch(sign)
	{
		case 0:REG(m.reg)=MEM_R(addr) & REG(m.reg);
        	print_asm("and"str(SUFFIX) " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));break;
		case 1:REG(m.reg)=MEM_R(addr) | REG(m.reg);
        	print_asm("or"str(SUFFIX) " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));break;
		case 2:REG(m.reg)=MEM_R(addr) ^ REG(m.reg);
        	print_asm("xor"str(SUFFIX) " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));break;
	}
	DATA_TYPE result=REG(m.reg);
        add_flags(MSB(and1), MSB(and2), MSB(result), (uint32_t) result);
        cpu.CF = 0;
        cpu.OF = 0;
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
        DATA_TYPE and1=REG(m.R_M);
	switch(sign)
	{
        	case 0:REG(m.R_M)=imm & REG(m.R_M);
        	print_asm("and"str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));break;
        	case 1:REG(m.R_M)=imm | REG(m.R_M);
        	print_asm("or"str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));break;
        	case 2:REG(m.R_M)=imm ^ REG(m.R_M);
        	print_asm("xor"str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));break;
	}
        DATA_TYPE result=REG(m.R_M);
        add_flags(MSB(and1), MSB(imm), MSB(result), (uint32_t) result);
        cpu.CF = 0;
        cpu.OF = 0;
        return 3;
    }
    else
    {
        swaddr_t addr;
        int len=read_ModR_M(eip+1,&addr);
        int8_t instr=instr_fetch(eip+len+1,1);
        DATA_TYPE_S imm_temp=instr;
        DATA_TYPE imm=imm_temp;
        DATA_TYPE and1=MEM_R(addr);
        switch(sign)
	{
		case 0:MEM_W(addr,imm & MEM_R(addr));
        	print_asm("and"str(SUFFIX) " $0x%x,%s",imm, ModR_M_asm);break;
		case 1:MEM_W(addr,imm | MEM_R(addr));
        	print_asm("or"str(SUFFIX) " $0x%x,%s",imm, ModR_M_asm);break;
		case 2:MEM_W(addr,imm ^ MEM_R(addr));
        	print_asm("xor"str(SUFFIX) " $0x%x,%s",imm, ModR_M_asm);break;
	}
        DATA_TYPE result=MEM_R(addr);
        add_flags(MSB(and1), MSB(imm), MSB(result), (uint32_t) result);
        cpu.CF = 0;
        cpu.OF = 0;
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
        DATA_TYPE and1=REG(m.R_M);
	switch(sign)
	{
		case 0:REG(m.R_M)=REG(m.R_M) & imm;
        	print_asm("and"str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));break;
		case 1:REG(m.R_M)=REG(m.R_M) | imm;
        	print_asm("or"str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));break;
		case 2:REG(m.R_M)=REG(m.R_M) ^ imm;
        	print_asm("xor"str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));break;
	}
        DATA_TYPE result=REG(m.R_M);
        add_flags(MSB(and1), MSB(imm), MSB(result), (uint32_t) result);
        cpu.CF = 0;
        cpu.OF = 0;
        return DATA_BYTE+2;
    }
    else
    {
        swaddr_t addr;
        int len=read_ModR_M(eip+1,&addr);
        DATA_TYPE imm=instr_fetch(eip+len+1,DATA_BYTE);
        DATA_TYPE and1=MEM_R(addr);
	switch(sign)
	{
		case 0:MEM_W(addr,imm & MEM_R(addr));
        	print_asm("and"str(SUFFIX) " $0x%x,%s",imm, ModR_M_asm);break;
		case 1:MEM_W(addr,imm | MEM_R(addr));
        	print_asm("or"str(SUFFIX) " $0x%x,%s",imm, ModR_M_asm);break;
		case 2:MEM_W(addr,imm ^ MEM_R(addr));
        	print_asm("xor"str(SUFFIX) " $0x%x,%s",imm, ModR_M_asm);break;
	}
        DATA_TYPE result=MEM_R(addr);
        add_flags(MSB(and1), MSB(imm), MSB(result), (uint32_t) result);
        cpu.CF = 0;
        cpu.OF = 0;
        return len+1+DATA_BYTE;
    }
}

#ifndef __SHIFT_

make_helper(concat(not_r_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    if(m.mod==3)
    {
        REG(m.R_M) = ~REG(m.R_M);
        print_asm("not"str(SUFFIX) " %%%s",REG_NAME(m.R_M));

        return 2;
    }
    else
    {
        swaddr_t addr;
        int len=read_ModR_M(eip+1,&addr);
        MEM_W(addr,~MEM_R(addr));

        print_asm("not"str(SUFFIX) " %s", ModR_M_asm);

        return len+1;
    }
}


make_helper(concat(sal_cl2rm_, SUFFIX))
{
    ModR_M m;
    DATA_TYPE dest;

    swaddr_t addr;
    int len = 0;
    m.val = instr_fetch(eip + 1,1);
    if(m.mod == 3)
    {
        dest = REG(m.R_M);
        print_asm("sal" "   %%cl,%%%s",REG_NAME(m.R_M));
    }
    else
    {
        len = read_ModR_M(eip + 1, &addr);
        dest = MEM_R(addr);
        print_asm("sal" "   %%cl,%%%s",ModR_M_asm);
    }
    uint8_t temp = reg_b(R_CL);
    if(temp == 1)    cpu.OF = MSB(dest) != cpu.CF;
    while(temp != 0)
    {
        cpu.CF = MSB(dest);
        dest = dest * 2;
        temp --;
    }
    if(dest == 0)    cpu.ZF = 1;
    else    cpu.ZF = 0;
    if(MSB(dest) == 1)    cpu.SF = 1;
    else    cpu.SF = 0;
    PF_W((uint32_t) dest);
    if(m.mod == 3)
    {
        REG(m.R_M) = dest;
        return 2;
    }
    else
    {
        MEM_W(addr, dest);
        return len + 1;
    }
}

make_helper(concat(sal_12rm_, SUFFIX))
{
    ModR_M m;
    DATA_TYPE dest;
    swaddr_t addr;
    int len = 0;
    m.val = instr_fetch(eip + 1,1);
    if(m.mod == 3)
    {
        dest = REG(m.R_M);
        print_asm("sal" "   $0x1,%%%s",REG_NAME(m.R_M));
    }
    else
    {
        len = read_ModR_M(eip + 1, &addr);
        dest = MEM_R(addr);
        print_asm("sal" "   $0x1,%%%s",ModR_M_asm);
    }
    uint8_t temp = 1;
    if(temp == 1)    cpu.OF = MSB(dest) != cpu.CF;
    while(temp != 0)
    {
        cpu.CF = MSB(dest);
        dest = dest * 2;
        temp --;
    }
    if(dest == 0)    cpu.ZF = 1;
    else    cpu.ZF = 0;
    if(MSB(dest) == 1)    cpu.SF = 1;
    else    cpu.SF = 0;
    PF_W((uint32_t) dest);
    if(m.mod == 3)
    {
        REG(m.R_M) = dest;
        return 2;
    }
    else
    {
        MEM_W(addr, dest);
        return len + 1;
    }
}

make_helper(concat(sal_ib2rm_, SUFFIX))
{
    ModR_M m;
    DATA_TYPE dest;

    swaddr_t addr;
    int len = 0;
    m.val = instr_fetch(eip + 1,1);
    uint8_t temp = 0;
    if(m.mod == 3)
    {
        temp = instr_fetch(eip + 2, 1);
    }
    else
    {
        temp = instr_fetch(eip + len + 1, 1);
    }
    if(m.mod == 3)
    {
        dest = REG(m.R_M);
        print_asm("sal" "   $0x%x,%%%s",temp,REG_NAME(m.R_M));
    }
    else
    {
        len = read_ModR_M(eip + 1, &addr);
        dest = MEM_R(addr);
        print_asm("sal" "   $0x%x,%%%s",temp,ModR_M_asm);
    }
    if(temp == 1)    cpu.OF = MSB(dest) != cpu.CF;
   
    while(temp != 0)
    {
        cpu.CF = MSB(dest);
        dest = dest * 2;
        temp --;
    }
    if(dest == 0)    cpu.ZF = 1;
    else    cpu.ZF = 0;
    if(MSB(dest) == 1)    cpu.SF = 1;
    else    cpu.SF = 0;
    PF_W((uint32_t) dest);
    if(m.mod == 3)
    {
        REG(m.R_M) = dest;
        return 3;
    }
    else
    {
        MEM_W(addr, dest);
        return len + 1 + 1;
    }
}
make_helper(concat(sar_cl2rm_, SUFFIX))
{
    ModR_M m;
    DATA_TYPE_S dest;

    swaddr_t addr;
    int len = 0;
    m.val = instr_fetch(eip + 1,1);
    if(m.mod == 3)
    {
        dest = REG(m.R_M);
        print_asm("sar" "   %%cl,%%%s",REG_NAME(m.R_M));
    }
    else
    {
        len = read_ModR_M(eip + 1, &addr);
        dest = MEM_R(addr);
        print_asm("sar" "   %%cl,%%%s",ModR_M_asm);
    }
    uint8_t temp = reg_b(R_CL);
    if(temp == 1)    cpu.OF = 0;
    while(temp != 0)
    {
        cpu.CF = dest & 0x1;
        dest = dest / 2;
        temp --;
    }
    if(dest == 0)    cpu.ZF = 1;
    else    cpu.ZF = 0;
    if(MSB(dest) == 1)    cpu.SF = 1;
    else    cpu.SF = 0;
    PF_W((uint32_t) dest);
    if(m.mod == 3)
    {
        REG(m.R_M) = dest;
        return 2;
    }
    else
    {
        MEM_W(addr, dest);
        return len + 1;
    }
}

make_helper(concat(sar_12rm_, SUFFIX))
{
    ModR_M m;
    DATA_TYPE_S dest;
    swaddr_t addr;
    int len = 0;
    m.val = instr_fetch(eip + 1,1);
    if(m.mod == 3)
    {
        dest = REG(m.R_M);
        print_asm("sar" "   $0x1,%%%s",REG_NAME(m.R_M));
    }
    else
    {
        len = read_ModR_M(eip + 1, &addr);
        dest = MEM_R(addr);
        print_asm("sar" "   $0x1,%%%s",ModR_M_asm);
    }
    uint8_t temp = 1;
    if(temp == 1)    cpu.OF = 0;
    while(temp != 0)
    {
        cpu.CF = dest & 0x1;
        dest = dest / 2;
        temp --;
    }
    if(dest == 0)    cpu.ZF = 1;
    else    cpu.ZF = 0;
    if(MSB(dest) == 1)    cpu.SF = 1;
    else    cpu.SF = 0;
    PF_W((uint32_t) dest);
    if(m.mod == 3)
    {
        REG(m.R_M) = dest;
        return 2;
    }
    else
    {
        MEM_W(addr, dest);
        return len + 1;
    }
}

make_helper(concat(sar_ib2rm_, SUFFIX))
{
    ModR_M m;
    DATA_TYPE_S dest;

    swaddr_t addr;
    int len = 0;
    m.val = instr_fetch(eip + 1,1);
    uint8_t temp = 0;
    if(m.mod == 3)
    {
        temp = instr_fetch(eip + 2, 1);
    }
    else
    {
        temp = instr_fetch(eip + len + 1, 1);
    }
    if(temp == 1)    cpu.OF = 0;
    if(m.mod == 3)
    {
        dest = REG(m.R_M);
        print_asm("sar" "   $0x%x,%%%s",temp,REG_NAME(m.R_M));
    }
    else
    {
        len = read_ModR_M(eip + 1, &addr);
        dest = MEM_R(addr);
        print_asm("sar" "   $0x%x,%%%s",temp,ModR_M_asm);
    }
    while(temp != 0)
    {
        cpu.CF = dest & 0x1;
        dest = dest / 2;
        temp --;
    }
    if(dest == 0)    cpu.ZF = 1;
    else    cpu.ZF = 0;
    if(MSB(dest) == 1)    cpu.SF = 1;
    else    cpu.SF = 0;
    PF_W((uint32_t) dest);
    if(m.mod == 3)
    {
        REG(m.R_M) = dest;
        return 3;
    }
    else
    {
        MEM_W(addr, dest);
        return len + 1 + 1;
    }
}

make_helper(concat(shr_cl2rm_, SUFFIX))
{
    ModR_M m;
    DATA_TYPE dest;

    swaddr_t addr;
    int len = 0;
    m.val = instr_fetch(eip + 1,1);
    if(m.mod == 3)
    {
        dest = REG(m.R_M);
        print_asm("shr" "   %%cl,%%%s",REG_NAME(m.R_M));
    }
    else
    {
        len = read_ModR_M(eip + 1, &addr);
        dest = MEM_R(addr);
        print_asm("shr" "   %%cl,%%%s",ModR_M_asm);
    }
    uint8_t temp = reg_b(R_CL);
    if(temp == 1)    cpu.OF = MSB(dest);
    while(temp != 0)
    {
        cpu.CF = dest & 0x1;
        dest = dest / 2;
        temp --;
    }
    if(dest == 0)    cpu.ZF = 1;
    else    cpu.ZF = 0;
    if(MSB(dest) == 1)    cpu.SF = 1;
    else    cpu.SF = 0;
    PF_W((uint32_t) dest);
    if(m.mod == 3)
    {
        REG(m.R_M) = dest;
        return 2;
    }
    else
    {
        MEM_W(addr, dest);
        return len + 1;
    }
}

make_helper(concat(shr_12rm_, SUFFIX))
{
    ModR_M m;
    DATA_TYPE dest;
    swaddr_t addr;
    int len = 0;
    m.val = instr_fetch(eip + 1,1);
    if(m.mod == 3)
    {
        dest = REG(m.R_M);
        print_asm("shr" "   $0x1,%%%s",REG_NAME(m.R_M));
    }
    else
    {
        len = read_ModR_M(eip + 1, &addr);
        dest = MEM_R(addr);
        print_asm("shr" "   $0x1,%%%s",ModR_M_asm);
    }
    uint8_t temp = 1;
    if(temp == 1)    cpu.OF = MSB(dest);
    while(temp != 0)
    {
        cpu.CF = dest & 0x1;
        dest = dest / 2;
        temp --;
    }
    if(dest == 0)    cpu.ZF = 1;
    else    cpu.ZF = 0;
    if(MSB(dest) == 1)    cpu.SF = 1;
    else    cpu.SF = 0;
    PF_W((uint32_t) dest);
    if(m.mod == 3)
    {
        REG(m.R_M) = dest;
        return 2;
    }
    else
    {
        MEM_W(addr, dest);
        return len + 1;
    }
}

make_helper(concat(shr_ib2rm_, SUFFIX))
{
    ModR_M m;
    DATA_TYPE dest;

    swaddr_t addr;
    int len = 0;
    m.val = instr_fetch(eip + 1,1);
    uint8_t temp = 0;
    if(m.mod == 3)
    {
        temp = instr_fetch(eip + 2, 1);
    }
    else
    {
        temp = instr_fetch(eip + len + 1, 1);
    }
    if(m.mod == 3)
    {
        dest = REG(m.R_M);
        print_asm("shr" "   $0x%x,%%%s",temp,REG_NAME(m.R_M));
    }
    else
    {
        len = read_ModR_M(eip + 1, &addr);
        dest = MEM_R(addr);
        print_asm("shr" "   $0x%x,%%%s",temp,ModR_M_asm);
    }
    if(temp == 1)    cpu.OF = MSB(dest);
    while(temp != 0)
    {
        cpu.CF = dest & 0x1;
        dest = dest / 2;
        temp --;
    }
    if(dest == 0)    cpu.ZF = 1;
    else    cpu.ZF = 0;
    if(MSB(dest) == 1)    cpu.SF = 1;
    else    cpu.SF = 0;
    PF_W((uint32_t) dest);
    if(m.mod == 3)
    {
        REG(m.R_M) = dest;
        return 3;
    }
    else
    {
        MEM_W(addr, dest);
        return len + 1 + 1;
    }
}

#endif
#include "exec/template-end.h"

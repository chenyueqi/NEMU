#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "../flag/flag.h"

make_helper(concat(cmp_i2a_,SUFFIX))
{
    DATA_TYPE sub = REG(R_EAX);
    DATA_TYPE imm = instr_fetch(eip+1,DATA_BYTE);
    DATA_TYPE result = REG(R_EAX)-imm;

    sub_flags(MSB(sub), ( (~MSB(imm)) & 0x1), MSB(result), (uint32_t) result);
    print_asm("cmp"str(SUFFIX)" $0x%x,%s",imm,REG_NAME(R_EAX));
    return DATA_BYTE+1;
}

make_helper(concat(cmp_r2rm_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    if(m.mod==3)
    {
        DATA_TYPE sub = REG(m.R_M);
        DATA_TYPE sub2 = REG(m.reg);
        DATA_TYPE result = REG(m.R_M)-REG(m.reg);
        sub_flags(MSB(sub), ( (~MSB(sub2)) & 0x1), MSB(result), (uint32_t) result);
        print_asm("cmp"str(SUFFIX) " %%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));

        return 2;
    }
    else
    {
        swaddr_t addr;
        int len=read_ModR_M(eip+1,&addr);
        DATA_TYPE sub = MEM_R(addr);
        DATA_TYPE sub2 = REG(m.reg);
        DATA_TYPE result = MEM_R(addr)-REG(m.reg);
        sub_flags(MSB(sub), ( (~MSB(sub2)) & 0x1), MSB(result), (uint32_t) result);

        print_asm("cmp"str(SUFFIX) " %%%s,%s",REG_NAME(m.reg), ModR_M_asm);
        return len+1;
    }
}

make_helper(concat(cmp_rm2r_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip+1,1);
    if(m.mod==3)
    {
        DATA_TYPE sub = REG(m.reg);
        DATA_TYPE sub2 = REG(m.R_M);
        DATA_TYPE result = REG(m.reg)-REG(m.R_M);
        print_asm("cmp"str(SUFFIX) " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
        sub_flags(MSB(sub), ((~MSB(sub2))&0x1), MSB(result), (uint32_t) result);
        return 2;
    }
    else
    {
        swaddr_t addr;
        int len=read_ModR_M(eip+1,&addr);
        DATA_TYPE sub = REG(m.reg);
        DATA_TYPE sub2 = MEM_R(addr);
        DATA_TYPE result =REG(m.reg)-MEM_R(addr);
        sub_flags(MSB(sub), ( (~MSB(sub2)) & 0x1), MSB(result), (uint32_t) result);

        print_asm("cmp"str(SUFFIX) " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));
        return len+1;
    }
}

make_helper(concat(cmp_ib2rm_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip+1,1);
    if(m.mod==3)
    {
        int8_t instr = instr_fetch(eip+2,1);
        DATA_TYPE_S imm_temp = instr;
        DATA_TYPE imm = imm_temp;
        DATA_TYPE sub = REG(m.R_M);
        DATA_TYPE result = REG(m.R_M)-imm;
        sub_flags(MSB(sub),( (~MSB(imm)) & 0x1), MSB(result), (uint32_t) result);
        print_asm("cmp"str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));
        return 3;
    }
    else
    {
        swaddr_t addr;
        int len=read_ModR_M(eip+1,&addr);
        int8_t instr = instr_fetch(eip+len+1,1);
        DATA_TYPE_S imm_temp = instr;
        DATA_TYPE imm = imm_temp;
        DATA_TYPE sub=MEM_R(addr);
        DATA_TYPE result = MEM_R(addr)-imm;
        sub_flags(MSB(sub),( (~MSB(imm)) & 0x1), MSB(result), (uint32_t) result);

        print_asm("cmp"str(SUFFIX) " $0x%x,%s",imm,ModR_M_asm);
        return len+2;
    }
}


make_helper(concat(cmp_i2rm_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip+1,1);
    if(m.mod==3)
    {
        DATA_TYPE imm=instr_fetch(eip+2,DATA_BYTE);
        DATA_TYPE sub=REG(m.R_M);
        DATA_TYPE result=REG(m.R_M)-imm;
        print_asm("cmp"str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));
        sub_flags(MSB(sub),( (~MSB(imm)) & 0x1), MSB(result), (uint32_t) result);
        return DATA_BYTE+2;
    }
    else
    {
        swaddr_t addr;
        int len=read_ModR_M(eip+1,&addr);
        DATA_TYPE imm=instr_fetch(eip+len+1,DATA_BYTE);
        DATA_TYPE sub=MEM_R(addr);
        DATA_TYPE result=MEM_R(addr)-imm;
        sub_flags(MSB(sub),( (~MSB(imm)) & 0x1), MSB(result), (uint32_t) result);

        print_asm("cmp"str(SUFFIX) " $0x%x,%s",imm,ModR_M_asm);
        return len+DATA_BYTE+1;
    }
}


#include "exec/template-end.h"

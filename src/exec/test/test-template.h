#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "../flag/flag.h"

make_helper(concat(test_r2rm_,SUFFIX))
{
    ModR_M m;
    m.val=instr_fetch(eip+1,1);
    if(m.mod == 3)
    {
        DATA_TYPE test1 = REG(m.R_M);
        DATA_TYPE test2 = REG(m.reg);
        DATA_TYPE result = REG(m.reg) & REG(m.R_M);
        add_flags(MSB(test1),MSB(test2),MSB(result), (uint32_t) result);
        cpu.CF = 0;
        cpu.OF = 0;
        print_asm("test"str(SUFFIX) " %%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));
        return 2;
    }
    else 
    {
        swaddr_t addr;
        int len = read_ModR_M(eip+1,&addr);
        DATA_TYPE test1 = MEM_R(addr);
        DATA_TYPE test2 = REG(m.reg);
        DATA_TYPE result=REG(m.reg) & MEM_R(addr);

        add_flags(MSB(test1),MSB(test2),MSB(result), (uint32_t) result);
        cpu.CF = 0;
        cpu.OF = 0;

        print_asm("test"str(SUFFIX) " %%%s,%s",REG_NAME(m.reg),ModR_M_asm);
        return len+1;
    }
}

make_helper(concat(test_i2ar_,SUFFIX))
{
    DATA_TYPE test1 = REG(R_EAX);
    DATA_TYPE imm = instr_fetch(eip + 1, DATA_BYTE);
    DATA_TYPE result = REG(R_EAX) & imm;
    add_flags(MSB(test1),MSB(imm),MSB(result), (uint32_t) result);
    cpu.CF = 0;
    cpu.OF = 0;

    print_asm("test"str(SUFFIX) " $0x%x,%s",imm,REG_NAME(R_EAX));
    return DATA_BYTE + 1;

}

make_helper(concat(test_i2rm_,SUFFIX))
{
    ModR_M m;
    m.val=instr_fetch(eip+1,1);
    if(m.mod == 3)
    {
        DATA_TYPE test1 = REG(m.R_M);
        DATA_TYPE imm = instr_fetch(eip+2,DATA_BYTE);
        DATA_TYPE result = REG(m.reg) & imm;
        add_flags(MSB(test1),MSB(imm),MSB(result), (uint32_t) result);
        cpu.CF = 0;
        cpu.OF = 0;
        print_asm("test"str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));
        return DATA_BYTE + 2;
    }
    else 
    {
        swaddr_t addr;
        int len = read_ModR_M(eip+1,&addr);
        DATA_TYPE test1 = MEM_R(addr);
        DATA_TYPE imm = instr_fetch(eip+len+1,DATA_BYTE);
        DATA_TYPE result = imm & MEM_R(addr);

        add_flags(MSB(test1),MSB(imm),MSB(result), (uint32_t) result);
        cpu.CF = 0;
        cpu.OF = 0;

        print_asm("test"str(SUFFIX) " $0x%x,%s",imm,ModR_M_asm);
        return len+1+DATA_BYTE;
    }
}
#include "exec/template-end.h"

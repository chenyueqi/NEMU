#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(mul_rm2al_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    swaddr_t addr;
    DATA_TYPE num;
    int len = 0;
    if(m.mod == 3)
    {
        num = REG(m.R_M);
        print_asm("mul" "   %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(R_EAX));
    }
    else
    {
        len = read_ModR_M(eip + 1, &addr);
        num = MEM_R(addr);
        print_asm("mul" "   %s,%%%s",ModR_M_asm,REG_NAME(R_EAX));
    }
    if(DATA_BYTE == 1)
    {
        reg_w(R_EAX) = reg_b(R_EAX) * num;
        if((reg_w(R_EAX)>> 8) == 0)
        {
            cpu.CF = 0;
            cpu.OF = 0;
        }
        else
        {
            cpu.CF = 1;
            cpu.OF = 1;
        }
    }
    else if(DATA_BYTE == 2)
    {
        uint32_t result = reg_w(R_EAX) * num;
        reg_w(R_EAX) = result & 0xffff;
        reg_w(R_EDX) = (result >> 16) & 0xffff;
        if(reg_w(R_EDX) == 0)
        {
            cpu.CF = 0;
            cpu.OF = 0;
        }
        else
        {
            cpu.CF = 1;
            cpu.OF = 1;
        }
    }
    else
    {
        unsigned long long result = reg_l(R_EAX) * num;
        reg_l(R_EAX) = result & 0xffffffff;
        reg_l(R_EDX) = (result >> 32) & 0xffffffff;
        if(reg_l(R_EDX) == 0)
        {
            cpu.CF = 0;
            cpu.OF = 0;
        }
        else
        {
            cpu.CF = 1;
            cpu.OF = 1;
        }
    }
    
    if(m.mod == 3)
        return 1 + 1;
    else 
        return 1 + len;
}

make_helper(concat(imul_rm2al_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    long long int temp;
    if(m.mod == 3)
    {
        temp = (long long int)REG(R_EAX) * REG(m.R_M);
        REG(R_EAX) = temp;
        if(DATA_BYTE == 1)
        {
            REG(R_AH) = (temp) >> (DATA_BYTE << 3);
        }
        else
        {
            REG(R_EDX) = (temp) >> (DATA_BYTE << 3);
        }
        print_asm("imul" " %%%s", REG_NAME(m.R_M));
        return 2;
    }
    else
    {
        swaddr_t addr;
        int len = read_ModR_M(eip + 1, &addr);
        temp = (long long int)REG(R_EAX) * MEM_R(addr);
        REG(R_EAX) = temp;
        if(DATA_BYTE == 1)
        {
            REG(R_AH) = (temp) >> (DATA_BYTE << 3);
        }
        else
        {
            REG(R_EDX) = (temp) >> (DATA_BYTE << 3);
        }
        print_asm("imul" " %s", ModR_M_asm);
        return len + 1;
    }
}
make_helper(concat(imul_rm2r_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    swaddr_t addr;
    DATA_TYPE_S num;
    int len = 0;
    if(m.mod == 3)
    {
        num = REG(m.R_M);
        print_asm("imul" "   %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
    }
    else
    {
        len = read_ModR_M(eip + 1, &addr);
        num = MEM_R(addr);
        print_asm("imul" "   %s,%%%s",ModR_M_asm,REG_NAME(m.reg));
    }
    DATA_TYPE_S result = REG(m.reg) * num;
    REG(m.reg) = result;
    
    if(m.mod == 3)
        return 1 + 1;
    else 
        return 1 + len;
}

make_helper(concat(imul_ib2r_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    swaddr_t addr;
    DATA_TYPE_S num;
    int8_t num2;

    int len = 0;
    if(m.mod == 3)
    {
        num = REG(m.R_M);
        num2 = instr_fetch(eip + 2,1);
        print_asm("imul" "   %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
    }
    else
    {
        len = read_ModR_M(eip + 1, &addr);
        num = MEM_R(addr);
        num2 = instr_fetch(eip + len + 1,1);
        print_asm("imul" "   %s,%%%s",ModR_M_asm,REG_NAME(m.reg));
    }
    DATA_TYPE_S result = num2 * num;
    REG(m.reg) = result;
    
    if(m.mod == 3)
        return 1 + 1 + 1;
    else 
        return 1 + len + 1;
}


make_helper(concat(imul_i2r_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    swaddr_t addr;
    DATA_TYPE_S num;
    DATA_TYPE_S num2;

    int len = 0;
    if(m.mod == 3)
    {
        num = REG(m.R_M);
        num2 = instr_fetch(eip + 2,DATA_BYTE);
        print_asm("imul" "   %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
    }
    else
    {
        len = read_ModR_M(eip + 1, &addr);
        num = MEM_R(addr);
        num2 = instr_fetch(eip + len + 1,DATA_BYTE);
        print_asm("imul" "   %s,%%%s",ModR_M_asm,REG_NAME(m.reg));
    }
    DATA_TYPE_S result = num2 * num;
    REG(m.reg) = result;
    
    if(m.mod == 3)
        return 1 + 1 + DATA_BYTE;
    else 
        return 1 + len + DATA_BYTE;
}

make_helper(concat(div_rm2al_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    swaddr_t addr;
    DATA_TYPE num;
    int len = 0;
    if(m.mod == 3)
    {
        num = REG(m.R_M);
        print_asm("div" "   %%%s",REG_NAME(m.R_M));
    }
    else
    {
        len = read_ModR_M(eip + 1, &addr);
        num = MEM_R(addr);
        print_asm("div" " %s",ModR_M_asm);
    }
    if(DATA_BYTE == 1)
    {
        reg_w(R_EAX) = (reg_b(R_EAX) % num) & 0xffff0000;
        reg_b(R_EAX) = (reg_b(R_EAX) / num) & 0xffff;
    }
    else if(DATA_BYTE == 2)
    {
        uint32_t result = reg_w(R_EAX) / num;
        uint32_t result2 = reg_w(R_EAX) % num; 
        reg_w(R_EAX) = result & 0xffff;
        reg_w(R_EDX) = result2 & 0xffff;
    }
    else
    {
        unsigned long long result = reg_l(R_EAX) / num;
        unsigned long long result2 = reg_l(R_EAX) % num;
        reg_l(R_EAX) = result & 0xffffffff;
        reg_l(R_EDX) = result2 & 0xffffffff;
    }
    
    if(m.mod == 3)
        return 1 + 1;
    else 
        return 1 + len;
}

make_helper(concat(idiv_rm2al_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    swaddr_t addr;
    DATA_TYPE_S num;
    int len = 0;
    if(m.mod == 3)
    {
        num = REG(m.R_M);
        print_asm("idiv" "   %%%s",REG_NAME(m.R_M));
    }
    else
    {
        len = read_ModR_M(eip + 1, &addr);
        num = MEM_R(addr);
        print_asm("idiv" " %s",ModR_M_asm);
    }
    if(DATA_BYTE == 1)
    {
        reg_w(R_EAX) = (DATA_TYPE_S)(reg_b(R_EAX) % num) & 0xffff0000;
        reg_b(R_EAX) = (DATA_TYPE_S)(reg_b(R_EAX) / num) & 0xffff;
    }
    else if(DATA_BYTE == 2)
    {
        int32_t result = reg_w(R_EAX) / num;
        int32_t result2 = reg_w(R_EAX) % num; 
        reg_w(R_EAX) = result & 0xffff;
        reg_w(R_EDX) = result2 & 0xffff;
    }
    else
    {
        long long result = reg_l(R_EAX) / num;
        long long result2 = reg_l(R_EAX) % num;
        reg_l(R_EAX) = result & 0xffffffff;
        reg_l(R_EDX) = result2 & 0xffffffff;
    }
    
    if(m.mod == 3)
        return 1 + 1;
    else 
        return 1 + len;
}

#include "exec/template-end.h"


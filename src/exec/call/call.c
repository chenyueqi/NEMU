#include "cpu/modrm.h"
#include "exec/helper.h"
#include "nemu.h"
#include "ui/ui.h"
#include "cpu/reg.h"

make_helper(call_rel)
{
    int32_t imm=instr_fetch(eip+1,4);
    cpu.esp-=4;
    swaddr_write(cpu.esp,4,cpu.eip+4);
    cpu.eip=eip+imm;
    print_asm("call  %x",eip+5+imm);
    return 5;
}

make_helper(call_rm)
{
    ModR_M m;
    m.val=instr_fetch(eip+1,1);
    if(m.mod == 3)
    {
        cpu.esp-=4;
        swaddr_write(cpu.esp,4,eip+1);

        print_asm("call"" %s",regsl[m.R_M]);
        cpu.eip=reg_l(m.R_M)-2;
        return 2;
    }
    else
    {
        swaddr_t addr;
        int len =read_ModR_M(eip+1,&addr);
        cpu.esp-=4;
        swaddr_write(cpu.esp,4,cpu.eip+len+1);
        cpu.eip=swaddr_read(addr,4)-len-1;
        print_asm("call %s",ModR_M_asm);

        return len+1;

    }
}


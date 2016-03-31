#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(neg_r_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip+1,1);
    if(m.mod==3)
    {
        DATA_TYPE result=REG(m.R_M);
        if(result==0)    cpu.CF=0;
        else    cpu.CF=1;
        print_asm("neg %%%s",REG_NAME(m.R_M));
        return 2;
    }
    else
    {
        swaddr_t addr;
        int len = read_ModR_M(eip+1,&addr);
        DATA_TYPE result = MEM_R(addr);
        if(result==0)    cpu.CF=0;
        else    cpu.CF=1;
        print_asm("neg %s",ModR_M_asm);
        return len+1;
    }
}

#include "exec/template-end.h"

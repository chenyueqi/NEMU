#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(setne_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    if(cpu.ZF==0)
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=1;
            print_asm("setne %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,1);
            print_asm("setne %s",ModR_M_asm);
            return len+1;
        }
    }
    else
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=0;
            print_asm("setne %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,0);
            print_asm("setne %s",ModR_M_asm);
            return len+1;
        }
    }
}


make_helper(concat(seta_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    if(cpu.ZF==0&&cpu.CF==0)
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=1;
            print_asm("seta %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,1);
            print_asm("seta %s",ModR_M_asm);
            return len+1;
        }
    }
    else
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=0;
            print_asm("seta %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,0);
            print_asm("seta %s",ModR_M_asm);
            return len+1;
        }
    }
}

make_helper(concat(setae_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    if(cpu.CF==0)
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=1;
            print_asm("setae %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,1);
            print_asm("setae %s",ModR_M_asm);
            return len+1;
        }
    }
    else
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=0;
            print_asm("setae %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,0);
            print_asm("setae %s",ModR_M_asm);
            return len+1;
        }
    }
}

make_helper(concat(setb_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    if(cpu.CF==1)
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=1;
            print_asm("setb %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,1);
            print_asm("setb %s",ModR_M_asm);
            return len+1;
        }
    }
    else
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=0;
            print_asm("setb %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,0);
            print_asm("setb %s",ModR_M_asm);
            return len+1;
        }
    }
}


make_helper(concat(setbe_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    if(cpu.ZF==1||cpu.CF==1)
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=1;
            print_asm("setbe %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,1);
            print_asm("setbe %s",ModR_M_asm);
            return len+1;
        }
    }
    else
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=0;
            print_asm("setbe %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,0);
            print_asm("setbe %s",ModR_M_asm);
            return len+1;
        }
    }
}

make_helper(concat(sete_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    if(cpu.ZF==1)
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=1;
            print_asm("sete %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,1);
            print_asm("sete %s",ModR_M_asm);
            return len+1;
        }
    }
    else
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=0;
            print_asm("sete %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,0);
            print_asm("sete %s",ModR_M_asm);
            return len+1;
        }
    }
}

make_helper(concat(setg_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    if(cpu.ZF==0&&(cpu.SF==cpu.OF))
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=1;
            print_asm("setg %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,1);
            print_asm("setg %s",ModR_M_asm);
            return len+1;
        }
    }
    else
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=0;
            print_asm("setg %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,0);
            print_asm("setg %s",ModR_M_asm);
            return len+1;
        }
    }
}

make_helper(concat(setge_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    if(cpu.SF==cpu.OF)
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=1;
            print_asm("setge %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,1);
            print_asm("setge %s",ModR_M_asm);
            return len+1;
        }
    }
    else
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=0;
            print_asm("setge %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,0);
            print_asm("setge %s",ModR_M_asm);
            return len+1;
        }
    }
}

make_helper(concat(setl_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    if(cpu.SF!=cpu.OF)
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=1;
            print_asm("setl %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,1);
            print_asm("setl %s",ModR_M_asm);
            return len+1;
        }
    }
    else
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=0;
            print_asm("setl %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,0);
            print_asm("setl %s",ModR_M_asm);
            return len+1;
        }
    }
}

make_helper(concat(setle_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    if(cpu.ZF==1&&(cpu.SF!=cpu.OF))
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=1;
            print_asm("setle %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,1);
            print_asm("setle %s",ModR_M_asm);
            return len+1;
        }
    }
    else
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=0;
            print_asm("setle %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,0);
            print_asm("setle %s",ModR_M_asm);
            return len+1;
        }
    }
}

make_helper(concat(setno_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    if(cpu.OF==0)
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=1;
            print_asm("setno %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,1);
            print_asm("setno %s",ModR_M_asm);
            return len+1;
        }
    }
    else
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=0;
            print_asm("setno %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,0);
            print_asm("setno %s",ModR_M_asm);
            return len+1;
        }
    }
}

make_helper(concat(setnp_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    if(cpu.PF==0)
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=1;
            print_asm("setnp %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,1);
            print_asm("setnp %s",ModR_M_asm);
            return len+1;
        }
    }
    else
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=0;
            print_asm("setnp %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,0);
            print_asm("setnp %s",ModR_M_asm);
            return len+1;
        }
    }
}

make_helper(concat(setns_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    if(cpu.SF==0)
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=1;
            print_asm("setns %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,1);
            print_asm("setns %s",ModR_M_asm);
            return len+1;
        }
    }
    else
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=0;
            print_asm("setns %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,0);
            print_asm("setns %s",ModR_M_asm);
            return len+1;
        }
    }
}

make_helper(concat(seto_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    if(cpu.OF==1)
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=1;
            print_asm("seto %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,1);
            print_asm("seto %s",ModR_M_asm);
            return len+1;
        }
    }
    else
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=0;
            print_asm("seto %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,0);
            print_asm("seto %s",ModR_M_asm);
            return len+1;
        }
    }
}

make_helper(concat(setp_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    if(cpu.PF==1)
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=1;
            print_asm("setp %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,1);
            print_asm("setp %s",ModR_M_asm);
            return len+1;
        }
    }
    else
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=0;
            print_asm("setp %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,0);
            print_asm("setp %s",ModR_M_asm);
            return len+1;
        }
    }
}

make_helper(concat(sets_,SUFFIX))
{
    ModR_M m;
    m.val = instr_fetch(eip + 1,1);
    if(cpu.SF==1)
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=1;
            print_asm("sets %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,1);
            print_asm("sets %s",ModR_M_asm);
            return len+1;
        }
    }
    else
    {
        if(m.mod == 3)
        {
            REG(m.R_M)=0;
            print_asm("sets %%%s",REG_NAME(m.R_M));
            return 2;
        }
        else
        {
            swaddr_t addr;
            int len = read_ModR_M(eip +1,&addr);
            MEM_W(addr,0);
            print_asm("sets %s",ModR_M_asm);
            return len+1;
        }
    }
}
#include "exec/template-end.h"

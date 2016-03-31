#include "exec/helper.h"
#include "cpu/modrm.h"
#include "exec/template-start.h"

	extern uint8_t current_sreg ;
make_helper(concat(je_z_, SUFFIX))
{
    if(cpu.ZF==1)
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("je  %x",cpu.eip+len+2);
        cpu.eip+=len;
        if(DATA_BYTE==2)
            cpu.eip=cpu.eip&0x0000ffff;
        return DATA_BYTE+1;
    }
    else 
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("je  %x",cpu.eip+len+2);
        return DATA_BYTE+1;
    }
}

make_helper(concat(je_s_, SUFFIX))
{
    if(cpu.SF==1)
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("je  %x",cpu.eip+len+2);
        cpu.eip+=len;
    if(DATA_BYTE==2)
        cpu.eip=cpu.eip&0x0000ffff;
        return DATA_BYTE+1;
    }
    else 
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("je  %x",cpu.eip+len+2);
        return DATA_BYTE+1;
    }
}

make_helper(concat(jmp_, SUFFIX))
{
    DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
    print_asm("jmp  %x",cpu.eip+len+2);
    cpu.eip+=len;
    if(DATA_BYTE==2)
        cpu.eip=cpu.eip&0x0000ffff;

    return DATA_BYTE+1;
}

make_helper(concat(jle_, SUFFIX))
{
    if(cpu.ZF==1||(cpu.SF!=cpu.OF))
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jle  %x",cpu.eip+len+2);
        cpu.eip+=len;
    if(DATA_BYTE==2)
        cpu.eip=cpu.eip&0x0000ffff;
        return DATA_BYTE+1;
    }
    else 
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jle  %x",cpu.eip+len+2);
        return DATA_BYTE+1;
    }
}

make_helper(concat(ja_, SUFFIX))
{
    if(cpu.CF==0&&cpu.ZF==0)
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("ja  %x",cpu.eip+len+2);
        cpu.eip+=len;
    if(DATA_BYTE==2)
        cpu.eip=cpu.eip&0x0000ffff;
        return DATA_BYTE+1;
    }
    else 
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("ja  %x",cpu.eip+len+2);
        return DATA_BYTE+1;
    }
}

make_helper(concat(jae_, SUFFIX))
{
    if(cpu.CF==0)
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jae  %x",cpu.eip+len+2);
        cpu.eip+=len;
    if(DATA_BYTE==2)
        cpu.eip=cpu.eip&0x0000ffff;
        return DATA_BYTE+1;
    }
    else 
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jae  %x",cpu.eip+len+2);
        return DATA_BYTE+1;
    }
}

make_helper(concat(jb_, SUFFIX))
{
    if(cpu.CF==1)
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jb  %x",cpu.eip+len+2);
        cpu.eip+=len;
    if(DATA_BYTE==2)
        cpu.eip=cpu.eip&0x0000ffff;
        return DATA_BYTE+1;
    }
    else 
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jb  %x",cpu.eip+len+2);
        return DATA_BYTE+1;
    }
}

make_helper(concat(jbe_, SUFFIX))
{
    if(cpu.ZF==1||cpu.CF==1)
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        cpu.eip+=len;
    if(DATA_BYTE==2)
        cpu.eip=cpu.eip&0x0000ffff;
        print_asm("jbe  %x",cpu.eip+len+2);
        return DATA_BYTE+1;
    }
    else 
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jbe  %x",cpu.eip+len+2);
        return DATA_BYTE+1;
    }
}

make_helper(concat(jc_, SUFFIX))
{
    if(cpu.CF==1)
    {
        int8_t len=instr_fetch(eip+1,1);
        print_asm("jc  %x",cpu.eip+len+2);
        cpu.eip+=len;
    if(DATA_BYTE==2)
        cpu.eip=cpu.eip&0x0000ffff;
        return 2;
    }
    else 
    {
        int8_t len=instr_fetch(eip+1,1);
        print_asm("jc  %x",cpu.eip+len+2);
        return 2;
    }
}


make_helper(concat(jcxz_, SUFFIX))
{
    if(REG(R_ECX)==0)
    {
        int8_t len=instr_fetch(eip+1,1);
        print_asm("jcxz  %x",cpu.eip+len+2);
        cpu.eip+=len;
        return 2;
    }
    else 
    {
        int8_t len=instr_fetch(eip+1,1);
        print_asm("jcxz  %x",cpu.eip+len+2);
        return 2;
    }
}

make_helper(concat(jg_, SUFFIX))
{
    if(cpu.ZF==0&&(cpu.SF==cpu.OF))
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jg  %x",cpu.eip+len+2);
        cpu.eip+=len;
    if(DATA_BYTE==2)
        cpu.eip=cpu.eip&0x0000ffff;
        return DATA_BYTE+1;
    }
    else 
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jg  %x",cpu.eip+len+2);
        return DATA_BYTE+1;
    }
}

make_helper(concat(jge_, SUFFIX))
{
    if(cpu.SF==cpu.OF)
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jge  %x",cpu.eip+len+2);
        cpu.eip+=len;
    if(DATA_BYTE==2)
        cpu.eip=cpu.eip&0x0000ffff;
        return DATA_BYTE+1;
    }
    else 
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jge  %x",cpu.eip+len+2);
        return DATA_BYTE+1;
    }
}

make_helper(concat(jl_, SUFFIX))
{
    if(cpu.SF!=cpu.OF)
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jl  %x",cpu.eip+len+2);
        cpu.eip+=len;
    if(DATA_BYTE==2)
        cpu.eip=cpu.eip&0x0000ffff;
        return DATA_BYTE+1;
    }
    else 
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jl  %x",cpu.eip+len+2);
        return DATA_BYTE+1;
    }
}

make_helper(concat(jno_, SUFFIX))
{
    if(cpu.OF==0)
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jno  %x",cpu.eip+len+2);
        cpu.eip+=len;
    if(DATA_BYTE==2)
        cpu.eip=cpu.eip&0x0000ffff;
        return DATA_BYTE+1;
    }
    else 
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jno  %x",cpu.eip+len+2);
        return DATA_BYTE+1;
    }
}

make_helper(concat(jnz_, SUFFIX))
{
    if(cpu.ZF==0)
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jnz  %x",cpu.eip+len+2);
        cpu.eip+=len;
    if(DATA_BYTE==2)
        cpu.eip=cpu.eip&0x0000ffff;
        return DATA_BYTE+1;
    }
    else 
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jnz  %x",cpu.eip+len+2);
        return DATA_BYTE+1;
    }
}

make_helper(concat(jo_, SUFFIX))
{
    if(cpu.OF==1)
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jo  %x",cpu.eip+len+2);
        cpu.eip+=len;
    if(DATA_BYTE==2)
        cpu.eip=cpu.eip&0x0000ffff;
        return DATA_BYTE+1;
    }
    else 
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jo  %x",cpu.eip+len+2);
        return DATA_BYTE+1;
    }
}

make_helper(concat(jns_, SUFFIX))
{
    if(cpu.SF==0)
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jns  %x",cpu.eip+len+2);
        cpu.eip+=len;
    if(DATA_BYTE==2)
        cpu.eip=cpu.eip&0x0000ffff;
        return DATA_BYTE+1;
    }
    else 
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jns  %x",cpu.eip+len+2);
        return DATA_BYTE+1;
    }
}

make_helper(concat(jp_, SUFFIX))
{
    if(cpu.PF==1)
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jp  %x",cpu.eip+len+2);
        cpu.eip+=len;
    if(DATA_BYTE==2)
        cpu.eip=cpu.eip&0x0000ffff;
        return DATA_BYTE+1;
    }
    else 
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jp  %x",cpu.eip+len+2);
        return DATA_BYTE+1;
    }
}

make_helper(concat(jnp_, SUFFIX))
{
    if(cpu.PF==0)
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jnp  %x",cpu.eip+len+2);
        cpu.eip+=len;
    if(DATA_BYTE==2)
        cpu.eip=cpu.eip&0x0000ffff;
        return DATA_BYTE+1;
    }
    else 
    {
        DATA_TYPE_S len=instr_fetch(eip+1,DATA_BYTE);
        print_asm("jnp  %x",cpu.eip+len+2);
        return DATA_BYTE+1;
    }
}

make_helper(concat(jmp_rm_, SUFFIX))
{
    ModR_M m;
    m.val=instr_fetch(eip+1,1);
    if(m.mod==3)
    {
        if(DATA_BYTE==2)
            cpu.eip=(REG(m.R_M)-2) & 0x0000ffff;
        else cpu.eip=REG(m.R_M)-2;
        print_asm("jmp %%%s",REG_NAME(m.R_M));
        return 2;
    }
    else
    {
        swaddr_t addr;
        int len = read_ModR_M(eip+1,&addr);
        if(DATA_BYTE==2)
            cpu.eip=(MEM_R(addr)-len-1)&0x0000ffff;
        else cpu.eip=MEM_R(addr)-len-1;
        print_asm("jmp %s",ModR_M_asm);
        return len+1;
    }
}

make_helper(concat(ljmp_, SUFFIX))
{
	DATA_TYPE_S val1 = instr_fetch(eip + 1 , DATA_BYTE);
	uint16_t val2 = instr_fetch(eip + 1 + DATA_BYTE , 2);
	cpu.eip = val1 - 3 - DATA_BYTE ; 
	cpu.cs = val2;
	if(DATA_BYTE == 2)
	{
		cpu.eip = cpu.eip & 0x0000ffff;
	}
	uint16_t index = cpu.cs;
	uint32_t gdt_index =  cpu.gdtr.base + (index & 0xfff8 );
	uint32_t val3 = swaddr_read(gdt_index , 4);
	uint32_t val4 = swaddr_read(gdt_index  + 4 , 4);
	cpu.sreg_discribe[CS].base = (val3 >> 16) | ((val4  & 0x000000ff) << 16) | (val4 & 0xff000000);
	print_asm("ljmp" str(SUFFIX) " $0x%x, $0x%x" , cpu.cs , val1);
	return 3 + DATA_BYTE ; 
}












#include "exec/template-end.h"

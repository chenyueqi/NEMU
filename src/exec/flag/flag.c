#include "exec/helper.h"
#include "nemu.h"

make_helper(cld)
{
    cpu.DF=0;
    print_asm("cld");
    return 1;
}

make_helper(cli)
{
	cpu.IF = 0;
	print_asm("cli");
	return 1;
}


make_helper(std)
{
    cpu.DF=1;
    print_asm("std");
    return 1;
}

make_helper(hlt)
{
	print_asm("hlt");
	return 1;
}

void CF_W(uint8_t msbx,uint8_t msby,uint8_t msbr,uint8_t op)
{
    bool cf = ((msbx & msby) | ((msbx | msby) & (~msbr))) ^ op;
    cpu.CF=cf;
}

void OF_W(uint8_t msbx, uint8_t msby,uint8_t msbr)
{
    bool of = (msbx == msby) && (msbr != msbx);
    cpu.OF=of;
}

void S_OF_W(uint8_t msbx, uint8_t msby,uint8_t msbr)
{
    bool of = (msbx == msby) && (msbr != msbx);
    cpu.OF=of;
}

void PF_W(uint32_t num)
{
    int i;
    int sum = 0;
    uint8_t pf = num & 0xff;
    for(i = 0;i < 8;i++)
    {
        if((pf & 0x1) == 1)
            sum++;
        pf = pf >> 1;
    }
    if((sum & 0x1) == 0) cpu.PF = 1;
    else cpu.PF = 0;
}

void add_flags(uint8_t msb_m,uint8_t msb_s,uint8_t msb_r,uint32_t r)
{
    if(r==0)   
        cpu.ZF = 1;
    else    
        cpu.ZF = 0;
    if(msb_r == 1)    
        cpu.SF = 1;
    else
        cpu.SF = 0;
    CF_W(msb_m,msb_s,msb_r,0);
    OF_W(msb_m,msb_s,msb_r);
    PF_W(r);
}

void sub_flags(uint8_t msb_m,uint8_t msb_s,uint8_t msb_r,uint32_t r)
{
    if(r==0)   
        cpu.ZF = 1;
    else    
        cpu.ZF = 0;
    if(msb_r == 1)    
        cpu.SF = 1;
    else
        cpu.SF = 0;
    CF_W(msb_m,msb_s,msb_r,1);
    S_OF_W(msb_m,msb_s,msb_r);
    PF_W(r);
}

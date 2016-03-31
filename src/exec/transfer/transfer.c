#include "exec/helper.h"

#include "../all-instr.h"

typedef int (*helper_fun)(swaddr_t);

helper_fun transfer_table[64]=
{
/*0x80*/	jo_v,jno_v,jb_v,jae_v,
/*0x84*/	je_z_v,jnz_v,jbe_v,ja_v,
/*0x88*/	je_s_v,jns_v,jp_v,jnp_v,
/*0x8c*/	jl_v,jge_v,jle_v,jg_v,
/*0x90*/	seto_b,setno_b,setb_b,setae_b,
/*0x94*/	sete_b,setne_b,setbe_b,seta_b,
/*0x98*/	sets_b,setns_b,setp_b,setnp_b,
/*0x9c*/	setl_b,setge_b,setle_b,setg_b,
/*0xa0*/	inv,inv,inv,inv,
/*0xa4*/	inv,inv,inv,inv,
/*0xa8*/	inv,inv,inv,inv,
/*0xac*/	inv,inv,inv,imul_rm2r_v,
/*0xb0*/	inv,inv,inv,inv,
/*0xb4*/	inv,inv,movzx_rmb2r_v,movzx_rmw2r_l,
/*0xb8*/	inv,inv,inv,inv,
/*0xbc*/	inv,inv,movsx_rmb2r_v,movsx_rmw2r_l

};

make_helper(transfer)
{
	uint8_t instr = instr_fetch(eip + 1 , 1);
	if(instr >= 0x80)
		return 1+transfer_table[instr-0x80](eip+1);
	else
	{
		int instr_len = 0;
		switch(instr)
		{
			case 0x01: instr_len = lgdt_lidt_v(eip + 1);break;
			case 0x20: instr_len = mov_cr2r_l(eip + 1);break;
			case 0x22: instr_len = mov_r2cr_l(eip + 1);break;
		}
		return 1 + instr_len;
	}
}

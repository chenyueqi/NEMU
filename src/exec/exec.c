#include "exec/helper.h"

#include "all-instr.h"

typedef int (*helper_fun)(swaddr_t);


/* TODO: Add more instructions!!! */

helper_fun opcode_table [256] = {
/* 0x00 */	add_r2rm_b, add_r2rm_v, add_rm2r_b, add_rm2r_v, 
/* 0x04 */	add_i2a_b, add_i2a_v, inv, inv, 
/* 0x08 */	or_r2rm_b, or_r2rm_v, or_rm2r_b, or_rm2r_v, 
/* 0x0c */	or_i2a_b, or_i2a_v, inv, transfer,
/* 0x10 */	adc_r2rm_b, adc_r2rm_v, adc_rm2r_b, adc_rm2r_v, 
/* 0x14 */	adc_i2a_b, adc_i2a_v, inv, inv, 
/* 0x18 */	sbb_r2rm_b, sbb_r2rm_v, sbb_rm2r_b, sbb_rm2r_v, 
/* 0x2c */	sbb_i2a_b, sbb_i2a_v, inv, inv, 
/* 0x20 */	and_r2rm_b, and_r2rm_v, and_rm2r_b, and_rm2r_v, 
/* 0x24 */	and_i2a_b, and_i2a_v, inv, inv,
/* 0x28 */	sub_r2rm_b, sub_r2rm_v, sub_rm2r_b, sub_rm2r_v, 
/* 0x2c */	sub_i2a_b, sub_i2a_v, inv, inv, 
/* 0x30 */	xor_r2rm_b, xor_r2rm_v, xor_rm2r_b, xor_rm2r_v, 
/* 0x34 */	xor_i2a_b, xor_i2a_v, inv, inv,
/* 0x38 */	cmp_r2rm_b, cmp_r2rm_v, cmp_rm2r_b, cmp_rm2r_v, 
/* 0x3c */	cmp_i2a_b, cmp_i2a_v, inv, inv, 
/* 0x40 */	inc_r_v, inc_r_v, inc_r_v, inc_r_v, 
/* 0x44 */	inc_r_v, inc_r_v, inc_r_v, inc_r_v,
/* 0x48 */	dec_r_v, dec_r_v, dec_r_v, dec_r_v, 
/* 0x4c */	dec_r_v, dec_r_v, dec_r_v, dec_r_v,
/* 0x50 */	push_r_v, push_r_v, push_r_v, push_r_v, 
/* 0x54 */	push_r_v, push_r_v, push_r_v, push_r_v,
/* 0x58 */	pop_r_v, pop_r_v, pop_r_v, pop_r_v, 
/* 0x5c */	pop_r_v, pop_r_v, pop_r_v, pop_r_v, 
/* 0x60 */	pusha_v, popa_v, inv, inv,
/* 0x64 */	inv, inv, data_size, inv,
/* 0x68 */	push_i_v, imul_i2r_v, push_i_b, imul_ib2r_v, 
/* 0x6c */	inv, inv, inv, inv, 
/* 0x70 */	jo_b, jno_b, jb_b, jae_b,
/* 0x74 */	je_z_b, jnz_b, jbe_b, ja_b,
/* 0x78 */	je_s_b, jns_b, jp_b, jnp_b, 
/* 0x7c */	jl_b, jge_b, jle_b, jg_b, 
/* 0x80 */	choose_80, choose_81, nemu_trap, choose_83, 
/* 0x84 */	test_r2rm_b, test_r2rm_v, xchg_r2rm_b, xchg_r2rm_v, 
/* 0x88 */	mov_r2rm_b, mov_r2rm_v, mov_rm2r_b, mov_rm2r_v,
/* 0x8c */	mov_sr2rm_w, lea_v, mov_rm2sr_w, pop_m_v, 
/* 0x90 */	xchg_r2a_v, xchg_r2a_v, xchg_r2a_v, xchg_r2a_v,
/* 0x94 */	xchg_r2a_v, xchg_r2a_v, xchg_r2a_v, xchg_r2a_v,
/* 0x98 */	inv, cltd, inv, inv, 
/* 0x9c */	inv, inv, inv, inv, 
/* 0xa0 */	mov_moffs2a_b, mov_moffs2a_v, mov_a2moffs_b, mov_a2moffs_v,
/* 0xa4 */	movs_b, movs_v, inv, inv,
/* 0xa8 */	inv, inv, stos_b, stos_v,
/* 0xac */	inv, inv, inv, inv,
/* 0xb0 */	mov_i2r_b, mov_i2r_b, mov_i2r_b, mov_i2r_b,
/* 0xb4 */	mov_i2r_b, mov_i2r_b, mov_i2r_b, mov_i2r_b,
/* 0xb8 */	mov_i2r_v, mov_i2r_v, mov_i2r_v, mov_i2r_v, 
/* 0xbc */	mov_i2r_v, mov_i2r_v, mov_i2r_v, mov_i2r_v, 
/* 0xc0 */	choose_c0, choose_c1, ret_imm_l, ret_v,
/* 0xc4 */	inv, inv, mov_i2rm_b, mov_i2rm_v,
/* 0xc8 */	inv, leave_v, inv, inv,
/* 0xcc */	int3, int_imm, inv, inv,
/* 0xd0 */	choose_d0, choose_d1, choose_d2, choose_d3,
/* 0xd4 */	inv, inv, inv, inv,
/* 0xd8 */	inv, inv, inv, inv,
/* 0xdc */	inv, inv, inv, inv,
/* 0xe0 */	inv, inv, inv, jcxz_v,
/* 0xe4 */	inv, inv, inv, inv,
/* 0xe8 */	call_rel, jmp_v, ljmp_v, jmp_b,
/* 0xec */	inv, inv, inv, inv,
/* 0xf0 */	inv, inv, inv, rep,
/* 0xf4 */	hlt, inv, choose_f6, choose_f7,
/* 0xf8 */	inv, inv, cli, inv,
/* 0xfc */	cld, std, choose_fe, choose_ff
};

helper_fun choose_80_opcode_table[8] =
{
/*0x00*/	add_i2rm_b,or_i2rm_b,adc_i2rm_b,sbb_i2rm_b,
/*0x04*/	and_i2rm_b,sub_i2rm_b,xor_i2rm_b,cmp_i2rm_b,
};

helper_fun choose_81_opcode_table[8] =
{
/*0x00*/	add_i2rm_v,or_i2rm_v,adc_i2rm_v,sbb_i2rm_v,
/*0x04*/	and_i2rm_v,sub_i2rm_v,xor_i2rm_v,cmp_i2rm_v
};

helper_fun choose_83_opcode_table[8] = 
{
/*0x00*/	add_ib2rm_v,or_ib2rm_v,adc_ib2rm_v,sbb_ib2rm_v,
/*0x04*/	and_ib2rm_v,sub_ib2rm_v,xor_ib2rm_v,cmp_ib2rm_v
};

helper_fun choose_ff_opcode_table[8] = 
{
/*0x00*/	inc_rm_v,dec_rm_v,call_rm,inv,	
/*0x04*/	jmp_rm_v,inv,push_m_v,inv
};

helper_fun choose_fe_opcode_table[8] =
{
/*0x00*/	inc_rm_b,dec_rm_b,inv,inv,
/*ox04*/	inv,inv,inv,inv
};

helper_fun choose_f6_opcode_table[8] = 
{
/*0x00*/	test_i2rm_b,inv,not_r_b,neg_r_b,
/*0x04*/	mul_rm2al_b,imul_rm2al_b,inv,idiv_rm2al_b
};

helper_fun choose_f7_opcode_table[8] = 
{
/*0x00*/	test_i2rm_v,inv,not_r_v,neg_r_v,
/*0x04*/	mul_rm2al_v,imul_rm2al_v,inv,idiv_rm2al_v
};

helper_fun choose_c0_opcode_table[8] = 
{
/*0x00*/	inv,inv,inv,inv,
/*0x04*/	sal_ib2rm_b,shr_ib2rm_b,inv,sar_ib2rm_b
};

helper_fun choose_c1_opcode_table[8] = 
{
/*0x00*/	inv,inv,inv,inv,
/*0x04*/	sal_ib2rm_v,shr_ib2rm_v,inv,sar_ib2rm_v
};

helper_fun choose_d0_opcode_table[8] = 
{
/*0x00*/	inv,inv,inv,inv,
/*0x04*/	sal_12rm_b,shr_12rm_b,inv,sar_12rm_b
};

helper_fun choose_d1_opcode_table[8] = 
{
/*0x00*/	inv,inv,inv,inv,
/*0x04*/	sal_12rm_v,shr_12rm_v,inv,sar_12rm_v
};

helper_fun choose_d2_opcode_table[8] = 
{
/*0x00*/	inv,inv,inv,inv,
/*0x04*/	sal_cl2rm_b,shr_cl2rm_b,inv,sar_cl2rm_b
};

helper_fun choose_d3_opcode_table[8] = 
{
/*0x00*/	inv,inv,inv,inv,
/*0x04*/	sal_cl2rm_v,shr_cl2rm_v,inv,sar_cl2rm_v
};

int exec_choose_80(int i , swaddr_t eip)
{
	return choose_80_opcode_table[i](eip);
}

int exec_choose_81(int i ,swaddr_t eip)
{
	return choose_81_opcode_table[i](eip);
}

int exec_choose_83(int i , swaddr_t eip)
{
	return choose_83_opcode_table[i](eip);
}

int exec_choose_ff(int i , swaddr_t eip)
{
	return choose_ff_opcode_table[i](eip);
}

int exec_choose_fe(int i , swaddr_t eip)
{
	return choose_fe_opcode_table[i](eip);
}

int exec_choose_f6(int i , swaddr_t eip)
{
	return choose_f6_opcode_table[i](eip);
}

int exec_choose_f7(int i , swaddr_t eip)
{
	return choose_f7_opcode_table[i](eip);
}

int exec_choose_c0(int i , swaddr_t eip)
{
	return choose_c0_opcode_table[i](eip);
}

int exec_choose_c1(int i , swaddr_t eip)
{
	return choose_c1_opcode_table[i](eip);
}

int exec_choose_d0(int i , swaddr_t eip)
{
	return choose_d0_opcode_table[i](eip);
}

int exec_choose_d1(int i , swaddr_t eip)
{
	return choose_d1_opcode_table[i](eip);
}

int exec_choose_d2(int i , swaddr_t eip)
{
	return choose_d2_opcode_table[i](eip);
}

int exec_choose_d3(int i , swaddr_t eip)
{
	return choose_d3_opcode_table[i](eip);
}

make_helper(exec) {
	return opcode_table[ instr_fetch(eip, 1) ](eip);
}

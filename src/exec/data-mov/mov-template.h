#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(mov_i2r_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	DATA_TYPE imm = instr_fetch(eip + 1, DATA_BYTE);
	REG(reg_code) = imm;

	print_asm("mov" str(SUFFIX) " $0x%x,%%%s", imm, REG_NAME(reg_code));
	return DATA_BYTE + 1;
}

make_helper(concat(mov_i2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		REG(m.R_M) = imm;
		print_asm("mov" str(SUFFIX) " $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		MEM_W(addr, imm);
		print_asm("mov" str(SUFFIX) " $0x%x,%s", imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}

make_helper(concat(mov_r2rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		REG(m.R_M) = REG(m.reg);
		print_asm("mov" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.reg), REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		MEM_W(addr, REG(m.reg));

		print_asm("mov" str(SUFFIX) " %%%s,%s", REG_NAME(m.reg), ModR_M_asm);
		return len + 1;
	}
}

make_helper(concat(mov_rm2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		REG(m.reg) = REG(m.R_M);
		print_asm("mov" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		REG(m.reg) = MEM_R(addr);

		print_asm("mov" str(SUFFIX) " %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}

make_helper(concat(mov_a2moffs_, SUFFIX)) {
	swaddr_t addr = instr_fetch(eip + 1, 4);
	MEM_W(addr, REG(R_EAX));

	print_asm("mov" str(SUFFIX) " %%%s,0x%x", REG_NAME(R_EAX), addr);
	return 5;
}

make_helper(concat(mov_moffs2a_, SUFFIX)) {
	swaddr_t addr = instr_fetch(eip + 1, 4);
	REG(R_EAX) = MEM_R(addr);

	print_asm("mov" str(SUFFIX) " 0x%x,%%%s", addr, REG_NAME(R_EAX));
	return 5;
}





make_helper(concat(movsx_rmb2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
        int8_t dest_tmp=REG(m.R_M);
        DATA_TYPE_S dest=dest_tmp;
		REG(m.reg) = dest;
		print_asm("movsx" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
        int8_t dest_tmp=MEM_R(addr);
        DATA_TYPE_S dest=dest_tmp;
		REG(m.reg) = dest;

		print_asm("movsx" str(SUFFIX) " %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}

make_helper(concat(movsx_rmw2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
        int16_t dest_tmp=REG(m.R_M);
        DATA_TYPE_S dest=dest_tmp;
		REG(m.reg) = dest;
		print_asm("movsx" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
        int16_t dest_tmp=MEM_R(addr);
        DATA_TYPE_S dest=dest_tmp;
		REG(m.reg) = dest;

		print_asm("movsx" str(SUFFIX) " %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}

make_helper(concat(movzx_rmb2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
        uint8_t dest_tmp=REG(m.R_M);
        DATA_TYPE dest=dest_tmp;
		REG(m.reg) = dest;
		print_asm("movzx" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
        uint8_t dest_tmp=MEM_R(addr);
        DATA_TYPE dest=dest_tmp;
		REG(m.reg) = dest;

		print_asm("movzx" str(SUFFIX) " %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}

make_helper(concat(movzx_rmw2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
        uint16_t dest_tmp=REG(m.R_M);
        DATA_TYPE dest=dest_tmp;
		REG(m.reg) = dest;
		print_asm("movzx" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
        uint16_t dest_tmp=MEM_R(addr);
        DATA_TYPE dest=dest_tmp;
		REG(m.reg) = dest;

		print_asm("movzx" str(SUFFIX) " %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}

make_helper(concat(mov_rm2sr_,SUFFIX))
{
	ModR_M m;
	m.val = instr_fetch(eip + 1 , 1);
	if(m.mod == 3)
	{
		sreg(m.reg) = REG(m.R_M);
		print_asm("mov  %%%s , %%%s" , REG_NAME(m.R_M) ,SREG_NAME[m.reg]);
		return 2;
	}
	else
	{
		swaddr_t addr  ;
		int len = read_ModR_M(eip + 1 , &addr);
		sreg(m.reg) = MEM_R(addr);
		print_asm("mov %s , %%%s",ModR_M_asm , SREG_NAME[m.reg]);

		return len + 1;
	}
}

make_helper(concat(mov_sr2rm_ , SUFFIX))
{
	ModR_M m;
	m.val = instr_fetch(eip + 1 , 1);
	if(m.mod == 3)
	{
		REG(m.R_M) = sreg(m.reg);
		print_asm("mov  %%%s , %%%s" , SREG_NAME[m.reg] , REG_NAME(m.R_M));
		return 2;
	}
	else
	{
		swaddr_t addr ; 
		int len = read_ModR_M(eip + 1 , &addr);
		MEM_W(addr , sreg(m.reg));
		print_asm("mov %%%s , %s" , SREG_NAME[m.reg] , ModR_M_asm);

		return len + 1;

	}
}
#include "exec/template-end.h"

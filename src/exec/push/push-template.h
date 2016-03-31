#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
extern uint8_t current_sreg;

make_helper(concat(push_r_,SUFFIX))
{
	current_sreg = SS;
    int reg_code=instr_fetch(eip,1) & 0x7;
    MEM_W(REG(R_ESP)-DATA_BYTE,REG(reg_code));
    REG(R_ESP)-=DATA_BYTE;
    print_asm("push"str(SUFFIX)  " %%%s",REG_NAME(reg_code));
    return 1;
}

make_helper(concat(push_i_,SUFFIX))
{
	current_sreg = SS;
    DATA_TYPE_S imm;
    imm=instr_fetch(eip+1,DATA_BYTE);
    REG(R_ESP)-=DATA_BYTE;
	current_sreg = SS;
    MEM_W(REG(R_ESP),imm);
    print_asm("push"str(SUFFIX)" $0x%x",imm);
    return 1+DATA_BYTE;
}

make_helper(concat(push_m_,SUFFIX))
{
	current_sreg = SS;
    ModR_M m;
    m.val = instr_fetch(eip+1,1);
    swaddr_t addr;
    int len = read_ModR_M(eip + 1, &addr);
    REG(R_ESP)-=DATA_BYTE;
    MEM_W(REG(R_ESP),addr);
    print_asm("push"str(SUFFIX)" %s,%%%s",ModR_M_asm,REG_NAME(m.reg));
    return 1 + len;
}

make_helper(concat(pusha_,SUFFIX))
{
	current_sreg = SS;
	uint32_t temp = REG(R_ESP);
	REG(R_ESP)-=DATA_BYTE;
	MEM_W(REG(R_ESP) , REG(R_EAX));
	REG(R_ESP)-=DATA_BYTE;
	MEM_W(REG(R_ESP) , REG(R_ECX));
	REG(R_ESP)-=DATA_BYTE;
	MEM_W(REG(R_ESP) , REG(R_EDX));
	REG(R_ESP)-=DATA_BYTE;
	MEM_W(REG(R_ESP) , REG(R_EBX));
	REG(R_ESP)-=DATA_BYTE;
	MEM_W(REG(R_ESP) , temp);
	REG(R_ESP)-=DATA_BYTE;
	MEM_W(REG(R_ESP) , REG(R_EBP));
	REG(R_ESP)-=DATA_BYTE;
	MEM_W(REG(R_ESP) , REG(R_ESI));
	REG(R_ESP)-=DATA_BYTE;
	MEM_W(REG(R_ESP) , REG(R_EDI));
	print_asm("pusha"str(SUFFIX));
	return 1;
}
#include "exec/template-end.h"

#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
extern uint8_t current_sreg;
make_helper(concat(pop_r_,SUFFIX))
{
	current_sreg = SS;
    int reg_code=instr_fetch(eip,1)&0x07;
    DATA_TYPE_S pop_result;
    pop_result=MEM_R(REG(R_ESP));
    REG(reg_code)=pop_result;
    REG(R_ESP)+=DATA_BYTE;
    print_asm("pop" str(SUFFIX) " %%%s",REG_NAME(reg_code));

    return 1;
}

make_helper(concat(pop_m_,SUFFIX))
{
	current_sreg = SS;
    ModR_M m;
    m.val = instr_fetch(eip+1,1);
    swaddr_t addr;
    int len = read_ModR_M(eip + 1, &addr);
    DATA_TYPE_S pop_result;
    pop_result=MEM_R(REG(R_ESP));
    MEM_W(addr,pop_result);
    REG(R_ESP)+=DATA_BYTE;
    print_asm("pop" str(SUFFIX) " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));

    return 1 + len;
}

make_helper(concat(popa_ , SUFFIX))
{
	current_sreg = SS;
//	uint32_t temp;
	REG(R_EDI) = MEM_R(REG(R_ESP));
	REG(R_ESP)-=DATA_BYTE;

	REG(R_ESI) = MEM_R(REG(R_ESP));
	REG(R_ESP)-=DATA_BYTE;

	REG(R_EBP) = MEM_R(REG(R_ESP));
	REG(R_ESP)-=DATA_BYTE;

//	temp = MEM_R(REG(R_ESP));
	REG(R_ESP)-=DATA_BYTE;

	REG(R_EBX) = MEM_R(REG(R_ESP));
	REG(R_ESP)-=DATA_BYTE;

	REG(R_EDX) = MEM_R(REG(R_ESP));
	REG(R_ESP)-=DATA_BYTE;

	REG(R_ECX) = MEM_R(REG(R_ESP));
	REG(R_ESP)-=DATA_BYTE;

	REG(R_EAX) = MEM_R(REG(R_ESP));
	REG(R_ESP)-=DATA_BYTE;

	return 1;
}
#include "exec/template-end.h"

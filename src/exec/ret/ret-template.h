#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
extern uint8_t current_sreg;
make_helper(concat(ret_,SUFFIX))
{
	current_sreg = SS;
    cpu.eip=MEM_R(REG(R_ESP));
    REG(R_ESP)+=DATA_BYTE;
    print_asm("ret");
    return 1;
}

make_helper(concat(ret_imm_,SUFFIX))
{
	current_sreg = SS;
    int16_t imm=instr_fetch(eip+1,2);
    cpu.eip=MEM_R(REG(R_ESP));
    REG(R_ESP)+=DATA_BYTE;
    REG(R_ESP)+=imm;
    print_asm("ret" " $0x%X",imm);
    return 1;
}
#include "exec/template-end.h"

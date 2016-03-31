#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
extern uint8_t current_sreg;
make_helper(concat(leave_,SUFFIX))
{
	current_sreg = SS;
    REG(R_ESP)=REG(R_EBP);
    REG(R_EBP)=MEM_R(REG(R_ESP));
    REG(R_ESP)=REG(R_ESP)+DATA_BYTE;
    print_asm("leave");
    return 1;
}

#include "exec/template-end.h"

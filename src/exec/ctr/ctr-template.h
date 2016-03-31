#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(movs_,SUFFIX))
{
    int inc=0;
    MEM_W(REG(R_EDI),MEM_R(REG(R_ESI)));
    if(cpu.DF == 0)
        inc = DATA_BYTE;
    else
        inc = -DATA_BYTE;
    REG(R_ESI) = REG(R_ESI) + inc;
    REG(R_EDI) += inc;
    print_asm("movs"str(SUFFIX)" %%ds:(%%esi),%%es:(%%edi)");
    return 1;
}
make_helper(concat(stos_,SUFFIX))
{
	int inc = 0;
	MEM_W(REG(R_EDI), REG(R_EAX));
	if(cpu.DF == 0)
		inc = DATA_BYTE;
	else
		inc = -DATA_BYTE;
	REG(R_EDI) = REG(R_EDI) + inc;
	print_asm("stos"str(SUFFIX) "%%%s , %%es:(%%edi)", REG_NAME(0));
	return 1;
}

#include "exec/template-end.h"

#include "exec/helper.h"
#include "cpu/modrm.h"
make_helper(cltd)
{
	if(reg_l(R_EAX)>>31)
		reg_l(R_EDX) = 0xffffffff;
	else
		reg_l(R_EDX) = 0x00000000;
	print_asm("cltd\n");
	return 1;
}

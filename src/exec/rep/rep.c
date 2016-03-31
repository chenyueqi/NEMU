#include "exec/helper.h"
#include "cpu/modrm.h"
extern char suffix;
make_helper(exec);
make_helper(rep)
{

	uint32_t countreg;
       	if(suffix == 'w')
       		countreg = reg_w(R_ECX); 
	else
		countreg = reg_l(R_ECX);
       	while(countreg > 0)
       	{
		exec(eip + 1);
		countreg --;		
       	}
	print_asm("rep movs" " %%ds:(%%esi) , %%es:(%%edi)");
       	return 2;
}

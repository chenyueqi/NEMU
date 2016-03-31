#include "exec/helper.h"

#define DATA_BYTE 2
#include "lgdt_lidt-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "lgdt_lidt-template.h"
#undef DATA_BYTE




extern char suffix;
make_helper(lgdt_lidt_v)
{
	return (suffix == 'l' ? lgdt_lidt_l(eip) : lgdt_lidt_w(eip));
}

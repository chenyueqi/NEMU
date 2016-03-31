#include "exec/helper.h"

#define DATA_BYTE 1
#include "ctr-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "ctr-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "ctr-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(movs_v)
{
    return (suffix == 'l' ? movs_l(eip) : movs_w(eip));
}

make_helper(stos_v)
{
	return (suffix == 'l' ? stos_l(eip) : stos_w(eip));
}

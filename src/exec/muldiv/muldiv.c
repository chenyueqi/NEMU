#include "exec/helper.h"

#define DATA_BYTE 1
#include "muldiv-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "muldiv-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "muldiv-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(mul_rm2al_v)
{
    return (suffix == 'l' ? mul_rm2al_l(eip) : mul_rm2al_w(eip));
}

make_helper(imul_rm2al_v)
{
    return (suffix == 'l' ? imul_rm2al_l(eip) : imul_rm2al_w(eip));
}

make_helper(imul_rm2r_v)
{
    return (suffix == 'l' ? imul_rm2r_l(eip) : imul_rm2r_w(eip));
}

make_helper(imul_ib2r_v)
{
    return (suffix == 'l' ? imul_ib2r_l(eip) : imul_ib2r_w(eip));
}

make_helper(imul_i2r_v)
{
    return (suffix == 'l' ? imul_i2r_l(eip) : imul_i2r_w(eip));
}
make_helper(idiv_rm2al_v)
{
    return (suffix == 'l' ? idiv_rm2al_l(eip) : idiv_rm2al_w(eip));
}

make_helper(div_rm2al_v)
{
    return (suffix == 'l' ? div_rm2al_l(eip) : div_rm2al_w(eip));
}

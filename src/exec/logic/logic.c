#include "exec/helper.h"

#define Operator and
#define sign 0
#define DATA_BYTE 1
#include "logic-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "logic-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "logic-template.h"
#undef DATA_BYTE
#undef Operator
#undef sign

#define __SHIFT_
#define Operator or
#define sign 1
#define DATA_BYTE 1
#include "logic-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "logic-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "logic-template.h"
#undef DATA_BYTE
#undef Operator
#undef sign

#define Operator xor
#define sign 2
#define DATA_BYTE 1
#include "logic-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "logic-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "logic-template.h"
#undef DATA_BYTE
#undef Operator
#undef sign
#undef __SHIFT_
extern char suffix;

make_helper(and_i2a_v)
{
    return (suffix == 'l' ? and_i2a_l(eip) : and_i2a_w(eip));
}

make_helper(and_r2rm_v)
{
    return (suffix == 'l' ? and_r2rm_l(eip) : and_r2rm_w(eip));
}

make_helper(and_rm2r_v)
{
    return (suffix == 'l' ? and_rm2r_l(eip) : and_rm2r_w(eip));
}

make_helper(and_ib2rm_v)
{
    return (suffix == 'l' ? and_ib2rm_l(eip) : and_ib2rm_w(eip));
}

make_helper(and_i2rm_v)
{
    return (suffix == 'l' ? and_i2rm_l(eip) : and_i2rm_w(eip));
}

make_helper(not_r_v)
{
    return (suffix == 'l' ? not_r_l(eip) : not_r_w(eip));
}

make_helper(or_i2a_v)
{
    return (suffix == 'l' ? or_i2a_l(eip) : or_i2a_w(eip));
}

make_helper(or_r2rm_v)
{
    return (suffix == 'l' ? or_r2rm_l(eip) : or_r2rm_w(eip));
}

make_helper(or_rm2r_v)
{
    return (suffix == 'l' ? or_rm2r_l(eip) : or_rm2r_w(eip));
}

make_helper(or_ib2rm_v)
{
    return (suffix == 'l' ? or_ib2rm_l(eip) : or_ib2rm_w(eip));
}

make_helper(or_i2rm_v)
{
    return (suffix == 'l' ? xor_i2rm_l(eip) : xor_i2rm_w(eip));
}




make_helper(xor_i2a_v)
{
    return (suffix == 'l' ? xor_i2a_l(eip) : xor_i2a_w(eip));
}

make_helper(xor_r2rm_v)
{
    return (suffix == 'l' ? xor_r2rm_l(eip) : xor_r2rm_w(eip));
}

make_helper(xor_rm2r_v)
{
    return (suffix == 'l' ? xor_rm2r_l(eip) : xor_rm2r_w(eip));
}

make_helper(xor_ib2rm_v)
{
    return (suffix == 'l' ? xor_ib2rm_l(eip) : xor_ib2rm_w(eip));
}

make_helper(xor_i2rm_v)
{
    return (suffix == 'l' ? xor_i2rm_l(eip) : xor_i2rm_w(eip));
}

make_helper(sal_12rm_v)
{
    return (suffix == 'l' ? sal_12rm_l(eip) : sal_12rm_w(eip));
}
make_helper(sal_ib2rm_v)
{
    return (suffix == 'l' ? sal_ib2rm_l(eip) : sal_ib2rm_w(eip));
}
make_helper(sal_cl2rm_v)
{
    return (suffix == 'l' ? sal_cl2rm_l(eip) : sal_cl2rm_w(eip));
}

make_helper(sar_12rm_v)
{
    return (suffix == 'l' ? sar_12rm_l(eip) : sar_12rm_w(eip));
}
make_helper(sar_ib2rm_v)
{
    return (suffix == 'l' ? sar_ib2rm_l(eip) : sar_ib2rm_w(eip));
}
make_helper(sar_cl2rm_v)
{
    return (suffix == 'l' ? sar_cl2rm_l(eip) : sar_cl2rm_w(eip));
}

make_helper(shr_12rm_v)
{
    return (suffix == 'l' ? shr_12rm_l(eip) : shr_12rm_w(eip));
}
make_helper(shr_ib2rm_v)
{
    return (suffix == 'l' ? shr_ib2rm_l(eip) : shr_ib2rm_w(eip));
}
make_helper(shr_cl2rm_v)
{
    return (suffix == 'l' ? shr_cl2rm_l(eip) : shr_cl2rm_w(eip));
}

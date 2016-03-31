#include "exec/helper.h"

#define Operator add
#define sign 1
#define DATA_BYTE 1
#include "add-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "add-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "add-template.h"
#undef DATA_BYTE
#undef sign
#undef Operator

#define Operator adc
#define sign 0
#define DATA_BYTE 1
#include "add-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "add-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "add-template.h"
#undef DATA_BYTE
#undef sign
#undef Operator

#define Operator sub
#define sign 3
#define DATA_BYTE 1
#include "add-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "add-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "add-template.h"
#undef DATA_BYTE
#undef sign
#undef Operator


#define Operator sbb
#define sign 2
#define DATA_BYTE 1
#include "add-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "add-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "add-template.h"
#undef DATA_BYTE
#undef sign
#undef Operator
extern char suffix;

make_helper(add_i2a_v)
{
    return (suffix == 'l' ? add_i2a_l(eip) : add_i2a_w(eip));
}

make_helper(add_r2rm_v)
{
    return (suffix == 'l' ? add_r2rm_l(eip) : add_r2rm_w(eip));
}

make_helper(add_rm2r_v)
{
    return (suffix == 'l' ? add_rm2r_l(eip) : add_rm2r_w(eip));
}

make_helper(add_ib2rm_v)
{
    return (suffix == 'l' ? add_ib2rm_l(eip) : add_ib2rm_w(eip));
}

make_helper(add_i2rm_v)
{
    return (suffix == 'l' ? add_i2rm_l(eip) : add_i2rm_w(eip));
}



make_helper(adc_i2a_v)
{
    return (suffix == 'l' ? adc_i2a_l(eip) : adc_i2a_w(eip));
}

make_helper(adc_r2rm_v)
{
    return (suffix == 'l' ? adc_r2rm_l(eip) : adc_r2rm_w(eip));
}

make_helper(adc_rm2r_v)
{
    return (suffix == 'l' ? adc_rm2r_l(eip) : adc_rm2r_w(eip));
}

make_helper(adc_ib2rm_v)
{
    return (suffix == 'l' ? adc_ib2rm_l(eip) : adc_ib2rm_w(eip));
}

make_helper(adc_i2rm_v)
{
    return (suffix == 'l' ? adc_i2rm_l(eip) : adc_i2rm_w(eip));
}




make_helper(sub_i2a_v)
{
    return (suffix == 'l' ? sub_i2a_l(eip) : sub_i2a_w(eip));
}

make_helper(sub_r2rm_v)
{
    return (suffix == 'l' ? sub_r2rm_l(eip) : sub_r2rm_w(eip));
}

make_helper(sub_rm2r_v)
{
    return (suffix == 'l' ? sub_rm2r_l(eip) : sub_rm2r_w(eip));
}

make_helper(sub_ib2rm_v)
{
    return (suffix == 'l' ? sub_ib2rm_l(eip) : sub_ib2rm_w(eip));
}

make_helper(sub_i2rm_v)
{
    return (suffix == 'l' ? sub_i2rm_l(eip) : sub_i2rm_w(eip));
}


make_helper(sbb_i2a_v)
{
    return (suffix == 'l' ? sbb_i2a_l(eip) : sbb_i2a_w(eip));
}

make_helper(sbb_r2rm_v)
{
    return (suffix == 'l' ? sbb_r2rm_l(eip) : sbb_r2rm_w(eip));
}

make_helper(sbb_rm2r_v)
{
    return (suffix == 'l' ? sbb_rm2r_l(eip) : sbb_rm2r_w(eip));
}

make_helper(sbb_ib2rm_v)
{
    return (suffix == 'l' ? sbb_ib2rm_l(eip) : sbb_ib2rm_w(eip));
}

make_helper(sbb_i2rm_v)
{
    return (suffix == 'l' ? sbb_i2rm_l(eip) : sbb_i2rm_w(eip));
}

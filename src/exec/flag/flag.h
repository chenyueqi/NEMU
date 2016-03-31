#ifndef _FLAG_H
#define _FLAG_H

make_helper(cld);
make_helper(cli);
make_helper(std);
make_helper(hlt);

void add_flags(uint8_t msb_m,uint8_t msb_s,uint8_t msb_r,uint32_t r);
void sub_flags(uint8_t msb_m,uint8_t msb_s,uint8_t msb_r,uint32_t r);
void PF_W(uint32_t num);

#endif

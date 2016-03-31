#include "exec/helper.h"
#include "cpu/modrm.h"
int exec_choose_80(int , swaddr_t);
int exec_choose_81(int , swaddr_t);
int exec_choose_83(int , swaddr_t);
int exec_choose_ff(int , swaddr_t);
int exec_choose_fe(int , swaddr_t);
int exec_choose_f6(int , swaddr_t);
int exec_choose_f7(int , swaddr_t);
int exec_choose_c0(int , swaddr_t);
int exec_choose_c1(int , swaddr_t);
int exec_choose_d0(int , swaddr_t);
int exec_choose_d1(int , swaddr_t);
int exec_choose_d2(int , swaddr_t);
int exec_choose_d3(int , swaddr_t);

make_helper(concat(choose_,NUM_SUFFIX))
{
	ModR_M m;
	m.val = instr_fetch(eip + 1 , 1);
	int instr_len = (concat(exec_choose_,NUM_SUFFIX))(m.reg, eip);
	return instr_len;	
}



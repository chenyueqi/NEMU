#include "ui/ui.h"

#include "nemu.h"

#include <setjmp.h>
#include"ui/breakpoint.h"
#include"ui/expr.h"

#define LOADER_START_EIP 0x100000


#define LOADER_START_EFLAGS 0x2

int exec(swaddr_t);
void load_prog();
void init_dram();
void init_cache_L1();
void init_cache_L2();
void init_tlb();
static int eip1;

char assembly[40];
jmp_buf jbuf;	/* Make it easy to perform exception handling */

extern uint8_t loader [];
extern uint32_t loader_len;

extern int quiet;

void restart() {
	/* Perform some initialization to restart a program */
	load_prog();
	memcpy(hwa_to_va(LOADER_START_EIP), loader, loader_len);

	cpu.eip = LOADER_START_EIP;
	cpu.EFLAGS = LOADER_START_EFLAGS;
	cpu.ebp=0x0;
	cpu.esp=0x8000000;
	init_cache_L1();
	init_cache_L2();
	init_tlb();
	init_dram();
	cpu.PE = 0;
	cpu.PG = 0;
	cpu.sreg_discribe[CS].base = 0;
	cpu.sreg_discribe[CS].limit = 0xffff;

}

static void print_bin_instr(swaddr_t eip, int len) {
	int i;
	printf("%8x:   ", eip);
	for(i = 0; i < len; i ++) {
		printf("%02x ", swaddr_read(eip + i, 1));
	}
	printf("%*.s", 50 - (12 + 3 * len), "");
}

void cpu_exec(volatile uint32_t n) {
	volatile uint32_t n_temp = n;

	setjmp(jbuf);
	for(; n > 0; n --) {
		swaddr_t eip_temp = cpu.eip;
		int instr_len = exec(cpu.eip);

		cpu.eip += instr_len;

		if(n_temp != -1 || (enable_debug && !quiet)) {
			print_bin_instr(eip_temp, instr_len);
			puts(assembly);
		}
		if(checkw())
		{
			return;
		}
		reset_b();
		if(nemu_state == INT) 
		{		
			cpu.eip--;
			eip1=cpu.eip;
			BP* p;
			p=bfind(cpu.eip,'b');
			swaddr_write(cpu.eip,1,p->content);
			assert(swaddr_read(cpu.eip,1) == p->content);
			printf("  breakpoint   %d    0x%X\n",p->NO,p->address);
			return;
		} 
		else if(nemu_state == END) { return; }
	}
}

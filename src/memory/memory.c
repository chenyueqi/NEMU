#include "common.h"
#include "cpu/reg.h"
uint8_t current_sreg;
uint32_t dram_read(hwaddr_t addr, size_t len);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);

uint32_t lnaddr_read(lnaddr_t addr,size_t len);
void lnaddr_write(lnaddr_t addr, size_t len , uint32_t data);

extern uint32_t cache_read_L1(hwaddr_t addr,size_t len);
extern void cache_write_L1(hwaddr_t addr, size_t len,uint32_t data);

lnaddr_t segment_translate(swaddr_t addr , size_t len, uint8_t current_sreg);
hwaddr_t page_translate(lnaddr_t addr);

hwaddr_t tlb_read(lnaddr_t addr);
/* Memory accessing interfaces */

uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
//	return dram_read(addr, len);
	return cache_read_L1(addr, len);
}

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	//dram_write(addr, len, data);
	cache_write_L1(addr, len, data);
}

uint32_t swaddr_read(swaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
//	return hwaddr_read(addr, len);
	lnaddr_t lnaddr = segment_translate(addr , len , current_sreg);
	return lnaddr_read(lnaddr,len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
//	hwaddr_write(addr, len, data);
	lnaddr_t lnaddr = segment_translate(addr , len , current_sreg);
	return lnaddr_write(lnaddr , len , data);
}

/*static uint32_t hwaddr_read_instr(hwaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	return dram_read(addr, len);
}*/

uint32_t instr_fetch(swaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	current_sreg = CS;
	//return hwaddr_read_instr(addr, len);
	return swaddr_read(addr , len);
}

uint32_t lnaddr_read(lnaddr_t addr,size_t len)
{
	assert(len == 1 || len ==2 || len == 4);
//	if(data cross page boundary)
//	{
//		assert(0);
//	}
//	else
//	{
		hwaddr_t hwaddr = page_translate(addr);
		return hwaddr_read(hwaddr, len);
//	}
	return hwaddr_read(addr , len);
}

void lnaddr_write(lnaddr_t addr, size_t len , uint32_t data)
{
	assert(len == 1 || len ==2 || len == 4);
	hwaddr_t hwaddr = page_translate(addr);
	return hwaddr_write(hwaddr, len ,data);
}


lnaddr_t segment_translate(swaddr_t addr , size_t len, uint8_t current_sreg)
{
	assert(len == 1 || len ==2 || len == 4);
	if(cpu.PE == 0)
		return addr;
	else
	{

		uint32_t segbase = cpu.sreg_discribe[current_sreg].base;
		uint32_t lnaddr;		
		lnaddr = addr + segbase;
		return lnaddr;
	}
	
}


hwaddr_t page_translate(lnaddr_t addr)
{
	if(cpu.PG == 0)
		return addr;
	else
	{	
		return tlb_read(addr);
	}
}


















#include "common.h"
#include "cpu/reg.h"
#include "lib/misc.h"
#include "stdlib.h"
#include "time.h"

#define SLOT 64
uint32_t hwaddr_read(hwaddr_t addr , size_t len);
typedef struct
{
	bool valid;
	uint32_t va_tag;
	uint32_t pa_tag;
} LINE;

LINE tlb[SLOT];

typedef union PageDirectoryEntry
{
	struct
	{
		uint32_t present		:1;
		uint32_t read_write		:1;
		uint32_t user_supervisor	:1;
		uint32_t page_write_through	:1;
		uint32_t page_cache_disable	:1;
		uint32_t accessed		:1;
		uint32_t pad0			:6;
		uint32_t page_frame		:20;
	};
	uint32_t val;
} PDE;


typedef union PageTableEntry
{
	struct
	{
		uint32_t present		:1;
		uint32_t read_write		:1;
		uint32_t user_supervisor	:1;
		uint32_t page_write_through	:1;
		uint32_t page_cache_disable	:1;
		uint32_t accessed		:1;
		uint32_t dirty			:1;
		uint32_t pad0			:1;
		uint32_t global			:1;
		uint32_t pad1			:3;
		uint32_t page_frame		:20;
	};
	uint32_t val;
} PTE;

hwaddr_t tlb_read(lnaddr_t addr);
void init_tlb();

void init_tlb()
{
	int i;
	for(i = 0; i<SLOT;i++)
	{
		tlb[i].valid = false;
	}
}

hwaddr_t tlb_read(lnaddr_t addr)
{
	uint32_t va_tag = addr & 0xfffff000 ;
	uint32_t offset = addr & 0x00000fff ;
	int i;
	for(i=0; i< SLOT ;i++)
	{
		if((tlb[i].valid == true) && (va_tag == tlb[i].va_tag))
			return (tlb[i].pa_tag + offset) ;
	}

	uint32_t pdir_idx , ptable_idx;
	pdir_idx = addr >> 22;
	ptable_idx = (addr & 0x003ff000) >> 12;

	uint32_t pdir_base;
	pdir_base = (cpu.cr3 & 0xfffff000) + (pdir_idx << 2);
	PDE pdir_entry;
	pdir_entry.val = hwaddr_read(pdir_base ,4);

	uint32_t ptable_base;
	ptable_base = (pdir_entry.val & 0xfffff000) + (ptable_idx << 2);
	PTE ptable_entry;
	ptable_entry.val = hwaddr_read(ptable_base , 4);
	uint32_t pa_tag = ptable_entry.val & 0xfffff000;
	srand((unsigned)time(NULL));
	uint8_t line;	
	line = rand() % SLOT;
	tlb[line].valid = true;
	tlb[line].va_tag = va_tag;
	tlb[line].pa_tag = pa_tag;
	return pa_tag + offset;
}

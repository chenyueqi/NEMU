#include "common.h"
#include "memory.h"
#include <string.h>

#include <elf.h>

#ifdef HAS_DEVICE
#define ELF_OFFSET_IN_DISK 0
#endif

#define STACK_SIZE (1 << 20)

void ide_read(uint8_t *, uint32_t, uint32_t);
void create_video_mapping();
uint32_t get_ucr3();

uint32_t loader() {
	Elf32_Ehdr *elf;
	Elf32_Phdr *ph = NULL;

#ifdef HAS_DEVICE
	uint8_t buf[4096];
	ide_read(buf, ELF_OFFSET_IN_DISK, 4096);
	elf = (void*)buf;
#else
	/* The ELF file is located at memory address 0 */
	elf = (void *)0x0;
#endif

	/* Load each program segment */
	int i;
	for(i = 0; i < elf->e_phnum; i++ ) 
	{
		ph = (void *)(elf->e_phoff + i * elf->e_phentsize);
		/* Scan the program header table, load each segment into memory */
		if(ph->p_type == PT_LOAD) 
		{
			int j;
			char *p, *q;
			uint32_t pha;
		      	pha = mm_malloc(ph->p_vaddr, ph->p_memsz);
			for( j = 0;j < ph->p_filesz ; j++)
			{
				p = (void *)(pha + j);
				q = (void *)(ph->p_offset + j);
				*p = *q;
			}
			for( j = ph->p_filesz ; j < ph->p_memsz ; j++)
			{
				p = (void *)(pha + j);
				*p = 0;
			}

			extern uint32_t brk;
			uint32_t new_brk = ph->p_vaddr + ph->p_memsz - 1;
			if(brk < new_brk) { brk = new_brk; }
		}
	}
	volatile uint32_t entry = elf->e_entry;

#ifdef IA32_PAGE
	mm_malloc(KOFFSET - STACK_SIZE, STACK_SIZE);

#ifdef HAS_DEVICE
	create_video_mapping();
#endif

	write_cr3(get_ucr3());
#endif

	return entry;
}

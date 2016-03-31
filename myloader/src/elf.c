#include <elf.h>
#include "trap.h"

void loader() {
    Elf32_Ehdr *elf = (void *)0;

    int i;
    for (i = 0; i < elf->e_phnum; i++)
    {
        Elf32_Phdr *ph = (void *)(elf->e_phoff + i * elf->e_phentsize);
        if(ph->p_type == PT_LOAD)
        {
            int j;
            char *p,*q;
            for(j=0 ; j < ph->p_filesz; j++)
            {
                p = (void *)(ph->p_vaddr + j);
                q = (void *)(ph->p_offset + j);
                *p = *q;
            }
            for(j = ph->p_filesz; j< ph->p_memsz; j++)
            {
                p = (void *)(ph->p_vaddr + j);
            }
        }
    }

    ((void(*)(void)) elf->e_entry) ();

    HIT_GOOD_TRAP;
}

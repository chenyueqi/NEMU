#ifndef __CPU_REG_H__
#define __CPU_REG_H__

#include "common.h"

/* TODO: Re-organize the 'CPU_state' structure to match
 * the GPR encoding scheme in i386 instruction format.
 * For example, if we access reg_w(R_BX) we will get the 'bx' register;
 * if we access reg_b(R_CH), we will get the 'ch' register.
 * Hint: Use 'union'.
 * For more details about the GPR encoding scheme, see i386 manual.
 */

typedef struct {
	union {
		union{
			uint32_t _32;
			uint16_t _16;
			uint8_t _8[2];
		} gpr[8];

	/* Do NOT change the order of the GPRs' definitions. 
	 * They match the register encoding scheme used in i386 instruction format.
	 * See i386 manual for more details.
	 */struct{

		uint32_t eax, ecx, edx, ebx, esp, ebp, esi, edi;
	 	};

         };

	 union
	{	
		swaddr_t EFLAGS ; 
/*		struct
		{
			swaddr_t haha1		:8;
			swaddr_t haha2		:8;
			swaddr_t haha3		:1;
			swaddr_t VM		:1;
			swaddr_t RF 		:1;
			swaddr_t haha4		:1;
			swaddr_t NT		:1;
			swaddr_t IOPL		:2;
			swaddr_t OF		:1;
			swaddr_t DF		:1;
			swaddr_t IF		:1;
			swaddr_t TF		:1;
			swaddr_t SF		:1;
			swaddr_t ZF		:1;
			swaddr_t haha5		:1;
			swaddr_t AF		:1;
			swaddr_t haha6		:1;		
			swaddr_t PF		:1;
			swaddr_t haha7		:1;
			swaddr_t CF		:1;	
		};*/		
		struct
		{
			swaddr_t CF		:1;
			swaddr_t hah7		:1;
			swaddr_t PF		:1;
			swaddr_t haha6		:1;
			swaddr_t AF 		:1;
			swaddr_t haha5		:1;
			swaddr_t ZF		:1;
			swaddr_t SF		:1;
			swaddr_t TF		:1;
			swaddr_t IF		:1;
			swaddr_t DF		:1;
			swaddr_t OF		:1;
			swaddr_t IOPL		:2;
			swaddr_t NT		:1;
			swaddr_t haha4		:1;
			swaddr_t RF		:1;
			swaddr_t VM		:1;		
			swaddr_t haha3		:1;
			swaddr_t haha2		:8;
			swaddr_t haha1		:8;	
		};		
	};	
	 union
	 {
		 union
		 {
			uint16_t seg_register;
		 	struct
		 	{
				uint16_t index		:13;
				uint16_t TI		:1;
				uint16_t RPL		:2;
		 	}; 
		 } sreg[4];
		 struct
		 {
			 uint16_t es , cs , ss , ds;
		 };
	 };
	 struct
	 {
		 uint32_t base;
		 uint16_t limit;
	 }sreg_discribe[4];//段描述符的部分内容
	struct
	{
		uint32_t base;
	       	uint16_t limit;	
	}gdtr;	

	struct
	{
		uint32_t base;
		uint16_t limit;
	}idtr;
	
	union
	{
		struct
		{
			uint32_t PE		:1;
			uint32_t MP		:1;
			uint32_t EM		:1;
			uint32_t TS		:1;
			uint32_t ET		:1;
			uint32_t reserved0	:26;
			uint32_t PG		:1;
		};
		uint32_t cr0;
	};
	union
	{
		struct
		{
			uint32_t reserved3	:12;
			uint32_t pdbr		:20; 
		};
		uint32_t cr3;
	};
	swaddr_t eip;
} CPU_state;

extern CPU_state cpu;

enum { R_EAX, R_ECX, R_EDX, R_EBX, R_ESP, R_EBP, R_ESI, R_EDI };
enum { R_AX, R_CX, R_DX, R_BX, R_SP, R_BP, R_SI, R_DI };
enum { R_AL, R_CL, R_DL, R_BL, R_AH, R_CH, R_DH, R_BH };
enum { ES , CS , SS , DS };

#define reg_l(index) (cpu.gpr[index]._32)
#define reg_w(index) (cpu.gpr[index]._16)
#define reg_b(index) (cpu.gpr[index & 0x3]._8[index >> 2])
#define sreg(index) (cpu.sreg[index].seg_register)

extern const char* regsl[];
extern const char* regsw[];
extern const char* regsb[];
extern const char* SREG_NAME[]; 

#endif

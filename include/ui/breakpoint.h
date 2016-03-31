#ifndef __UI_BREAKPOINT_H__
#define __UI_BREAKPOINT_H__

#include "common.h"

#define INT3_CODE 0xcc

typedef struct breakpoint {
	char s[30];
	char type;
	int NO;
	struct breakpoint *next;
	uint32_t address;
	uint8_t content;
	int val;
	/* TODO: Add more members if necessary */


} BP;
BP* new_bp(int num,uint32_t baddress,char c,char *s);
void free_bp(int num);
BP*  bfind(swaddr_t e,char c);
void infoutb();
void reset_b();
void infoutw();
bool checkw();
#endif

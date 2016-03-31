#include "trap.h"
extern void loader();

void init() {
	loader();
 
	nemu_assert(0);
}

#include "exec/helper.h"

#define DATA_BYTE 1
#include "setcc-tem.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "setcc-tem.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "setcc-tem.h"
#undef DATA_BYTE

extern char suffix;

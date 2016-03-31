#include "trap.h"
int main()
{
    char str[] = "abcdefg";
    nemu_assert(*str);
    HIT_GOOD_TRAP;
    return 0;
}


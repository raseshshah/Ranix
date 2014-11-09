/****************************** Kernel **********************************************/ 
/*generate 16-bit code*/
__asm__(".code16gcc");
__asm__("jmpl $0x1000,$main");


// diffrent module of the kernel
#include "display.c"
#include "file.c"
#include "mem.c"
#include "config.h"

void main()
{	
	sprint("Welcome Ran!x");
	while(1);
}


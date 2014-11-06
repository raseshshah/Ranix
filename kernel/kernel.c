/*generate 16-bit code*/
__asm__(".code16\n");
__asm__("jmpl $0x1000,$main");

// diffrent module of the kernel
#include "device.c"
#include "file.c"

void main() 
{
	printString("\n\rwelcome Ran!x Kernel");
	__asm__ __volatile__ ("hlt");
}


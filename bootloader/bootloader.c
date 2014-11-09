/****************************** Boot Loader **********************************************/ 
#include "../kernel/config.h"

//generate 16-bit code
__asm__(".code16gcc\n");
//jump boot code entry
__asm__("jmpl $0x0000, $main\n");



void main()
{
	//set Extra segment to code segment 
	__asm__ __volatile__ ("movw %0,%%es"::"a"(CODESEG));
	__asm__ __volatile__ ("movw $0x0000,%bp");
	
	//reset floppy drive
	__asm__ __volatile__ ("int $0x13"::"a"(0x0000),"d"(0x0000));
	
	//read kernel code and load into extra segment
	__asm__ __volatile__ ("int $0x13"::"a"(0x0200|KERNELSIZE),"b"(0x0000),"c"(0x0000|KERNELSTART),"d"(0x0000|0x0000));
	

	//set segment register
	__asm__ __volatile__ ("movw %0,%%es"::"a"(EXTRASEG));
	__asm__ __volatile__ ("movw %0,%%ds"::"a"(CODESEG));
	__asm__ __volatile__ ("movw %0,%%ss"::"a"(STACKSEG));
	__asm__ __volatile__ ("movw %0,%%sp"::"i"(STACKPTR));
	
	//give control to kernel
	__asm__("jmpl $0x1000,$0x0000\n"::"i"(CODESEG));
}

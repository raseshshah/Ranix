/****************************** Boot Loader **********************************************/ 



/********************************** MEMORY MAP *********************************************
		   
	0xfffff -----------------
		:      BIOS	:
	0xc0000	-----------------		
		:		:
		:		:
		:		:
	0x3ffff ----------------- <--SP
		:	SS	:
        0x30000 ----------------- 
		:   ES(Buffer)	:
        0x20000	----------------- 		
		:     CS DS	:
	0x10000	----------------- 		
		:     INTMAP	: <--0x7c000 BOOTLOADER
	0x00000	-----------------
 		
********************************************************************************************/

//generate 16-bit code
__asm__(".code16\n");
//jump boot code entry
__asm__("jmpl $0x0000, $main\n");

void printString(const char* pStr) {
     while(*pStr) {
          __asm__ __volatile__ (
               "int $0x10" : : "a"(0x0e00 | *pStr), "b"(0x0007) 
          );
          ++pStr;
     }
}

void loadRanix()
{
	//reset floppy drive
	__asm__ __volatile__ ("reset:");
	__asm__ __volatile__ ("movb $0x00,%ah"); //reset floppy disk function
	__asm__ __volatile__ ("movb $0x00,%dl"); //drive 0 is floppy drive
	__asm__ __volatile__ ("int $0x13");	  //call BIOS
	__asm__ __volatile__ ("jc reset");	  //If Carry Flag (CF) is set, there was an error. Try resetting again


	//set segment register
	__asm__ __volatile__ ("movw $0x1000,%ax");
	__asm__ __volatile__ ("movw %ax,%es");
        __asm__ __volatile__ ("xorw %bx,%bx");

	//read floppy drive
	__asm__ __volatile__ ("read:");
	__asm__ __volatile__ ("movb $0x02,%ah"); //Reading Sectors
	__asm__ __volatile__ ("movb $0x01,%al"); //Number of sectors to read
	__asm__ __volatile__ ("movb $0x00,%ch"); //Low eight bits of cylinder number
	__asm__ __volatile__ ("movb $0x02,%cl"); //Sector Number (Bits 0-5). Bits 6-7 are for hard disks only
	__asm__ __volatile__ ("movb $0x00,%dh"); //Head Number
	__asm__ __volatile__ ("movb $0x00,%dl"); //Drive Number 		
	__asm__ __volatile__ ("int $0x13");	//call floppy handler
	__asm__ __volatile__ ("jc read");	//redo read if error occured


	//set segment register for kernel
	__asm__ __volatile__ ("movw $0x1000,%ax");
	__asm__ __volatile__ ("movw %ax,%ds");

	__asm__ __volatile__ ("movw $0x2000,%ax");
	__asm__ __volatile__ ("movw %ax,%es");

	__asm__ __volatile__ ("movw $0x3000,%ax");
	__asm__ __volatile__ ("movw %ax,%ss");
	
	__asm__ __volatile__ ("movw $0xfffa,%sp");

	//give control to kernel
	__asm__ __volatile__("jmp $0x1000,$0x0000");

}

void main() 
{
    printString("Loading Ran!x Kernel");
    loadRanix();			 
} 



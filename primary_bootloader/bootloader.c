/*generate 16-bit code*/
__asm__(".code16\n");
/*jump boot code entry*/
__asm__("jmpl $0x0000, $main\n");

#define KERNEL_ 0x1000
 
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
	__asm__ __volatile__ ("movb $0x02,%ah");
	__asm__ __volatile__ ("movb $0x01,%al");
	__asm__ __volatile__ ("movb $0x00,%ch");
	__asm__ __volatile__ ("movb $0x02,%cl");
	__asm__ __volatile__ ("movb $0x00,%dh");
	__asm__ __volatile__ ("movb $0x00,%dl");		
	__asm__ __volatile__ ("int $0x13");	
	__asm__ __volatile__ ("jc read");


	//set segment register for kernel
	__asm__ __volatile__ ("movw $0x1000,%ax");
	__asm__ __volatile__ ("movw %ax,%ds");
	__asm__ __volatile__ ("movw %ax,%es");
	__asm__ __volatile__ ("movw %ax,%ss");
	__asm__ __volatile__ ("movw %ax,%gs");
	__asm__ __volatile__ ("movw %ax,%fs");
	__asm__ __volatile__ ("movw $0xfffa,%sp");

	//give control to kernel
	__asm__ __volatile__("jmp $0x1000,$0x0000");

	
}
void print512byte()
{
	__asm__  __volatile__ ("movw $0x0000,%bp");	
	__asm__  __volatile__ ("movw $0x0200,%dx");
	__asm__ __volatile__ ("loop:");
	__asm__  __volatile__ ("xorw %ax,%ax");
	__asm__  __volatile__ ("movw %es:0(%bp),%ax");
	__asm__  __volatile__ ("movb $0x0e,%ah");
	__asm__ __volatile__ ("int $0x10" : : "b"(0x0007) );
	__asm__ __volatile__ ("decw %dx");	
	__asm__  __volatile__ ("incw %bp");
	__asm__ __volatile__ ("cmpw $0x0000,%dx" );
	__asm__ __volatile__ ("jne loop");

}
void main() 
{
    printString("Loading Ran!x");
    loadRanix();			 
} 



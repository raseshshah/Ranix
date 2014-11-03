/*generate 16-bit code*/
__asm__(".code16\n");
__asm__("jmpl $0x1000,$main");
void printString(const char *ptrs) 
{
	while(*ptrs)
{
          __asm__ __volatile__ (
               "int $0x10" : : "a"(0x0e00 | *ptrs), "b"(0x0007) 
          );
	ptrs++;
}
}
void main() 
{
	printString("\n\rwelcome Ran!x Kernel");
	__asm__ __volatile__ ("hlt");
}


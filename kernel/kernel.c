/*generate 16-bit code*/
__asm__(".code16\n");
__asm__("jmpl $0x1000,$main\n");

void printString() 
{
	char *pStr="Welcome Ran!x\0";
          __asm__ __volatile__ (
               "int $0x10" : : "a"(0x0e00 | *pStr), "b"(0x0007) 
          );
          ++pStr;
     }
void main() 
{
	printString();
	__asm__ __volatile__ ("hlt");
}


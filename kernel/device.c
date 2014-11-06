/******************************* DEVICE MANAGEMENT **************************************************/

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

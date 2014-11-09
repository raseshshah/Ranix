/******************************* DEVICE MANAGEMENT *******************************************************

****************************************** print character ***********************************************/
/*
	func:	print character on monitor
	in : 	c- character to print
	out:	-
*/
void cprint(short c)
{
	/*INT 0x10 - VIDEO TELETYPE OUTPUT
      	  AH = 0x0E
	  AL = Character to write*/
	//print character	
        __asm__ __volatile__ ("int $0x10" : : "a"(0x0e00 | c), "b"(0x0007) );
}
/****************************************** display string *********************************************
	func:	print string to monitor
	in : 	string 
	out:	-
*/
void sprint(char* pstr) 
{
     while(*pstr) 
     {
	 cprint(*pstr);	
          pstr++;
     }
}

/****************************************** print buffer ***********************************************/
/*
	func:	print buffer on monitor
	in : 	bufp- pointer to base of the buffer (ES:bufp)
	        size- number of byte to read
	out:	-
*/
void bprint(char *bp,short size)
{
	char c;	
	while(size)
	{
	    __asm__ __volatile__("movb %%es:%1,%0\n":"=a"(c):"m"(bp));
	    cprint(c);	
	    __asm__ __volatile__("incw %0"::"m"(bp));
	    size--;
	}
}
/****************************************** print File ***********************************************/
/*
*/
void fprint()
{
	
}

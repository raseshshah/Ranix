/******************************* FILE SYSTEM MANAGEMENT **************************************************


************************** File Descriptor Structure ****************************************************

	-----------------
	:E:C:B:D : : : : :
	:---------------:<--control bits E-file exist/not C-character file/not B-buffer/not D-dirty/not
	: : : : : : : : :
	:---------------:
	:    626byte	:<-size of the file
	:---------------:
	:    0xffff	:<--buffer pointer if file is buffered 
	:---------------:
	:    kernel.c	:<--name of file
	:---------------: 


	FILE_DESC_SIZE --> 32byte

************************** Root Descriptor Structure ********************************************************
                                    
	------------------------------------------	
	:	: 	:       :	:	 :	
	: desc0	: desc1 : desc2 :......	: desc255:
	:	:   	:       :	:	 :
	------------------------------------------
	0	31	63	95		 8191  	


	ROOT_DESC_SIZE --> FILE_DESC * FILES = 32*256 = 8192byte (16 block) 

*************************** Disk Memory Layout *****************************************************************

  					
	---------------------------------------------------------------------------------
	:	: 		:          :		:		:	:	:
	:  MBR	:  ROOT_DESC 	:   file0  :	file1	:	file2	:.......:file255:
	:	:   		:          :		:		:	:	:
	---------------------------------------------------------------------------------
	0	1		17	    	

	FLOPPY_SIZE -->  MBR + ROOT_DESC + FILEMAXBLK * FILES + PAD = 1 + 16 + 2816 (11*256) + 47 = 2880 BLOCKS
 
***************************** Buffer Memory Layout ****************************************************************

0xffff	-----------------
	:   File3 buf   :
	:---------------:<-- ROOT_DESC[2].bufp 
	:		:
	:---------------:
	:    		:
0x2002	:---------------:
	:1:1:1:1:1:1:1:1: <--FREEBUF 0-Allocated 1-Free
	:0:1:1:1:1:1:1:1:
0x2000	:---------------:
	:   Root_DESC	:
0x0000	:---------------: 


Extra Segment work as Buffer 64k (128 block)

MAX FILE BUFFER = ( ESBLKS - ROOT_DESCSIZE)/ (MAXFILEBLK) = ( 128 - 16)/ 11 ~ 10 FILES

****************************** File System Parameters & Descriptor Structure *******************************************/

//Floppy disk parameters
#define BLKSIZE 512
#define TRACK 18
#define SECTOR 80
#define HEAD 2
#define TOTALBLK 2880

//File System Parameter
#define FILES 256
#define FILENAMESIZE 26
#define BUFSIZE 128

struct fdesc
{
	short control;
	short *bufp;
	char name[FILENAMESIZE];
};

struct bdesc
{
	short freeb;
	struct fdesc rdesc[FILES];
};

/******************************************* intialize buffer management ****************************************************/

void binit()
{
	
}

/******************************************* allocate buffer ***************************************************************/

short * balloc(short size)
{
	short *blk=0x0000;

	return blk;
}

/******************************************* deallocate buffer ***************************************************************/

void bfree(short *buf)
{
	
}

/****************************************** disk read *********************************************************************/
/*
	func:	read sector from disk and store into buffer 
	in : 	blkno- block number from which reading start 
 	   	bufp- pointer to base of the buffer (ES:bufp)
	        size- number of sector to read
	out:	number of sector read successfully
*/
short dread(short bno,char *bp)
{
	short status=0,track,sector,head;
	
	//BLOCK <-> (SECTOR,TRACK,HEAD) conversion 
	sector=1+(bno%SECTOR);
	head =(bno/SECTOR)%HEAD;
	track=bno/(SECTOR*HEAD);

	/*BIOS Interrupt (INT) 0x13 Function 0x02 - Reading Sectors

	INT 0x13/AH=0x02 - DISK : READ SECTOR(S) INTO MEMORY
	AL = Number of sectors to read
	CH = Low eight bits of cylinder/track number
	CL = Sector Number (Bits 0-5). Bits 6-7 are for hard disks only
	DH = Head Number
	DL = Drive Number (Bit 7 set for hard disks)
	ES:BX = Buffer to read sectors to (ES:bufp)

	Returns:
	AH = Status Code
	AL = Number of sectors read
	CF = set if failure, cleared is successfull*/	
	
	//reset floppy drive
	__asm__ __volatile__ ("int $0x13"::"a"(0x0000),"d"(0x0000));
	//read sectors
	__asm__ __volatile__ ("int $0x13":"=a"(status):"a"(0x0201),"b"(bp),"c"((track<<8)|sector),"d"((head<<8)|0x0000));
	
	return status & 0x00ff;	
}

short dwrite(short bno,short *bp)
{
	short status=0;
	return status;	
}
/****************************************** open file *****************************************************************************/

void fopen()
{
}

void fclose()
{
	
}

void fread()
{
}

void fwrite()
{
	
}



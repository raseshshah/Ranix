/******************************* FILE SYSTEM MANAGEMENT **************************************************


/************************** File Descriptor Structure ****************************************************

	-----------------
	:E:B:D: : : : : :
	:---------------:<--control bits E-file exist/not B-buffer/not D-dirty/not
	: : : : : : : : :
	:---------------:
	:    626byte	:<-size of the file
	:---------------:
	:    0xffff	:<--buffer pointer if file is buffered 
	:---------------:
	:    kernel.c	:<--name of file
	:---------------: 


	FILE_DESC_SIZE --> 32byte

/************************** Root Descriptor Structure ********************************************************
                                    
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

****************************** File System Functions *************************************************************/


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

typedef struct file_desc
{
	short control;
	short size;
	short *bufp;
	char name[FILENAMESIZE];
};

typedef struct buf_desc
{
	short freebuf;
	file_desc root_desc[FILES];
};

short * bufalloc(short size)
{
	short *blk=0x0000;
	while()
	{	
		
	}
	return blk;
}

void buffree(short *buf)
{
	
}

short dread(short diskblkno,short *buf)
{
	short status=0;
	return status;	
}

short dwrite(short diskblkno,short *buf)
{
	return status;	
}

void finit()
{
}

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

void fprint()
{
	
}


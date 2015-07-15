/*****************************************************************************
 *   type.h:  Type definition Header file for NXP LPC230x Family 
 *   Microprocessors
 *
 *   Copyright(C) 2006, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2006.09.01  ver 1.00    Prelimnary version, first Release
******************************************************************************/
#ifndef __TYPE_H__
#define __TYPE_H__

#ifndef NULL
#define NULL    ((void *)0)
#endif

#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
//typedef unsigned int   BOOL;

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned long  uint32;

/*CTOS Define*/

#define CHAR	char
#define UCHAR	unsigned char
//#define BYTE	unsigned char
#define STR		unsigned char	
#define SHORT	short
#define USHORT	unsigned short
//#define WORD	unsigned short
#define INT		int
#define UINT	unsigned int
//#define DWORD	unsigned int
#define BOOL	unsigned char
#define LONG	long
#define ULONG	unsigned long
typedef unsigned char CL_STATUS;


#ifndef NULL
#define NULL	0
#endif

#define IN
#define OUT
#define INOUT

#define IN_RAM
#define CODE_ROM
#define EX_RAM


//#if READER_MANUFACTURERS==NE_CASTLES
/*No support*/
#define __packed
//#endif

#endif


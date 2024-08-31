#ifndef CRC32_H
#define CRC32_H

#ifndef DWORD
typedef unsigned long DWORD;
typedef unsigned char BYTE;
#endif


#include "stdio.h"
static char d_last[128] = "empty";
#define D_CHECKPOINT {sprintf(d_last,"%s:%d",__FILE__,__LINE__);}

//===================================================================================================


class cCRC
{
public:
	void generate_crc32_table();
	__forceinline DWORD crc32(const char* s)
	{
		extern DWORD* crctable;
		//gCRC.generate_crc32_table();

		if (!crctable) { generate_crc32_table(); }

		register DWORD dwCrc32 = 0xFFFFFFFF;
		while (*s) { dwCrc32 = ((dwCrc32) >> 8) ^ crctable[*s ^ ((dwCrc32) & 0xFF)]; s++; }
		return ~dwCrc32;
	}
};


extern cCRC gCRC;

#endif
#ifndef _l_lhkpubdrv_h_
#define _l_lhkpubdrv_h_

#include "winlite.h"
#include <WinIoCtl.h>

/*FILE_DEVICE_kLHK I/O*/
#define FILE_DEVICE_kLHK 64963
#define IOCTL_SET_PROC CTL_CODE(FILE_DEVICE_kLHK, 2050, METHOD_BUFFERED, FILE_READ_DATA|FILE_WRITE_DATA)
#define IOCTL_UNSET_PROC CTL_CODE(FILE_DEVICE_kLHK, 2051, METHOD_BUFFERED, FILE_READ_DATA|FILE_WRITE_DATA)

#define IOCTL_READ_DWORD CTL_CODE(FILE_DEVICE_kLHK, 2060, METHOD_BUFFERED, FILE_READ_DATA|FILE_WRITE_DATA)
#define IOCTL_READ_QWORD CTL_CODE(FILE_DEVICE_kLHK, 2061, METHOD_BUFFERED, FILE_READ_DATA|FILE_WRITE_DATA)

#define IOCTL_WRITE_DWORD CTL_CODE(FILE_DEVICE_kLHK, 2070, METHOD_BUFFERED, FILE_READ_DATA|FILE_WRITE_DATA)
#define IOCTL_WRITE_QWORD CTL_CODE(FILE_DEVICE_kLHK, 2071, METHOD_BUFFERED, FILE_READ_DATA|FILE_WRITE_DATA)

#define IOCTL_SIGSCAN CTL_CODE(FILE_DEVICE_kLHK, 2080, METHOD_BUFFERED, FILE_READ_DATA|FILE_WRITE_DATA)
#define IOCTL_POPIMAGEDATA CTL_CODE(FILE_DEVICE_kLHK, 2081, METHOD_BUFFERED, FILE_READ_DATA|FILE_WRITE_DATA)

#define DrvMaxSigLength 256
typedef struct {
	DWORD dwStartAddress;
	DWORD dwMaxScanLength;
	UCHAR bSignature[DrvMaxSigLength];
	DWORD dwSignatureLength;
} DrvSigScanData;

typedef struct  _IMAGE_INFO {
	union {
		ULONG  Properties;
		struct {
			ULONG ImageAddressingMode  : 8; //code addressing mode
			ULONG SystemModeImage      : 1; //system mode image
			ULONG ImageMappedToAllPids : 1; //mapped in all processes
			ULONG Reserved             : 22;
		};
	};
	PVOID  ImageBase;
	ULONG  ImageSelector;
	ULONG  ImageSize;
	ULONG  ImageSectionNumber;
} IMAGE_INFO, *PIMAGE_INFO; //taken from ntifs.h (also ntddk.h)

typedef struct {
	LIST_ENTRY ListEntry;
	char FullImageName[MAX_PATH];
	HANDLE ProcessId;
	IMAGE_INFO ImageInfo;
} DrvImageList;
/*FILE_DEVICE_kLHK I/O*/

void l_lhkpubdrv_register(lua_State *l);
void l_lhkpubdrv_globals(lua_State *l);
void l_lhkpubdrv_unregister(lua_State *l);

LUA_FUNC(DrvOpen);
LUA_FUNC(DrvClose);

LUA_FUNC(DrvSetProc);
LUA_FUNC(DrvUnsetProc);

LUA_FUNC(DrvReadByte);
LUA_FUNC(DrvReadShort);
LUA_FUNC(DrvReadInt);
LUA_FUNC(DrvReadFloat);

LUA_FUNC(DrvWriteByte);
LUA_FUNC(DrvWriteShort);
LUA_FUNC(DrvWriteInt);
LUA_FUNC(DrvWriteFloat);

LUA_FUNC(DrvSigScan);
LUA_FUNC(DrvPopImageData);

#endif

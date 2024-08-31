#include "kitapi.h"

ULONG rand_lfsr = 0xC7A0E33F;
unsigned int KitRand(ULONG new_lfsr)
{
	if (new_lfsr != 0) rand_lfsr = new_lfsr;
	rand_lfsr = (rand_lfsr >> 1) ^ (unsigned int)(0 - (rand_lfsr & 1) & 0xD0070A01);
	return rand_lfsr;
}

NTSTATUS KitAuthorizeUser(PUCHAR key)
{
	DbgPrint("[HackKit] Authorizing User...\n");

	PULONG buf = (PULONG)&key[0x00]; //add offset if u want
	ULONG maxBytes = KitAuthMaxB;
	ULONG maxUints = maxBytes / 4;
	ULONG maxPairs = maxUints / 2;

	ULONG i = 0;
	for (i = 0; i < maxUints; i+=2)
	{
		DbgPrint("\tChecking Keypair: 0x%08x : 0x%08x ", buf[i], buf[i+1]);
		ULONG y = (KitAuthA*(buf[i]*buf[i])) + (KitAuthB*buf[i]) + KitAuthC;
		if (y != buf[i+1]) { DbgPrint("[FAIL]\n"); return STATUS_UNSUCCESSFUL; }
		DbgPrint("[OK]\n");
	}
	
	DbgPrint("\tSuccessfully authenticated user\n");
	return STATUS_SUCCESS;
}

void KitGenerateKey(PUCHAR out)
{
	DbgPrint("[HackKit] Genertating Auth Key...\n");
	/*DbgPrint("\tWaiting for IOCTL_KITBRKCONT...\n");
	KitBreakAndWaitForCont();*/

	UCHAR buffer[256];
	memset(buffer, 0, 256);

	PULONG buf = (PULONG)&buffer[0x00]; //add offset if u want

	ULONG maxBytes = KitAuthMaxB;
	ULONG maxUints = maxBytes / 4;
	ULONG maxPairs = maxUints / 2;

	KitRand(9181561);

	ULONG i = 0; ULONG keylfsr = 0;
	for (i = 0; i < maxPairs; i++)
	{
		buf[i*2] = (KitRand(0)&0x9FF);
	}
	for (i = 0; i < maxUints; i+=2)
	{
		ULONG y = (KitAuthA*(buf[i]*buf[i])) + (KitAuthB*buf[i]) + KitAuthC;
		buf[i+1] = y;
		DbgPrint("\tGenerated Keypair: 0x%08x : 0x%08x\n", buf[i], buf[i+1]);
	}

	if (out != 0) RtlCopyMemory(out, buffer, 256);
}

PVOID KitSSDTCopy = 0;
void KitSetup()
{
	KitApiWaitingForCont = 0;
	KitSSDTCopy = 0;
	DbgPrint("[HackKit] ***Setup***\n");

	KitSSDTCopy = KitCreateSSDTCopy();

	PsSetLoadImageNotifyRoutine(KitImageLoadCallback);
	PsSetCreateProcessNotifyRoutineEx(KitCreateProcessCallbackEx, FALSE);
	PsSetCreateThreadNotifyRoutine(KitCreateThreadCallback);

	KitGenerateKey(0);
}

void KitDestroy()
{
	DbgPrint("[HackKit] ***Destory***\n");

	PsRemoveCreateThreadNotifyRoutine(KitCreateThreadCallback);
	PsSetCreateProcessNotifyRoutineEx(KitCreateProcessCallbackEx, TRUE);
	PsRemoveLoadImageNotifyRoutine(KitImageLoadCallback);

	KitDeleteSSDTCopy(KitSSDTCopy);
}

ULONG KitApiWaitingForCont = 0;
void KitBreakAndWaitForCont()
{
	KitApiWaitingForCont = 1;
	while (KitApiWaitingForCont > 0) KitRand(0);
}

void KitImageLoadCallback(IN PUNICODE_STRING FullImageName,
	IN HANDLE ProcessId, IN PIMAGE_INFO ImageInfo)
{
	
}

void KitCreateProcessCallbackEx(IN PEPROCESS Process, IN HANDLE ProcessId,
	IN PPS_CREATE_NOTIFY_INFO CreateInfo)
{
	/*DbgPrint("[HackKit] CreateProcess called...\n");
	DbgPrint("\tEPROCESS: 0x%x\n", (ULONG)Process);
	DbgPrint("\tProcessId: 0x%x\n", (ULONG)ProcessId);
	if (CreateInfo != 0)
	{
		DbgPrint("\tCreateInfo:\n");
		DbgPrint("\t\tParent ProcessId: 0x%x\n", (ULONG)CreateInfo->ParentProcessId);
		if (CreateInfo->ImageFileName != 0)
			DbgPrint("\t\tImage File Name: %ws\n", CreateInfo->ImageFileName->Buffer);
		if (CreateInfo->CommandLine != 0)
			DbgPrint("\t\tCommand Line: %ws\n", CreateInfo->CommandLine->Buffer);
	}*/
}

void KitCreateThreadCallback(IN HANDLE ProcessId, IN HANDLE ThreadId,
	IN BOOLEAN Create)
{
	/*DbgPrint("[HackKit] CreateThread called...\n");
	DbgPrint("\tProcessId: 0x%x\n", (ULONG)ProcessId);
	DbgPrint("\tThreadId: 0x%x\n", (ULONG)ThreadId);
	DbgPrint("\tCreate: %d\n", Create);*/
}

PVOID KitCreateSSDTCopy()
{
	PVOID ssdtcpy = ExAllocatePool(NonPagedPool,
		KeServiceDescriptorTable.NumberOfServices * 4);
	RtlCopyMemory(ssdtcpy, KeServiceDescriptorTable.ServiceTableBase,
		KeServiceDescriptorTable.NumberOfServices * 4);
	return ssdtcpy;
}

void KitDeleteSSDTCopy(PVOID cpy)
{
	ExFreePool(cpy);
}

PUINT32 KitEnableSSDTCopy(PVOID cpy)
{
	PUINT32 old = KeServiceDescriptorTable.ServiceTableBase;
	KeServiceDescriptorTable.ServiceTableBase = (PUINT32)cpy;
	return old;
}

void KitDisableSSDTCopy(PVOID cpy, PUINT32 old)
{
	KeServiceDescriptorTable.ServiceTableBase = old;
}

UINT32 KitReplaceDriverAddress(UINT32 dwIndex, UINT32 dwNewFunction) 
{ 
	UINT32* dwTIB = NULL; 

	__asm 
	{ 
		mov eax, fs:[18h] 
		add eax, dwIndex 
		mov dwTIB, eax 
	} 

	UINT32 retVal = *dwTIB; 
	*dwTIB = dwNewFunction; 

	return retVal; 
}

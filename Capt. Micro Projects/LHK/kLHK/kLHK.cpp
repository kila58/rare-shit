#include "kLHK.h"

void WriteLog(char *fmt, ...)
{
	va_list arglist;
	va_start(arglist, fmt);

	char *buffer = (char*)ExAllocatePool(NonPagedPool, 4096);
	memset(buffer, 0, 4096);
	RtlStringCbVPrintfA(buffer, 4096, fmt, arglist);
	ULONG buflen = 0;
	RtlStringCbLengthA(buffer, 4096, (size_t*)&buflen);

	DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, buffer);

	if (buflen > 0)
	{
		/*setup log file*/
		UNICODE_STRING logName;
		OBJECT_ATTRIBUTES objAttribs;
		NTSTATUS status;
		HANDLE hFile;
		IO_STATUS_BLOCK ioStatus;
		RtlInitUnicodeString(&logName, L"\\DosDevices\\C:\\kLHK.log");
		InitializeObjectAttributes(&objAttribs, &logName,
			OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
			NULL, NULL);
		if(KeGetCurrentIrql() != PASSIVE_LEVEL) goto _exitlogwrite;
		status = ZwCreateFile(&hFile, FILE_APPEND_DATA,
			&objAttribs, &ioStatus, NULL, FILE_ATTRIBUTE_NORMAL, 0,
			FILE_OPEN_IF, FILE_NON_DIRECTORY_FILE | FILE_RANDOM_ACCESS |
			FILE_NO_INTERMEDIATE_BUFFERING | FILE_SYNCHRONOUS_IO_NONALERT,
			NULL, 0);
		if (!NT_SUCCESS(status)) {
			DbgPrint("Failed to create log file\n");
			goto _exitlogwrite;
		}
		/*write log file*/
		ZwWriteFile(hFile, 0, 0, 0,
			&ioStatus, buffer, buflen, 0, 0);
		/*close log file*/
		ZwClose(hFile);
	}

_exitlogwrite:;
	ExFreePool(buffer);
	va_end(arglist);
}

HLPPROCTOKEN kLHK_systemtoken;
char kLHK_currprocname[MAX_PATH];
PEPROCESS kLHK_currproc;
DrvImageList *kLHK_imagehead;

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING  RegistryPath)
{
	UNICODE_STRING DeviceName,Win32Device;
	PDEVICE_OBJECT DeviceObject = NULL;
	NTSTATUS status;
	unsigned i;

	DbgPrint("************************************************\n");
	DbgPrint("* b0mbTECH.org Research & Development **********\n");
	DbgPrint("* [ kLHK ] lua hack kit driver plugin **********\n");
	DbgPrint("************************************************\n");

	RtlInitUnicodeString(&DeviceName,L"\\Device\\kLHK");
	RtlInitUnicodeString(&Win32Device,L"\\DosDevices\\kLHK");

	for (i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; i++)
		DriverObject->MajorFunction[i] = kLHKDefaultHandler;

	DriverObject->MajorFunction[IRP_MJ_CREATE] = kLHKCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = kLHKClose;
	DriverObject->MajorFunction[IRP_MJ_READ] = kLHKRead;
	DriverObject->MajorFunction[IRP_MJ_WRITE] = kLHKWrite;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = kLHKIoctl;

	DriverObject->DriverUnload = kLHKUnload;
	status = IoCreateDevice(DriverObject,
		0,
		&DeviceName,
		FILE_DEVICE_kLHK,
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

	kLHK_systemtoken = HlpGetCurrProcToken();
	DbgPrint("Got current process token. 0x%08X%08X\n", kLHK_systemtoken.hi, kLHK_systemtoken.lo);

	RtlZeroMemory(kLHK_currprocname, MAX_PATH);
	kLHK_currproc = 0;

	kLHK_imagehead = (DrvImageList*)ExAllocatePool(NonPagedPool, sizeof(DrvImageList));
	RtlZeroMemory(kLHK_imagehead, sizeof(DrvImageList));
	strcpy(kLHK_imagehead->FullImageName, "_image_list_head_");
	InitializeListHead(&kLHK_imagehead->ListEntry);

	NTSTATUS cbsetret = STATUS_UNSUCCESSFUL;

	DbgPrint("Setting load image notify routine\n");
	cbsetret = STATUS_UNSUCCESSFUL;
	cbsetret = PsSetLoadImageNotifyRoutine(kLHKImageLoadCallback);
	DbgPrint("\tNTSTATUS: 0x%08x (", (ULONG)cbsetret);
	switch (cbsetret)
	{
		case STATUS_SUCCESS: DbgPrint("STATUS_SUCCESS)\n"); break;
		case STATUS_INVALID_PARAMETER: DbgPrint("STATUS_INVALID_PARAMETER)\n"); break;
		case STATUS_ACCESS_DENIED: DbgPrint("STATUS_ACCESS_DENIED)\n"); break;
		case STATUS_UNSUCCESSFUL: DbgPrint("STATUS_UNSUCCESSFUL)\n"); break;
		default: DbgPrint("???)\n"); break;
	}
	if (!NT_SUCCESS(cbsetret)) { DbgPrint("* Failed to set routine.\n"); }

	DbgPrint("Setting create process notify routine\n");
	cbsetret = STATUS_UNSUCCESSFUL;
	cbsetret = PsSetCreateProcessNotifyRoutineEx(kLHKCreateProcessCallbackEx, FALSE);
	DbgPrint("\tNTSTATUS: 0x%08x (", (ULONG)cbsetret);
	switch (cbsetret)
	{
		case STATUS_SUCCESS: DbgPrint("STATUS_SUCCESS)\n"); break;
		case STATUS_INVALID_PARAMETER: DbgPrint("STATUS_INVALID_PARAMETER)\n"); break;
		case STATUS_ACCESS_DENIED: DbgPrint("STATUS_ACCESS_DENIED)\n"); break;
		case STATUS_UNSUCCESSFUL: DbgPrint("STATUS_UNSUCCESSFUL)\n"); break;
		default: DbgPrint("???)\n"); break;
	}
	if (!NT_SUCCESS(cbsetret)) { DbgPrint("* Failed to set routine.\n"); }


	DbgPrint("************************************************\n");
	DbgPrint("* kLHK INITIALIZED *****************************\n");
	DbgPrint("************************************************\n");

	return STATUS_SUCCESS;
}

void kLHKUnload(IN PDRIVER_OBJECT DriverObject)
{
	DbgPrint("************************************************\n");
	DbgPrint("* UNLOADING KLHK *******************************\n");
	DbgPrint("************************************************\n");

	PsSetCreateProcessNotifyRoutineEx(kLHKCreateProcessCallbackEx, TRUE);
	PsRemoveLoadImageNotifyRoutine(kLHKImageLoadCallback);

	while (!IsListEmpty(&kLHK_imagehead->ListEntry))
	{
		LIST_ENTRY *entry = RemoveHeadList(&kLHK_imagehead->ListEntry);
		DrvImageList *data = CONTAINING_RECORD(entry, DrvImageList, ListEntry);
		ExFreePool(data);
	}
	ExFreePool(kLHK_imagehead);

	UNICODE_STRING Win32Device;
	RtlInitUnicodeString(&Win32Device,L"\\DosDevices\\kLHK");
	IoDeleteSymbolicLink(&Win32Device);															 
	IoDeleteDevice(DriverObject->DeviceObject);

	DbgPrint("************************************************\n");
	DbgPrint("* GOODBYE **************************************\n");
	DbgPrint("************************************************\n");
}

NTSTATUS kLHKDefaultHandler(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	Irp->IoStatus.Status = STATUS_NOT_SUPPORTED;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return Irp->IoStatus.Status;
}

NTSTATUS kLHKCreate(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	DbgPrint("kLHKCreate called.\n");

	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS kLHKClose(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	DbgPrint("kLHKClose called.\n");

	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS kLHKRead(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	DbgPrint("kLHKRead called.\n");

	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS kLHKWrite(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	DbgPrint("kLHKWrite called.\n");

	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

#define CtlCode2Real(ctlCode) (2048 + ((ctlCode-0xFCCBE003)/4))
NTSTATUS kLHKIoctl(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	DbgPrint("kLHKIoctl called.\n");

	PIO_STACK_LOCATION irpStack = 0;
	irpStack = IoGetCurrentIrpStackLocation(Irp);
	ULONG ctlCode = irpStack->Parameters.DeviceIoControl.IoControlCode;
	DbgPrint("\tIOCTL func #%d\n", CtlCode2Real(ctlCode));

	Irp->IoStatus.Status = STATUS_UNSUCCESSFUL;
	Irp->IoStatus.Information = 0;

	if (Irp->AssociatedIrp.SystemBuffer)
	{
		UCHAR *buffer = (UCHAR*)Irp->AssociatedIrp.SystemBuffer;
		ULONG buflen = irpStack->Parameters.DeviceIoControl.InputBufferLength;
		DWORD dwPrefix = 0; if (buflen >= 4) dwPrefix = *(DWORD*)buffer;
		LARGE_INTEGER temp; RtlZeroMemory(&temp, sizeof(LARGE_INTEGER));
		DrvSigScanData tempScanData; RtlZeroMemory(&tempScanData, sizeof(DrvSigScanData));
		ULONG success = FALSE;
		__try
		{
			switch (ctlCode)
			{
				case IOCTL_POPIMAGEDATA:
					DbgPrint("Recevied IOCTL_CHK4LUACB\n", kLHK_currprocname);
					if (IsListEmpty(&kLHK_imagehead->ListEntry))
					{
						RtlZeroMemory(buffer, sizeof(DrvImageList));
						*(ULONG*)buffer = 0xDEADBEEF;
						Irp->IoStatus.Information = 4;
					}
					else
					{
						LIST_ENTRY *entry = RemoveTailList(&kLHK_imagehead->ListEntry);
						DrvImageList *data = CONTAINING_RECORD(entry, DrvImageList, ListEntry);
						RtlCopyMemory(buffer, data, sizeof(DrvImageList));
						Irp->IoStatus.Information = sizeof(DrvImageList);
						ExFreePool(data);
					}
					break;
			}
			if (kLHK_currproc == 0)
			{
				switch (ctlCode)
				{
					case IOCTL_SET_PROC:
						RtlCopyMemory(kLHK_currprocname, buffer,
							(buflen >= MAX_PATH) ? MAX_PATH-1 : buflen);
						success = TRUE;
						DbgPrint("Recevied IOCTL_SET_PROC '%s'\n", kLHK_currprocname);
						RtlCopyMemory(buffer, &success, 4);
						Irp->IoStatus.Information = 4;
						break;
					default:
						DbgPrint("Recevied unknown IOCTL!\n");
						break;
				}
			}
			else
			{
				switch (ctlCode)
				{
					case IOCTL_UNSET_PROC:
						DbgPrint("Recevied IOCTL_UNSET_PROC\n");
						kLHK_currproc = 0;
						success = TRUE;
						Irp->IoStatus.Information = 4;
						break;
					case IOCTL_READ_DWORD:
						if (kLHK_currproc == 0) break;
						DbgPrint("Recevied IOCTL_READ_DWORD 0x%08X\n", dwPrefix);
						HlpReadMemory(kLHK_currproc, dwPrefix, &temp.u.LowPart, 4);
						RtlCopyMemory(buffer, &temp.u.LowPart, 4);
						success = TRUE;
						Irp->IoStatus.Information = 4;
						break;
					case IOCTL_READ_QWORD:
						if (kLHK_currproc == 0) break;
						DbgPrint("Recevied IOCTL_READ_DWORD 0x%08X\n", dwPrefix);
						HlpReadMemory(kLHK_currproc, dwPrefix, &temp, 8);
						RtlCopyMemory(buffer, &temp, 8);
						success = TRUE;
						Irp->IoStatus.Information = 8;
						break;
					case IOCTL_WRITE_DWORD:
						if (kLHK_currproc == 0) break;
						RtlCopyMemory(&temp.u.LowPart, buffer+4, 4);
						DbgPrint("Recevied IOCTL_WRITE_DWORD 0x%08X with 0x%08X\n", dwPrefix, temp.u.LowPart);
						HlpWriteMemory(kLHK_currproc, dwPrefix, &temp.u.LowPart, 4);
						success = TRUE;
						RtlCopyMemory(buffer, &success, 4);
						Irp->IoStatus.Information = 4;
						break;
					case IOCTL_WRITE_QWORD:
						if (kLHK_currproc == 0) break;
						RtlCopyMemory(&temp, buffer+4, 8);
						DbgPrint("Recevied IOCTL_WRITE_QWORD 0x%08X with 0x%08X%08X\n", dwPrefix, temp.u.HighPart, temp.u.LowPart);
						HlpWriteMemory(kLHK_currproc, dwPrefix, &temp, 8);
						success = TRUE;
						RtlCopyMemory(buffer, &success, 4);
						Irp->IoStatus.Information = 4;
						break;
					case IOCTL_SIGSCAN:
						if (kLHK_currproc == 0) break;
						RtlCopyMemory(&tempScanData, buffer+4, 8);
						DbgPrint("Recevied IOCTL_SIGSCAN\n");
						temp.u.LowPart = HlpScanMemory(kLHK_currproc, &tempScanData);
						RtlCopyMemory(buffer, &temp.u.LowPart, 4);
						Irp->IoStatus.Information = 4;
						success = TRUE;
						break;
					default:
						DbgPrint("Recevied unknown IOCTL!\n");
						break;
				}
			}
			
		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{
			success = FALSE;
		}
		if (success == TRUE) Irp->IoStatus.Status = STATUS_SUCCESS;
		else Irp->IoStatus.Status = STATUS_UNSUCCESSFUL;
	}

	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

//called when image loads but before execution
void kLHKImageLoadCallback(IN PUNICODE_STRING FullImageName,
	IN HANDLE ProcessId, IN PIMAGE_INFO ImageInfo)
{
	DbgPrint("Image loaded...\n");
	if (FullImageName != 0)
		DbgPrint("\tFull Image Name: '%ws'\n", FullImageName->Buffer);
	DbgPrint("\tProcessId: 0x%x\n", (ULONG)ProcessId);

	if (ImageInfo != 0)
	{
		DbgPrint("\tImageInfo:\n");
		DbgPrint("\t\tImage Base: 0x%x\n", (ULONG)ImageInfo->ImageBase);
		DbgPrint("\t\tImage Selector: 0x%x\n", (ULONG)ImageInfo->ImageSelector);
		DbgPrint("\t\tImage Size: 0x%x\n", (ULONG)ImageInfo->ImageSize);
		DbgPrint("\t\tImage Section Number: 0x%x\n", (ULONG)ImageInfo->ImageSectionNumber);
		DbgPrint("\t\tProperties:\n");
		DbgPrint("\t\t\tImage Addressing Mode: 0x%x\n", (ULONG)ImageInfo->ImageAddressingMode);
		DbgPrint("\t\t\tSystem Mode Image: 0x%x\n", (ULONG)ImageInfo->SystemModeImage);
		DbgPrint("\t\t\tImage Mapped To All Pids: 0x%x\n", (ULONG)ImageInfo->ImageMappedToAllPids);
		DbgPrint("\t\t\tReserved: 0x%x\n", (ULONG)ImageInfo->Reserved);
	}

	if (kLHK_currproc == 0) return;

	if (FullImageName != 0)
	{
		if (FullImageName->Buffer != 0)
		{
			if (wcslen(FullImageName->Buffer) > 4)
			{
				DrvImageList *newentry = (DrvImageList*)ExAllocatePool(NonPagedPool, sizeof(DrvImageList));
				RtlZeroMemory(newentry, sizeof(DrvImageList));

				ANSI_STRING ansisz;
				RtlUnicodeStringToAnsiString(&ansisz, FullImageName, TRUE);
				RtlCopyMemory(newentry->FullImageName, ansisz.Buffer,
					(ansisz.Length >= MAX_PATH) ? MAX_PATH-1 : ansisz.Length);
				RtlFreeAnsiString(&ansisz);

				InsertHeadList(&kLHK_imagehead->ListEntry, &newentry->ListEntry);

				DbgPrint("Added image to DrvImageList head. '%s'\n", ansisz);
			}
			else { return; }
		}
		else { return; }
	}
	else { return; }
}

//called when process is created or exits,
//runs in context of thread that created the process
void kLHKCreateProcessCallbackEx(IN PEPROCESS Process, IN HANDLE ProcessId,
	IN PPS_CREATE_NOTIFY_INFO CreateInfo)
{
	DbgPrint("CreateProcess called...\n");
	DbgPrint("\tProcess: 0x%x\n", (ULONG)Process);
	DbgPrint("\tProcessId: 0x%x\n", (ULONG)ProcessId);

	if (CreateInfo != 0)
	{
		DbgPrint("\tCreateInfo:\n");
		DbgPrint("\t\tParent Process Id: 0x%x\n", (ULONG)CreateInfo->ParentProcessId);
		if (CreateInfo->ImageFileName != 0)
			DbgPrint("\t\tImage File Name: '%ws'\n", CreateInfo->ImageFileName->Buffer);
		if (CreateInfo->CommandLine != 0)
			DbgPrint("\t\tCommand Line: '%ws'\n", CreateInfo->CommandLine->Buffer);
		DbgPrint("\t\tFlags: 0x%x\n", (ULONG)CreateInfo->Flags);
	}

	if (CreateInfo != 0)
	{
		if (CreateInfo->ImageFileName != 0)
		{
			if (CreateInfo->ImageFileName->Buffer != 0)
			{
				if (CreateInfo->ImageFileName->Length > 3)
				{
					if (wcsstr(CreateInfo->ImageFileName->Buffer, L"LHK.exe"))
					{
						HlpElevateProcess(Process, &kLHK_systemtoken);
						DbgPrint("Elevated LHK.exe to System\n", kLHK_currproc);
					}
					else
					{
						if (kLHK_currproc != 0) return;

						ANSI_STRING ansisz;
						RtlUnicodeStringToAnsiString(&ansisz, CreateInfo->ImageFileName, TRUE);
						if (strstr(ansisz.Buffer, kLHK_currprocname) != 0)
						{
							kLHK_currproc = Process;
							DbgPrint("Set current process: 0x%08X\n", kLHK_currproc);
						}
						RtlFreeAnsiString(&ansisz);
					}
				}
				else { return; }
			}
			else { return; }
		}
		else { return; }
	}
	else { return; }
}

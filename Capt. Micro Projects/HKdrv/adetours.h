/*******************************************************
* Michael87
* ring0 detours.c/h - version 2.1 - 32 bit version
* This file contains varius detouring / mem editing
* functions.
*
* Created for Game-Deception
*
* ADetours-Credits:
*   Matthew L (Azorbix)
*   Dom1n1k
*   LanceVorgin
*   P47R!CK
*
* ASizeOfCode-Credits:
*	rain
*	Ms-Rem http://cracklab.ru/f/index.php?action=vthread&forum=3&topic=9539
*
\******************************************************/

#ifndef _DETOURS_H
#define _DETOURS_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <excpt.h>
#include <ntddk.h>


#define ADETOUR_DEFINE(IsPagedMemory, FunctionName, ReturnType, ArgumentPrototype, Callconvention) \
	typedef ReturnType (Callconvention * FunctionName##_Func)ArgumentPrototype; \
	FunctionName##_Func Org_##FunctionName = NULL; \
	FunctionName##_Func Trmp_##FunctionName = NULL; \
    BOOLEAN FunctionName##_ispaged = IsPagedMemory;

#define ADETOUR_DEFINE_AND_INIT(IsPagedMemory, FunctionName, ReturnType, ArgumentPrototype, FunctionAddress, Callconvention) \
	typedef ReturnType (Callconvention * FunctionName##_Func)ArgumentPrototype; \
	FunctionName##_Func Org_##FunctionName = (FunctionName##_Func)FunctionAddress; \
	FunctionName##_Func Trmp_##FunctionName = NULL; \
	BOOLEAN FunctionName##_ispaged = IsPagedMemory;

#define ADETOUR_HOOK(FunctionName) \
	if(Org_##FunctionName != NULL) \
	  Trmp_##FunctionName = (FunctionName##_Func)ADetourKernelFunc((PVOID)Org_##FunctionName, (PVOID)My_##FunctionName,  FunctionName##_ispaged);  

#define ADETOUR_HOOK_LEN(FunctionName, OpcodeLength) \
	if(Org_##FunctionName != NULL) \
	Trmp_##FunctionName = (FunctionName##_Func)ADetourKernelFuncEx((PVOID)Org_##FunctionName, (PVOID)My_##FunctionName,  FunctionName##_ispaged, OpcodeLength);  

#define ADETOUR_UNHOOK(FunctionName, FreeTrampoline) \
	if(Org_##FunctionName != NULL && Trmp_##FunctionName != NULL) \
	ARetourKernelFunc((PVOID)Org_##FunctionName, (PVOID)Trmp_##FunctionName, FreeTrampoline, FunctionName##_ispaged);

#define ADETOUR_UNHOOK_LEN(FunctionName, OpcodeLength, FreeTrampoline) \
	if(Org_##FunctionName != NULL && Trmp_##FunctionName != NULL) \
	ARetourKernelFuncEx((PVOID)Org_##FunctionName, (PVOID)Trmp_##FunctionName, FreeTrampoline, FunctionName##_ispaged, OpcodeLength);


PVOID NTAPI ADetourKernelFunc(PVOID TargetFunction, CONST PVOID OwnFunction, BOOLEAN IsPagedMemory);
PVOID NTAPI ADetourKernelFuncEx(PVOID TargetFunction, CONST PVOID OwnFunction, BOOLEAN IsPagedMemory, LONG OpcodeLength);

VOID NTAPI ARetourKernelFunc(PVOID TargetFunction, PVOID Trampoline, BOOLEAN FreeTrampoline, BOOLEAN IsPagedMemory);
VOID NTAPI ARetourKernelFuncEx(PVOID TargetFunction, PVOID Trampoline, BOOLEAN FreeTrampoline, BOOLEAN IsPagedMemory, LONG OpcodeLength);

PUCHAR ALockPage(PVOID SysAddr, ULONG Length, PMDL* Mdl, BOOLEAN IsPagedMemory);
VOID AUnLockPage(PVOID SysAddr, PVOID LockAddr, ULONG Length, PMDL* Mdl, BOOLEAN IsPagedMemory);

ULONG ASizeOfCode(PVOID FunctionAddress);


#ifdef  __cplusplus
}
#endif

#endif
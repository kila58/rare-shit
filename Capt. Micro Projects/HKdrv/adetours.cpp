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
#include "adetours.h"

#ifdef  __cplusplus
extern "C" {
#endif

PVOID NTAPI ADetourKernelFuncInt(PUCHAR osrc, CONST PUCHAR dst, BOOLEAN paged, LONG len)
{
	PMDL Mdl = NULL;
	PUCHAR src = NULL;
	PUCHAR jmp = NULL;
	LONG lockedLen = 0;
	LONG i = 0;

	if(len < 5) {
		lockedLen = (LONG)PAGE_SIZE;
		src = ALockPage(osrc,(ULONG)PAGE_SIZE,&Mdl,paged);
		if(src == NULL) 
	      return NULL;
		len = 0;
		while(len < 5) 
			len += ASizeOfCode(src + len);
	}
	else {
	  lockedLen = len;
      src = ALockPage(osrc,len,&Mdl,paged);
	  if(src == NULL) 
	    return NULL;
	}

	// we're using the msdn example tag "Tag1", so this cannot be used for hook detection
	jmp = (PUCHAR)ExAllocatePoolWithTag(NonPagedPool,(len+5),'HkAd');
	if(jmp == NULL)
		return NULL;

	memcpy(jmp, src, len);	

	jmp += len;
	
	jmp[0] = 0xE9;
	*(PULONG)(jmp+1) = (ULONG)(osrc+len - jmp) - 5;

	((PUCHAR)src)[0] = 0xE9;
	*(PULONG)(src+1) = (ULONG)(dst - osrc) - 5;

	for( i=5; i < len; i++ ) 
	  src[i] = 0x90;

    AUnLockPage(osrc,src,lockedLen,&Mdl,paged);

	return (jmp-len);
}

PVOID NTAPI ADetourKernelFunc(PVOID TargetFunction, CONST PVOID OwnFunction, BOOLEAN IsPagedMemory)
{
  return ADetourKernelFuncInt((PUCHAR)TargetFunction, (PUCHAR)OwnFunction, IsPagedMemory, 0);
}

PVOID NTAPI ADetourKernelFuncEx(PVOID TargetFunction, CONST PVOID OwnFunction, BOOLEAN IsPagedMemory, LONG OpcodeLength)
{
  return ADetourKernelFuncInt((PUCHAR)TargetFunction, (PUCHAR)OwnFunction, IsPagedMemory, OpcodeLength);
}



VOID NTAPI ARetourKernelFuncInt(PUCHAR osrc, PUCHAR restore, BOOLEAN freeTrampoline, BOOLEAN paged, LONG len)
{
	PMDL Mdl;
	PUCHAR src = NULL;
	LONG lockedLen = 0;

	if(len < 5) {
		lockedLen = (LONG)PAGE_SIZE;
		src = ALockPage(osrc,(ULONG)PAGE_SIZE,&Mdl,paged);
		if(src == NULL) 
	      return;
		len = 0;
		while(len < 5) 
			len += ASizeOfCode(restore + len);
	}
	else {
	  lockedLen = len;
      src = ALockPage(osrc,len,&Mdl,paged);
	  if(src == NULL) 
	    return;
	}
	memcpy(src, restore, len);

    AUnLockPage(osrc,src,lockedLen,&Mdl,paged);

	if(!freeTrampoline) {
	  restore[0] = 0xE9;
	  *(PULONG)(restore+1) = (ULONG)(osrc - restore) - 5;
	}
	else {
		ExFreePoolWithTag(restore,'HkAd');
	}
}

VOID NTAPI ARetourKernelFunc(PVOID TargetFunction, PVOID Trampoline, BOOLEAN FreeTrampoline, BOOLEAN IsPagedMemory)
{
  ARetourKernelFuncInt((PUCHAR)TargetFunction, (PUCHAR)Trampoline, FreeTrampoline, IsPagedMemory, 0);
}

VOID NTAPI ARetourKernelFuncEx(PVOID TargetFunction, PVOID Trampoline, BOOLEAN FreeTrampoline, BOOLEAN IsPagedMemory, LONG OpcodeLength)
{
  ARetourKernelFuncInt((PUCHAR)TargetFunction, (PUCHAR)Trampoline, FreeTrampoline, IsPagedMemory, OpcodeLength);
}

PUCHAR ALockPage(PVOID SysAddr, ULONG Length, PMDL* Mdl, BOOLEAN IsPagedMemory) 
{

  PUCHAR Buffer = NULL;
  BOOLEAN Success = FALSE;

  do {
    
	if(IsPagedMemory) {  

	// IoAllocateMdl
	*Mdl = IoAllocateMdl((PVOID*)SysAddr, Length, FALSE, FALSE, NULL);
    if (*Mdl == NULL) {
      //DbgPrint("ALockPage: Error: IoAllocateMdl failed. \n");
      break;
    }

 	// MmProbeAndLockPages
    __try 
    {
      MmProbeAndLockPages(*Mdl, KernelMode, IoModifyAccess);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
	  //DbgPrint("ALockPage: Error: MmProbeAndLockPages failed. \n");
      break;
    }
	
    // MmGetSystemAddressForMdlSafe
    Buffer = (PUCHAR)MmGetSystemAddressForMdlSafe(*Mdl,HighPagePriority);
	if(Buffer == NULL) {
	  //DbgPrint("ALockPage: Error: MmGetSystemAddressForMdlSafe failed. \n");
      break;
	}
	//DbgPrint("using buffer 0x%p\n",Buffer);

	// MmProtectMdlSystemAddress
	if(MmProtectMdlSystemAddress(*Mdl,PAGE_EXECUTE_READWRITE) != STATUS_SUCCESS) {
      //DbgPrint("ALockPage: Error: MmProtectMdlSystemAddress failed. \n");
      break;
	}

	}
	else {
      Buffer = (PUCHAR)SysAddr;
	}

   __asm cli // disable all interrupts to make sure we are no interrupted

   __asm  // disable page write-protection (cr0 16th bit)
   {
    push eax
    mov eax, cr0
    and eax, not 0x10000
    mov cr0, eax
	pop eax
   }

	Success = TRUE;
  } while (FALSE);

  if(Success) 
	  return Buffer;
  else 
	  return NULL;

}



VOID AUnLockPage(PVOID SysAddr, PVOID LockAddr, ULONG Length, PMDL* Mdl, BOOLEAN IsPagedMemory) 
{
  
   __asm  // enable page write-protection (cr0 16th bit)
   {
    push eax
    mov eax, cr0
    or eax, 0x10000
    mov cr0, eax
	pop eax
   }

  __asm sti // enable interrupts again

  if(IsPagedMemory) {
     if(*Mdl == NULL)
	    return;

     // MmUnlockPages if PagedPool
	  __try 
      {
	    MmUnlockPages(*Mdl);
      }
      __except (EXCEPTION_EXECUTE_HANDLER)
      {
	    //DbgPrint("AUnLockPage: Error: MmUnlockPages failed. \n");
      }

    IoFreeMdl(*Mdl);
    *Mdl = NULL;
  }
}

/* base opcode flags (by table) */ 
#define OP_NONE           0x000
#define OP_DATA_I8        0x001
#define OP_DATA_I16       0x002
#define OP_DATA_I32       0x004
#define OP_MODRM          0x008
#define OP_DATA_PRE66_67  0x010
#define OP_PREFIX         0x020
#define OP_REL32          0x040
#define OP_REL8           0x080

/* extended opcode flags (by analyzer) */
#define OP_EXTENDED       0x100



static UCHAR packed_table[] = 
{
	0x80, 0x84, 0x80, 0x84, 0x80, 0x84, 0x80, 0x84,
	0x80, 0x88, 0x80, 0x88, 0x80, 0x88, 0x80, 0x88,
	0x8c, 0x8b, 0x8b, 0x8b, 0x8b, 0x8b, 0x8b, 0x8b,
	0x90, 0x94, 0x98, 0x8b, 0x9c, 0x9c, 0x9c, 0x9c,
	0xa0, 0x80, 0x80, 0x80, 0x8b, 0x8b, 0xa4, 0x8b,
	0xa8, 0x8b, 0x84, 0x8b, 0xac, 0xac, 0xa8, 0xa8,
	0xb0, 0xb4, 0xb8, 0xbc, 0x80, 0xc0, 0x80, 0x80,
	0x9c, 0xac, 0xc4, 0x8b, 0xc8, 0x90, 0x8b, 0x90,
	0x80, 0x8b, 0x8b, 0xcc, 0x80, 0x80, 0xd0, 0x8b,
	0x80, 0xd4, 0x80, 0x80, 0x8b, 0x8b, 0x8b, 0x8b,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0xd8, 0xdc, 0x8b, 0x80,
	0xe0, 0xe0, 0xe0, 0xe0, 0x80, 0x80, 0x80, 0x80,
	0x8f, 0xcf, 0x8f, 0xdb, 0x80, 0x80, 0xe4, 0x80,
	0xe8, 0xd9, 0x8b, 0x8b, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xdc,
	0x08, 0x08, 0x08, 0x08, 0x01, 0x10, 0x00, 0x00,
	0x01, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x08, 0x08, 0x20, 0x20, 0x20, 0x20,
	0x10, 0x18, 0x01, 0x09, 0x81, 0x81, 0x81, 0x81,
	0x09, 0x18, 0x09, 0x09, 0x00, 0x00, 0x12, 0x00,
	0x10, 0x10, 0x10, 0x10, 0x01, 0x01, 0x01, 0x01,
	0x09, 0x09, 0x02, 0x00, 0x08, 0x08, 0x09, 0x18,
	0x03, 0x00, 0x02, 0x00, 0x00, 0x01, 0x00, 0x00,
	0x01, 0x01, 0x00, 0x00, 0x50, 0x50, 0x12, 0x81,
	0x20, 0x00, 0x20, 0x20, 0x00, 0x08, 0x00, 0x09,
	0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x08, 0x00,
	0x09, 0x09, 0x09, 0x09, 0x08, 0x08, 0x08, 0x00,
	0x50, 0x50, 0x50, 0x50, 0x00, 0x00, 0x09, 0x08,
	0x08, 0x08, 0x09, 0x08
};

static ULONG code_flags(ULONG code)
{
	return packed_table[ packed_table[ code / 4 ] + (code % 4) ];
} 

ULONG x_code_flags(PUCHAR addr)
{
	ULONG opcode;

	if ( (opcode = addr[0]) == 0x0F)
	{
		opcode = (addr[1] | OP_EXTENDED);
	}

	return code_flags(opcode) | (opcode & OP_EXTENDED);
}

ULONG skip_rex(PUCHAR* op)
{
	ULONG len = 0;
	
	while ( (**op > 0x40)  && (**op < 0x50))
	{
		*op += 1;
		len++;
	}
	return len;
}

ULONG ASizeOfCode(PVOID FunctionAddress)
{
	PUCHAR code;
	UCHAR i_mod, i_rm, i_reg;
	ULONG op1, op2, flags;
	ULONG pfx66, pfx67;
	ULONG osize, oflen;
	ULONG REX;

	code = (PUCHAR)FunctionAddress;

	pfx66 = pfx67 = osize = oflen = REX =0;

	if (skip_rex((PUCHAR*)&code))
	{
		osize ++;
		REX = 4;
	}
	/* skip preffixes */
	while (code_flags(*code) & OP_PREFIX)
	{
		if (*code == 0x66) pfx66 = 1;
		if (*code == 0x67) pfx67 = 1;
		code++; osize++;
	}
	
	/* get opcode size and flags */
	op1 = *code++; osize++;

	if (op1 == 0x0F)
	{
		op2 = (*code | OP_EXTENDED);
		code++; osize++;		
	} else 
	{
		op2 = op1;
		
		/* pfx66 = pfx67 for opcodes A0 - A3 */
		if (op2 >= 0xA0 && op2 <= 0xA3) 
		{
			pfx66 = pfx67;
		}
	}

	flags = code_flags(op2);
	
	/* process MODRM byte */
	if (flags & OP_MODRM)
	{
		REX = 0;
		i_mod = (*code >> 6);
		i_reg = (*code & 0x38) >> 3;  
		i_rm  = (*code & 7);
		code++; osize++;

		/* in F6 and F7 opcodes, immediate value present if i_reg == 0 */
		if (op1 == 0xF6 && i_reg == 0) 
		{
			flags |= OP_DATA_I8;    
		}
		if (op1 == 0xF7 && i_reg == 0)
		{
			flags |= OP_DATA_PRE66_67; 
		}
			
		switch (i_mod)
		{
			case 0:
			  {
				  if (pfx67)
				  {
					  if (i_rm == 6) oflen = 2;
				  } else
				  {
					  if (i_rm == 5) oflen = 4;
				  }
			  }
			break;
			case 1:
			  {
				  oflen = 1;
			  }
		    break; 
			case 2: 
			  {
				  if (pfx67) oflen = 2; else oflen = 4;
			  }
			break;
		}
		
		/* process SIB byte */
		if (pfx67 == 0 && i_rm == 4 && i_mod != 3)
		{
			if ( (*code & 7) == 5 && (i_mod != 1) )
			{
				oflen = 4;
			}

			oflen++;
		}

		osize += oflen;
	}

	/* process offset */
	if (flags & OP_DATA_PRE66_67)
	{
		osize += 4 + REX - (pfx66 << 1);
	}
	/* process immediate value */
	osize += (flags & 7);
	
	return osize;
}

#ifdef  __cplusplus
}
#endif

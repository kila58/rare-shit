#include "microhook.h"

/*memcpy*/
void *MH_memcpy(void *src, void *dst, DWORD sz)
{
	BYTE *bsrc = (BYTE*)src; --bsrc;
	BYTE *bdst = (BYTE*)dst; --bdst;
	while (sz--) *(++bdst) = *(++bsrc);
	return bdst;
}

/*memset*/
void *MH_memset(void *ptr, BYTE val, DWORD sz)
{
	BYTE *bptr = (BYTE*)ptr; --bptr;
	while (sz--) *(++bptr) = val;
	return ptr;
}

/*return instruction size*/
BYTE MH_instsz(BYTE *instruction)
{
	hde32s hde;
	MH_memset((void*)&hde, 0, sizeof(hde32s));
	hde32_disasm((void*)instruction, &hde);
	return hde.len;
}

/*return real function address*/
MH_FUNC MH_realfunc(MH_FUNC func)
{
	hde32s hde;
	MH_memset((void*)&hde, 0, sizeof(hde32s));
	hde32_disasm((void*)func, &hde);
	if (hde.opcode == 0xE9 && hde.imm.imm32 != 0) //opcode
	{
		DWORD offset = hde.imm.imm32; //imm32
		return (func + hde.len + offset);
	}
	return func;
}

/*returns pointer to pre-hook function*/
MH_FUNC MH_VTBLHook(MH_VTBL pVTBL, DWORD dwIdx, MH_FUNC pNewFunc)
{
	MH_CHKFUNC(pNewFunc);
	MH_FUNC pOrigFunc;

#ifdef MH_WINDOWS
	DWORD dwOldProt;
	VirtualProtect((void*)&pVTBL[dwIdx], 4, PAGE_READWRITE, &dwOldProt);
#endif

	pOrigFunc = (BYTE*)pVTBL[dwIdx]; //save old function
	MH_CHKFUNC(pOrigFunc);
	pVTBL[dwIdx] = (DWORD)pNewFunc; //set VTBL entry to new function

#ifdef MH_WINDOWS
	VirtualProtect((void*)&pVTBL[dwIdx], 4, dwOldProt, NULL);
#endif
	return pOrigFunc;
}

/*returns pointer to old (detour+7) function*/
MH_FUNC MH_Detour(MH_FUNC pFunc, MH_FUNC pNewFunc, MH_FUNC pDetour)
{
	MH_CHKFUNC(pFunc); MH_CHKFUNC(pNewFunc); MH_CHKFUNC(pDetour);

	hde32s hde; MH_memset((void*)&hde, 0, sizeof(hde32s));
	DWORD dwOrigFuncSz = 0;
	while (hde.opcode != 0xC2 && hde.opcode != 0xC3
		&& hde.opcode != 0xCA && hde.opcode != 0xCB
		&& hde.opcode != 0xCF)
	{
		hde32_disasm((void*)(pFunc + dwOrigFuncSz), &hde);
		dwOrigFuncSz += hde.len;
	}
	dwOrigFuncSz -= hde.len;

	DWORD reqsz = 0;
	while ((reqsz += MH_instsz(pFunc+reqsz)) < 6);

#ifdef MH_WINDOWS
	DWORD funcProt, detourProt;
	VirtualProtect((void*)pFunc, reqsz, PAGE_READWRITE, &funcProt);
	VirtualProtect((void*)pDetour, 7+reqsz+6, PAGE_READWRITE, &detourProt);
#endif

	BYTE bTemp[256]; MH_memcpy((void*)pFunc, (void*)&bTemp[0], reqsz);

	/* SAVE & OVERWRITE TOP OF ORIGINAL FUNCTION */
	DWORD dwDetour = (DWORD)pDetour, i = 0;
	*(pFunc + 0) = MH_PUSHimm; //PUSH imm32
	MH_memcpy((void*)&dwDetour, (void*)(pFunc + 1), 4); //imm32
	*(pFunc + 5) = MH_RET; //RET
	for (i = 6; i < reqsz; i++) *(pFunc + i) = MH_NOP;

	/* CALL NEW FUNCTION */
	DWORD dwNewFunc = (DWORD)pNewFunc;
	*(pDetour + 0) = MH_MOVEAXimm; //MOV EAX, imm32
	MH_memcpy((void*)&dwNewFunc, (void*)(pDetour + 1), 4); //imm32
	*(pDetour + 5) = MH_CALL; //CALL
	*(pDetour + 6) = MH_CALLeax; //eax

	MH_FUNC pOldFunc = (pDetour + 7);
	/* ORIGINAL FUNCTION TOP */
	MH_memcpy((void*)&bTemp[0], (void*)pOldFunc, reqsz);
	/* JUMP TO REST OF ORIGINAL FUNCTION */
	*(pOldFunc + reqsz) = MH_PUSHimm; //PUSH imm32
	DWORD dwOldFuncRest = (DWORD)(pFunc + reqsz);
	MH_memcpy((void*)&dwOldFuncRest, (void*)(pOldFunc + reqsz + 1), 4); //imm32
	*(pOldFunc + reqsz + 5) = MH_RET; //RET

#ifdef MH_WINDOWS
	VirtualProtect((void*)pFunc, reqsz, funcProt, NULL);
	VirtualProtect((void*)pDetour, 7+reqsz+6, detourProt, NULL);
#endif

	return pOldFunc;
}

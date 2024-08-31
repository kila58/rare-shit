#include "winlite.h"
#include "hde32.h"

#define MH_PUSHimm (0x68)
#define MH_RET (0xC3)
#define MH_NOP (0x90)
#define MH_MOVEAXimm (0xB8)
#define MH_CALL (0xFF)
#define MH_CALLeax (0xD0)
#define MH_CHKFUNC(func) (func = MH_realfunc(func))
#define MH_REALFUNC(func) (MH_realfunc(func))
#define MH_FIXSTACK() __asm { pop eax }
#define MH_PUSHRADDR() __asm { push raddr }

typedef BYTE* MH_FUNC;
typedef DWORD* MH_VTBL;

void *MH_memcpy(void *src, void *dst, DWORD sz);
void *MH_memset(void *ptr, BYTE val, DWORD sz);
BYTE MH_instsz(BYTE *instruction);
MH_FUNC MH_realfunc(MH_FUNC func);
MH_FUNC MH_VTBLHook(MH_VTBL pVTBL, DWORD dwIdx, MH_FUNC pNewFunc);
MH_FUNC MH_Detour(MH_FUNC pFunc, MH_FUNC pNewFunc, MH_FUNC pDetour);

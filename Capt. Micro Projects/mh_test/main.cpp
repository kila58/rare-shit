#include "winlite.h"
#include "microhook.h"
#include "stdio.h"

typedef DWORD (*_enc)(DWORD);

DWORD encrypt(DWORD sig)
{
	return sig ^ 0xBADDF00D;
}

DWORD haxencrypt(DWORD raddr, DWORD arg1)
{
	if (raddr != 0)
		printf("*** haxencrypt: %X\n", arg1);
	MH_FIXSTACK();
	return arg1;
}

__declspec(naked) void detourloc(void)
{
	__asm { nop }; __asm { nop }; __asm { nop }; __asm { nop };
	__asm { nop }; __asm { nop }; __asm { nop }; __asm { nop };
	__asm { nop }; __asm { nop }; __asm { nop }; __asm { nop };
	__asm { nop }; __asm { nop }; __asm { nop }; __asm { nop };
	__asm { nop }; __asm { nop }; __asm { nop }; __asm { nop };
	__asm { nop }; __asm { nop }; __asm { nop }; __asm { nop };
	__asm { nop }; __asm { nop }; __asm { nop }; __asm { nop };
	__asm { nop }; __asm { nop }; __asm { nop }; __asm { nop };
	__asm { nop }; __asm { nop }; __asm { nop }; __asm { nop };
	__asm { nop }; __asm { nop }; __asm { nop }; __asm { nop };
}

int main()
{
	printf("Detour test\n\n");
	
	printf("encrypt(0xDEADBEEF) = %X\n", encrypt(0xDEADBEEF));
	printf("detouring function...\n");
	MH_Detour((MH_FUNC)encrypt, (MH_FUNC)haxencrypt, (MH_FUNC)detourloc);
	printf("encrypt(0xDEADBEEF) = %X\n", encrypt(0xDEADBEEF));

	return 0;
}

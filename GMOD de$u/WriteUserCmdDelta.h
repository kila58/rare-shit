#include "Entrypoint.h"
#include <Windows.h>

bool __stdcall HookedWriteUsercmdDeltaToBuffer(void* buf, int from, int to, bool isnew)
{
	UserCmd nullcmd, *F, *T;

	typedef void(__cdecl* WriteUserCmd_t)(void*, UserCmd*, UserCmd*);

	static WriteUserCmd_t WriteUserCmd = (WriteUserCmd_t)sigscan::FindPattern("client.dll", "\x55\x8B\xEC\x8B\x45\x10\x8B\x48\x04");

	if (from == -1)
		F = &nullcmd;
	else if (!(F = HookedGetUserCmd(from)))
		F = &nullcmd;

	if (!(T = HookedGetUserCmd(to)))
		T = &nullcmd;

	
	WriteUserCmd(buf, T, F);

	return !(*(bool*)((DWORD)buf + 0x10));
}
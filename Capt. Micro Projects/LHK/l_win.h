#ifndef _l_win_h_
#define _l_win_h_

#include "winlite.h"

void l_win_register(lua_State *l);
void l_win_globals(lua_State *l);

BOOL VistaOrHigher();
DWORD RemoteGMH(HANDLE proc, char *module);
DWORD RemoteGMH2(HANDLE proc, char *module);

BOOL WritePrivateProfileIntA(LPCSTR lpAppName, LPCSTR lpKeyName, INT nValue, LPCSTR lpFileName);
BOOL WritePrivateProfileFloatA(LPCSTR lpAppName, LPCSTR lpKeyName, FLOAT fValue, LPCSTR lpFileName);
FLOAT GetPrivateProfileFloatA(LPCSTR lpAppName, LPCSTR lpKeyName, FLOAT fDefault, LPCSTR lpFileName);

LUA_FUNC(WriteConsole);
LUA_FUNC(SetConCursorPos);
LUA_FUNC(SetConTextAttribute);

LUA_FUNC(CleanExit);
LUA_FUNC(Sleep);
LUA_FUNC(CloseHandle);
LUA_FUNC(IsKeyDown);
LUA_FUNC(GetTickCount);

LUA_FUNC(FindWindow);
LUA_FUNC(PostMessage);
LUA_FUNC(SendMessage);
LUA_FUNC(GetProcessId);
LUA_FUNC(OpenProcess);
LUA_FUNC(TerminateProcess);
LUA_FUNC(GetBaseAddress);
LUA_FUNC(SigScan);

LUA_FUNC(AllocMem);
LUA_FUNC(FreeMem);
LUA_FUNC(ProtectMem);
LUA_FUNC(QueryMem);

LUA_FUNC(ReadByte);
LUA_FUNC(ReadShort);
LUA_FUNC(ReadInt);
LUA_FUNC(ReadLong);
LUA_FUNC(ReadFloat);
LUA_FUNC(ReadStr);

LUA_FUNC(WriteByte);
LUA_FUNC(WriteShort);
LUA_FUNC(WriteInt);
LUA_FUNC(WriteLong);
LUA_FUNC(WriteFloat);
LUA_FUNC(WriteStr);

LUA_FUNC(GetINIInt);
LUA_FUNC(GetINIFloat);
LUA_FUNC(GetINIStr);

LUA_FUNC(SetINIInt);
LUA_FUNC(SetINIFloat);
LUA_FUNC(SetINIStr);

LUA_FUNC(DrawInvalidateRect);
LUA_FUNC(DrawCreateBrush);
LUA_FUNC(DrawBox);
LUA_FUNC(DrawGetTextColor);
LUA_FUNC(DrawSetTextColor);
LUA_FUNC(DrawText);

LUA_FUNC(SetDebugPrivileges);

#endif

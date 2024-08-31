#include "main.h"

void lwin_import(lua_State *l)
{
	LUA_REG(l, Sleep);
	LUA_REG(l, IsKeyDown);
}

LUA_FUNC(Sleep)
{
	DWORD ms = (DWORD)lua_tointeger(l, 1);
	Sleep(ms);
	return 0;
}

LUA_FUNC(IsKeyDown)
{
	DWORD key = (DWORD)lua_tointeger(l, 1);
	BOOL keydown = 0;
	if (GetAsyncKeyState(key) & 0x8000) keydown = 1;
	lua_pushboolean(l, keydown);
	return 1;
}

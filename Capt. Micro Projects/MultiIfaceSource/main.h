#ifndef _MAIN_H_
#define _MAIN_H_

#include "winlite.h"
#include "lwin.h"
#include "lconvar.h"
#include "lentlist.h"
#include "lcliententity.h"

#define LUA_FUNC(name) int lf_##name(lua_State *l)
#define LUA_REG(l, name) lua_register(l, #name, lf_##name)

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID lpReserved);
DWORD WINAPI MultiFaceSource(LPVOID lpParam)

#endif //_MAIN_H_

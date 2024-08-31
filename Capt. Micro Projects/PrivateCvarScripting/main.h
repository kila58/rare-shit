#ifndef _MAIN_H_
#define _MAIN_H_

#include "winlite.h"

#define GAME_DLL
#define CVAR_NO_PRIVATE
#pragma comment(lib, "bitmap.lib")
#pragma comment(lib, "choreoobjects.lib")
#pragma comment(lib, "dmxloader.lib")
#pragma comment(lib, "mathlib.lib")
#pragma comment(lib, "matsys_controls.lib")
#pragma comment(lib, "nvtristrip.lib")
#pragma comment(lib, "particles.lib")
#pragma comment(lib, "raytrace.lib")
#pragma comment(lib, "steam_api.lib")
#pragma comment(lib, "tier0.lib")
#pragma comment(lib, "tier1.lib")
#pragma comment(lib, "tier2.lib")
#pragma comment(lib, "tier3.lib")
#pragma comment(lib, "vgui_controls.lib")
#pragma comment(lib, "vmpi.lib")
#pragma comment(lib, "vstdlib.lib")
#pragma comment(lib, "vtf.lib")
#include "public/icvar.h"
#include "public/tier1/convar.h"
#include "public/inetchannel.h"
#include "public/inetchannelinfo.h"
#include "public/cdll_int.h"

#pragma comment(lib, "lua5.1.lib")
#pragma comment(lib, "lua51.lib")
extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#define LUA_FUNC(name) int lf_##name(lua_State *l)
#define LUA_REG(l, name) lua_register(l, #name, lf_##name)

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID lpReserved);

DWORD WINAPI PCS(LPVOID lpParam);

void CVARglobals(lua_State *l);
void CVARregister(lua_State *l);

LUA_FUNC(Sleep);
LUA_FUNC(IsKeyDown);

LUA_FUNC(WriteConsole);

void VarChangeToLuaCallback(IConVar *var, const char *pOldValue, float flOldValue);
void CommandToLuaCallback(const CCommand &command);

LUA_FUNC(CreateVar);
LUA_FUNC(FindVar);
LUA_FUNC(CreateCommand);
LUA_FUNC(FindCommand);
LUA_FUNC(DeleteVar);

LUA_FUNC(GetFlags);
LUA_FUNC(SetFlags);
LUA_FUNC(GetName);
LUA_FUNC(SetName);
LUA_FUNC(GetHelpString);
LUA_FUNC(SetHelpString);

LUA_FUNC(CC_Dispatch);

LUA_FUNC(CV_GetFloat);
LUA_FUNC(CV_GetInt);
LUA_FUNC(CV_GetBool);
LUA_FUNC(CV_GetString);

LUA_FUNC(CV_SetFloat);
LUA_FUNC(CV_SetInt);
LUA_FUNC(CV_SetString);

LUA_FUNC(CV_Revert);
LUA_FUNC(CV_GetMin);
LUA_FUNC(CV_GetMax);
LUA_FUNC(CV_GetDefault);


#endif //_MAIN_H_
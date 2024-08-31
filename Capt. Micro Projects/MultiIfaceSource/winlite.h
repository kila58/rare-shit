#ifndef _WINLITE_H_
#define _WINLITE_H_

#define WIN32_LEAN_AND_MEAN
#define NOWINRES
#define NOSERVICE
#define NOMCX
#define NOIME
#include <windows.h>

#pragma comment(lib, "lua5.1.lib")
extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

extern lua_State *g_LuaState;

#endif //_WINLITE_H_

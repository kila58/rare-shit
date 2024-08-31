#ifndef WINLITE_H
#define WINLITE_H

#define WIN32_LEAN_AND_MEAN
#define NOWINRES
#define NOSERVICE
#define NOMCX
#define NOIME
#include <windows.h>
#include <TlHelp32.h>
#include <stdlib.h> //atof, memset

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

#endif
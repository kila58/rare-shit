#ifndef _LCONVAR_H_
#define _LCONVAR_H_

#include "winlite.h"
#include "gamesdk.h"

void lconvar_import(lua_State *l);

void VarChangeToLuaCallback(IConVar *var, const char *pOldValue, float flOldValue);
void CommandToLuaCallback(const CCommand &command);

LUA_FUNC(CV_print);

LUA_FUNC(CV_CreateVar);
LUA_FUNC(CV_CreateCmd);

LUA_FUNC(CV_FindVar);
LUA_FUNC(CV_FindCmd);

LUA_FUNC(CV_Delete);

LUA_FUNC(CV_DispatchCmd);

LUA_FUNC(CV_GetFlags);
LUA_FUNC(CV_SetFlags);

LUA_FUNC(CV_GetName);
LUA_FUNC(CV_SetName);

LUA_FUNC(CV_GetHelpText);
LUA_FUNC(CV_SetHelpText);

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

#endif //_LCONVAR_H_

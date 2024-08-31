#ifndef _LENTLIST_H_
#define _LENTLIST_H_

#include "winlite.h"
#include "gamesdk.h"

void lentlist_import(lua_State *l);

LUA_FUNC(EL_GetClientEntity);
LUA_FUNC(EL_GetHighestEntityIndex);
LUA_FUNC(EL_NumberOfEntities);
LUA_FUNC(EL_GetMaxEntities);

#endif //_LENTLIST_H_

#ifndef _LCLIENTENTITY_H_
#define _LCLIENTENTITY_H_

#include "winlite.h"
#include "gamesdk.h"

void lcliententity_import(lua_State *l);

LUA_FUNC(CE_Release);
LUA_FUNC(CE_GetAbsOrigin);
LUA_FUNC(CE_GetAbsAngles);

#endif //_LCLIENTENTITY_H_

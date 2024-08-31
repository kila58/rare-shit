#ifndef _LWIN_H_
#define _LWIN_H_

#include "winlite.h"

void lwin_import(lua_State *l);

LUA_FUNC(Sleep);
LUA_FUNC(IsKeyDown);

#endif //_LWIN_H_

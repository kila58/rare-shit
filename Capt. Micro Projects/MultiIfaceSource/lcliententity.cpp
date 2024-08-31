#include "lcliententity.h"

void lcliententity_import(lua_State *l)
{
	//Register functions
	LUA_REG(l, CE_Release);
	LUA_REG(l, CE_GetAbsOrigin);
	LUA_REG(l, CE_GetAbsAngles);
}

LUA_FUNC(CE_Release)
{
	if (lua_gettop(l) != 1) return 0;
	IClientEntity *ent = (IClientEntity*)lua_touserdata(l, 1);
	ent->Release();
	return 0;
}

LUA_FUNC(CE_GetAbsOrigin)
{
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	IClientEntity *ent = (IClientEntity*)lua_touserdata(l, 1);
	Vector vec = ent->GetAbsOrigin();
	lua_pushnumber(vec.x);
	lua_pushnumber(vec.y);
	lua_pushnumber(vec.z);
	return 3;
}

LUA_FUNC(CE_GetAbsAngles)
{
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	IClientEntity *ent = (IClientEntity*)lua_touserdata(l, 1);
	QAngle ang = ent->GetAbsAngles();
	lua_pushnumber(ang.x);
	lua_pushnumber(ang.y);
	lua_pushnumber(ang.z);
	return 3;
}

#include "lentlist.h"

IClientEntityList *g_IClientEntityList = 0;

void lentlist_import(lua_State *l)
{
	//get IClientEntityList interface
	CreateInterfaceFn clientFactory = (CreateInterfaceFn)GetProcAddress(
		GetModuleHandle("client.dll"), "CreateInterface");
	if (clientFactory == 0)
	{
		MessageBoxA(0, "Failed to load client factory!", "MultiIfaceSource", 0);
		return;
	}
	g_IClientEntityList = (ICvar*)clientFactory(VCLIENTENTITYLIST_INTERFACE_VERSION, 0);
	if (g_IClientEntityList == 0)
	{
		MessageBoxA(0, "Failed to load IClientEntityList interface!", "MultiIfaceSource", 0);
		return;
	}

	//Register functions
	LUA_REG(l, EL_GetClientEntity);
	LUA_REG(l, EL_GetHighestEntityIndex);
	LUA_REG(l, EL_NumberOfEntities);
	LUA_REG(l, EL_GetMaxEntities);
}

LUA_FUNC(EL_GetClientEntity)
{
	if (g_IClientEntityList == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	IClientEntity *ent = g_IClientEntityList->
		GetClientEntity(lua_tointeger(l, 1));
	lua_pushlightuserdata(ent);
	return 1;
}

LUA_FUNC(EL_GetHighestEntityIndex)
{
	if (g_IClientEntityList == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 0) { lua_pushnil(l); return 1; }
	lua_pushinteger(l, g_IClientEntityList->GetHighestEntityIndex());
	return 1;
}

LUA_FUNC(EL_NumberOfEntities)
{
	if (g_IClientEntityList == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 0) { lua_pushnil(l); return 1; }
	lua_pushinteger(l, g_IClientEntityList->NumberOfEntities());
	return 1;
}

LUA_FUNC(EL_GetMaxEntities)
{
	if (g_IClientEntityList == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 0) { lua_pushnil(l); return 1; }
	lua_pushinteger(l, g_IClientEntityList->GetMaxEntities());
	return 1;
}

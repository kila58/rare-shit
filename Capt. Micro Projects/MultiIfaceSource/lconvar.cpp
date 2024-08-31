#include "lconvar.h"

ICvar *g_ICvar = 0;

void lconvar_import(lua_State *l)
{
	//get ICvar interface
	CreateInterfaceFn vstdlibFactory = (CreateInterfaceFn)GetProcAddress(
		GetModuleHandle("vstdlib.dll"), "CreateInterface");
	if (vstdlibFactory == 0)
	{
		MessageBoxA(0, "Failed to load vstdlib factory!", "MultiIfaceSource", 0);
		return;
	}
	g_ICvar = (ICvar*)vstdlibFactory(CVAR_INTERFACE_VERSION, 0);
	if (g_ICvar == 0)
	{
		MessageBoxA(0, "Failed to load ICvar interface!", "MultiIfaceSource", 0);
		return;
	}

	//Register functions
	LUA_REG(l, CV_print);

	LUA_REG(l, CV_CreateVar);
	LUA_REG(l, CV_CreateCmd);

	LUA_REG(l, CV_FindVar);
	LUA_REG(l, CV_FindCmd);

	LUA_REG(l, CV_Delete);

	LUA_REG(l, CV_DispatchCmd);

	LUA_REG(l, CV_GetFlags);
	LUA_REG(l, CV_SetFlags);

	LUA_REG(l, CV_GetName);
	LUA_REG(l, CV_SetName);

	LUA_REG(l, CV_GetHelpText);
	LUA_REG(l, CV_SetHelpText);

	LUA_REG(l, CV_GetFloat);
	LUA_REG(l, CV_GetInt);
	LUA_REG(l, CV_GetBool);
	LUA_REG(l, CV_GetString);

	LUA_REG(l, CV_SetFloat);
	LUA_REG(l, CV_SetInt);
	LUA_REG(l, CV_SetString);

	LUA_REG(l, CV_Revert);
	LUA_REG(l, CV_GetMin);
	LUA_REG(l, CV_GetMax);
	LUA_REG(l, CV_GetDefault);

	// The default, no flags at all
	lua_pushinteger(l, FCVAR_NONE);
	lua_setglobal(l, "FCVAR_NONE");

	// ConVar Systems
	lua_pushinteger(l, FCVAR_UNREGISTERED);
	lua_setglobal(l, "FCVAR_UNREGISTERED");
	lua_pushinteger(l, FCVAR_DEVELOPMENTONLY);
	lua_setglobal(l, "FCVAR_DEVELOPMENTONLY");
	lua_pushinteger(l, FCVAR_GAMEDLL);
	lua_setglobal(l, "FCVAR_GAMEDLL");
	lua_pushinteger(l, FCVAR_CLIENTDLL);
	lua_setglobal(l, "FCVAR_CLIENTDLL");
	lua_pushinteger(l, FCVAR_HIDDEN);
	lua_setglobal(l, "FCVAR_HIDDEN");

	// ConVar only
	lua_pushinteger(l, FCVAR_PROTECTED);
	lua_setglobal(l, "FCVAR_PROTECTED");
	lua_pushinteger(l, FCVAR_SPONLY);
	lua_setglobal(l, "FCVAR_SPONLY");
	lua_pushinteger(l, FCVAR_ARCHIVE);
	lua_setglobal(l, "FCVAR_ARCHIVE");
	lua_pushinteger(l, FCVAR_NOTIFY);
	lua_setglobal(l, "FCVAR_NOTIFY");
	lua_pushinteger(l, FCVAR_USERINFO);
	lua_setglobal(l, "FCVAR_USERINFO");
	lua_pushinteger(l, FCVAR_CHEAT);
	lua_setglobal(l, "FCVAR_CHEAT");
	lua_pushinteger(l, FCVAR_PRINTABLEONLY);
	lua_setglobal(l, "FCVAR_PRINTABLEONLY");
	lua_pushinteger(l, FCVAR_UNLOGGED);
	lua_setglobal(l, "FCVAR_UNLOGGED");
	lua_pushinteger(l, FCVAR_NEVER_AS_STRING);
	lua_setglobal(l, "FCVAR_NEVER_AS_STRING");
	lua_pushinteger(l, FCVAR_REPLICATED);
	lua_setglobal(l, "FCVAR_REPLICATED");
	lua_pushinteger(l, FCVAR_DEMO);
	lua_setglobal(l, "FCVAR_DEMO");
	lua_pushinteger(l, FCVAR_DONTRECORD);
	lua_setglobal(l, "FCVAR_DONTRECORD");
	lua_pushinteger(l, FCVAR_NOT_CONNECTED);
	lua_setglobal(l, "FCVAR_NOT_CONNECTED");
	lua_pushinteger(l, FCVAR_ARCHIVE_XBOX);
	lua_setglobal(l, "FCVAR_ARCHIVE_XBOX");
	lua_pushinteger(l, FCVAR_SERVER_CAN_EXECUTE);
	lua_setglobal(l, "FCVAR_SERVER_CAN_EXECUTE");
	lua_pushinteger(l, FCVAR_SERVER_CANNOT_QUERY);
	lua_setglobal(l, "FCVAR_SERVER_CANNOT_QUERY");
	lua_pushinteger(l, FCVAR_CLIENTCMD_CAN_EXECUTE);
	lua_setglobal(l, "FCVAR_CLIENTCMD_CAN_EXECUTE");
}

void VarChangeToLuaCallback(IConVar *var, const char *pOldValue, float flOldValue)
{
	ConVar *cvar = (ConVar*)var;
	if ((cvar == 0) || (g_LuaState == 0)) return;
	lua_pushstring(g_LuaState, "VarChangeCallback");
	lua_pushlightuserdata(g_LuaState, (void*)cvar);
	lua_pushstring(g_LuaState, pOldValue);
	lua_pushnumber(g_LuaState, flOldValue);
	if (lua_pcall(g_LuaState, 3, 0, 0) != 0)
	{
		if (g_ICvar == 0) return;
		g_ICvar->ConsolePrintf("[PCS] Failed to call VarChangeCallback");
		return;
	}
}

void CommandToLuaCallback(const CCommand &command)
{
	ConCommand *ccmd = (ConCommand*)&command;
	if ((ccmd == 0) || (g_LuaState == 0) || (g_ICvar == 0)) return;
	lua_pushstring(g_LuaState, "CommandCallback");
	lua_pushlightuserdata(g_LuaState, (void*)ccmd);
	if (lua_pcall(g_LuaState, 1, 0, 0) != 0)
	{
		g_ICvar->ConsolePrintf("[PCS] Failed to call CommandCallback");
	}
}

LUA_FUNC(CV_print)
{
	if (g_ICvar == 0) return 0;
	if (lua_gettop(l) == 0) return 0;

	int numargs = lua_gettop(l), i = 0;
	for (i = 0; i < numargs; i ++)
	{
		char *str = (char*)lua_tostring(l, i);
		g_ICvar->ConsolePrintf(str);
	}

	return 0;
}

LUA_FUNC(CV_CreateVar)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 4) { lua_pushnil(l); return 1; }
	const char *varname = lua_tostring(l, 1);
	const char *defval = lua_tostring(l, 2);
	int flags = lua_tointeger(l, 3);
	const char *help = lua_tostring(l, 4);
	ConVar *newcvar = new ConVar(varname, defval, flags, help, VarChangeToLuaCallback);
	newcvar->m_pNext = 0; g_ICvar->RegisterConCommand(newcvar);
	//g_ICvar->ConsolePrintf("[PCS] Created ConVar '%s' [0x%08X]\n", varname, (DWORD)newcvar);
	lua_pushlightuserdata(l, newcvar);
	return 1;
}

LUA_FUNC(CV_CreateCmd)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 3) { lua_pushnil(l); return 1; }
	const char *varname = lua_tostring(l, 1);
	int flags = lua_tointeger(l, 2);
	const char *help = lua_tostring(l, 3);
	ConCommand *newcvar = new ConCommand(varname, CommandToLuaCallback, help, flags);
	newcvar->m_pNext = 0; g_ICvar->RegisterConCommand(newcvar);
	//g_ICvar->ConsolePrintf("[PCS] Created ConCommand '%s' [0x%08X]\n", varname, (DWORD)newcvar);
	lua_pushlightuserdata(l, newcvar);
	return 1;
}

LUA_FUNC(CV_FindVar)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	const char *varname = lua_tostring(l, 1);
	ConVar *cv = g_ICvar->FindVar(varname);
	if (cv != 0) lua_pushlightuserdata(l, (PVOID)cv);
	else lua_pushnil(l);
	return 1;
}

LUA_FUNC(CV_FindCmd)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	const char *cmdname = lua_tostring(l, 1);
	ConCommand *cc = g_ICvar->FindCommand(cmdname);
	if (cc == 0) { lua_pushnil(l); return 1; }

	lua_pushlightuserdata(l, (PVOID)cc);
	return 1;
}

LUA_FUNC(CV_Delete)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	ConCommandBase *cb = (ConCommandBase*)lua_touserdata(l, 1);
	g_ICvar->UnregisterConCommand(cb);
	return 0;
}

LUA_FUNC(CV_DispatchCmd)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 2) { lua_pushnil(l); return 1; }
	ConCommand *cc = (ConCommand*)lua_touserdata(l, 1);
	if (cc == 0) { lua_pushnil(l); return 1; }

	const char *str = (const char*)lua_tostring(l, 2);
	CCommand ccmd; ccmd.Tokenize(str);
	cc->Dispatch(ccmd);

	return 0;
}

LUA_FUNC(CV_GetFlags)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	ConCommandBase *cb = (ConCommandBase*)lua_touserdata(l, 1);
	if (cb == 0) { lua_pushnil(l); return 1; }

	lua_pushnumber(l, cb->m_nFlags);
	return 1;
}

LUA_FUNC(CV_SetFlags)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 2) { lua_pushnil(l); return 1; }
	ConCommandBase *cb = (ConCommandBase*)lua_touserdata(l, 1);
	if (cb == 0) { lua_pushnil(l); return 1; }

	int newflags = (int)lua_tointeger(l, 2);
	cb->m_nFlags = newflags;

	return 0;
}

LUA_FUNC(CV_GetName)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	ConCommandBase *cb = (ConCommandBase*)lua_touserdata(l, 1);
	if (cb == 0) { lua_pushnil(l); return 1; }

	lua_pushstring(l, cb->m_pszName);
	return 1;
}

LUA_FUNC(CV_SetName)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 2) { lua_pushnil(l); return 1; }
	ConCommandBase *cb = (ConCommandBase*)lua_touserdata(l, 1);
	if (cb == 0) { lua_pushnil(l); return 1; }

	const char *name = lua_tostring(l, 2);
	char *newname = (char*)GlobalAlloc(GMEM_ZEROINIT, lstrlenA(name) + 1);
	lstrcpyA(newname, name);
	cb->m_pszName = newname;

	return 0;
}

LUA_FUNC(CV_GetHelpText)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	ConCommandBase *cb = (ConCommandBase*)lua_touserdata(l, 1);
	if (cb == 0) { lua_pushnil(l); return 1; }

	lua_pushstring(l, cb->m_pszHelpString);
	return 1;
}

LUA_FUNC(CV_SetHelpText)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 2) { lua_pushnil(l); return 1; }
	ConCommandBase *cb = (ConCommandBase*)lua_touserdata(l, 1);
	if (cb == 0) { lua_pushnil(l); return 1; }

	//there is a memory allocation here that is never free'd, this is intended
	const char *help = lua_tostring(l, 2);
	char *newhelp = (char*)GlobalAlloc(GMEM_ZEROINIT, lstrlenA(help) + 1);
	lstrcpyA(newhelp, help);
	cb->m_pszHelpString = newhelp;

	return 0;
}

LUA_FUNC(CV_GetFloat)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	ConVar *cv = (ConVar*)lua_touserdata(l, 1);
	if (cv == 0) { lua_pushnil(l); return 1; }

	lua_pushnumber(l, cv->GetFloat());
	return 1;
}

LUA_FUNC(CV_GetInt)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	ConVar *cv = (ConVar*)lua_touserdata(l, 1);
	if (cv == 0) { lua_pushnil(l); return 1; }

	lua_pushinteger(l, cv->GetInt());
	return 1;
}

LUA_FUNC(CV_GetBool)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	ConVar *cv = (ConVar*)lua_touserdata(l, 1);
	if (cv == 0) { lua_pushnil(l); return 1; }

	lua_pushboolean(l, cv->GetBool());
	return 1;
}

LUA_FUNC(CV_GetString)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	ConVar *cv = (ConVar*)lua_touserdata(l, 1);
	if (cv == 0) { lua_pushnil(l); return 1; }

	lua_pushstring(l, cv->GetString());
	return 1;
}

LUA_FUNC(CV_SetFloat)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 2) { lua_pushnil(l); return 1; }
	ConVar *cv = (ConVar*)lua_touserdata(l, 1);
	if (cv == 0) { lua_pushnil(l); return 1; }

	float newvalue = (float)lua_tonumber(l, 2);
	cv->SetValue(newvalue);

	return 0;
}

LUA_FUNC(CV_SetInt)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 2) { lua_pushnil(l); return 1; }
	ConVar *cv = (ConVar*)lua_touserdata(l, 1);
	if (cv == 0) { lua_pushnil(l); return 1; }

	int newvalue = (int)lua_tointeger(l, 2);
	cv->SetValue(newvalue);

	return 0;
}

LUA_FUNC(CV_SetString)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 2) { lua_pushnil(l); return 1; }
	ConVar *cv = (ConVar*)lua_touserdata(l, 1);
	if (cv == 0) { lua_pushnil(l); return 1; }

	const char *newvalue = (const char*)lua_tostring(l, 2);
	cv->SetValue(newvalue);

	return 0;
}

LUA_FUNC(CV_Revert)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	ConVar *cv = (ConVar*)lua_touserdata(l, 1);
	if (cv == 0) { lua_pushnil(l); return 1; }

	cv->Revert();

	return 0;
}

LUA_FUNC(CV_GetMin)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	ConVar *cv = (ConVar*)lua_touserdata(l, 1);
	if (cv == 0) { lua_pushnil(l); return 1; }

	float minval = 0.0f;
	if (!cv->GetMin(minval)) { lua_pushnil(l); return 1; }

	lua_pushnumber(l, minval);
	return 1;
}

LUA_FUNC(CV_GetMax)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	ConVar *cv = (ConVar*)lua_touserdata(l, 1);
	if (cv == 0) { lua_pushnil(l); return 1; }

	float maxval = 0.0f;
	if (!cv->GetMax(maxval)) { lua_pushnil(l); return 1; }

	lua_pushnumber(l, maxval);
	return 1;
}

LUA_FUNC(CV_GetDefault)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	ConVar *cv = (ConVar*)lua_touserdata(l, 1);
	if (cv == 0) { lua_pushnil(l); return 1; }

	const char *defaultval = cv->GetDefault();
	lua_pushstring(l, defaultval);

	return 1;
}

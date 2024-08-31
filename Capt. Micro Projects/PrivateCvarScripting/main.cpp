#include "main.h"

ICvar *g_ICvar = 0;
IVEngineClient *g_IVEngineCleint = 0;
IBaseClientDLL *g_IBaseClientDLL = 0;
lua_State *g_LuaState;

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DWORD dwThreadId = 0;
		HANDLE hThread = CreateThread(0, 0,
			PCS, 0, 0, &dwThreadId);
	}
	return TRUE;
}

DWORD WINAPI PCS(LPVOID lpParam)
{
	CreateInterfaceFn engineFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandle("engine.dll"), "CreateInterface");
	if (engineFactory == 0)
	{
		MessageBoxA(0, "Failed to load engine factory!", "PCS", 0);
		ExitThread(1);
	}

	g_IVEngineCleint = (IVEngineClient*)engineFactory(VENGINE_CLIENT_INTERFACE_VERSION, 0);
	if (g_IVEngineCleint == 0)
	{
		MessageBoxA(0, "Failed to load IVEngineClient interface!", "PCS", 0);
		ExitThread(1);
	}

	CreateInterfaceFn vstdlibFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandle("vstdlib.dll"), "CreateInterface");
	if (vstdlibFactory == 0)
	{
		MessageBoxA(0, "Failed to load vstdlib factory!", "PCS", 0);
		ExitThread(1);
	}
	
	g_ICvar = (ICvar*)vstdlibFactory(CVAR_INTERFACE_VERSION, 0);
	if (g_ICvar == 0)
	{
		MessageBoxA(0, "Failed to load ICvar interface!", "PCS", 0);
		ExitThread(1);
	}
	
	g_ICvar->ConsolePrintf
	(
		"\n"
		"***********************************\n"
		"*** PrivateCvarScripting Loaded ***\n"
		"***********************************\n"
		"\n"
	);

	/*dump offsets for LHK*/
	g_ICvar->ConsolePrintf("IVEngineCleint->WorldToScreenMatrix() = 0x%08X\n",
		(DWORD)&g_IVEngineCleint->WorldToScreenMatrix());
	/*dump offsets for LHK*/

	lua_State *l = 0;
	l = lua_open();
	luaL_openlibs(l);
	CVARglobals(l);
	CVARregister(l);

	char *RootPath = (char*)GlobalAlloc(GMEM_ZEROINIT, MAX_PATH);
	ExpandEnvironmentStringsA("%SystemDrive%\\PCS", RootPath, MAX_PATH);
	char *OldPath = (char*)GlobalAlloc(GMEM_ZEROINIT, MAX_PATH);
	GetCurrentDirectoryA(MAX_PATH, OldPath);
	SetCurrentDirectoryA(RootPath);
	GlobalFree(RootPath);
	int err = luaL_dofile(l, "__init__.lua");
	if (err == 1)
	{
		MessageBoxA(0, lua_tostring(l, -1), "PCS", MB_OK);
	}
	g_LuaState = l;
	SetCurrentDirectoryA(OldPath);
	GlobalFree(OldPath);

	lua_close(l);

	g_ICvar->ConsolePrintf
	(
		"\n"
		"***********************************\n"
		"*** PrivateCvarScripting Exited ***\n"
		"***********************************\n"
		"\n"
	);

	return 0;
}

void CVARglobals(lua_State *l)
{
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

void CVARregister(lua_State *l)
{
	LUA_REG(l, Sleep);
	LUA_REG(l, IsKeyDown);

	LUA_REG(l, WriteConsole);

	LUA_REG(l, CreateVar);
	LUA_REG(l, FindVar);
	LUA_REG(l, CreateCommand);
	LUA_REG(l, FindCommand);
	LUA_REG(l, DeleteVar);

	LUA_REG(l, GetFlags);
	LUA_REG(l, SetFlags);
	LUA_REG(l, GetName);
	LUA_REG(l, SetName);
	LUA_REG(l, GetHelpString);
	LUA_REG(l, SetHelpString);

	LUA_REG(l, CC_Dispatch);

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
}

LUA_FUNC(Sleep)
{
	DWORD ms = (DWORD)lua_tointeger(l, 1);
	Sleep(ms);
	return 0;
}
LUA_FUNC(IsKeyDown)
{
	DWORD key = (DWORD)lua_tointeger(l, 1);
	BOOL keydown = 0;
	if (GetAsyncKeyState(key) & 0x8000) keydown = 1;
	lua_pushboolean(l, keydown);
	return 1;
}

LUA_FUNC(WriteConsole)
{
	if (g_ICvar == 0) return 0;
	if (lua_gettop(l) == 0) return 0;

	int numargs = lua_gettop(l), i = 0;
	for (i = 0; i < numargs; i++)
	{
		char *str = (char*)lua_tostring(l, i + 1);
		g_ICvar->ConsolePrintf(str);
	}

	return 0;
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
	if ((ccmd == 0) || (g_LuaState == 0)) return;
	lua_pushstring(g_LuaState, "CommandCallback");
	lua_pushlightuserdata(g_LuaState, (void*)ccmd);
	if (lua_pcall(g_LuaState, 1, 0, 0) != 0)
	{
		if (g_ICvar == 0) return;
		g_ICvar->ConsolePrintf("[PCS] Failed to call CommandCallback");
		return;
	}
}

LUA_FUNC(CreateVar)
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
LUA_FUNC(FindVar)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	const char *varname = lua_tostring(l, 1);
	ConVar *cv = g_ICvar->FindVar(varname);
	if (cv != 0) lua_pushlightuserdata(l, (PVOID)cv);
	else lua_pushnil(l);
	return 1;
}
LUA_FUNC(CreateCommand)
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
LUA_FUNC(FindCommand)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	const char *cmdname = lua_tostring(l, 1);
	ConCommand *cc = g_ICvar->FindCommand(cmdname);
	if (cc == 0) { lua_pushnil(l); return 1; }

	lua_pushlightuserdata(l, (PVOID)cc);
	return 1;
}
LUA_FUNC(DeleteVar)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	ConCommandBase *cb = (ConCommandBase*)lua_touserdata(l, 1);
	g_ICvar->UnregisterConCommand(cb);
	return 0;
}

LUA_FUNC(CC_Dispatch)
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

LUA_FUNC(GetFlags)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	ConCommandBase *cb = (ConCommandBase*)lua_touserdata(l, 1);
	if (cb == 0) { lua_pushnil(l); return 1; }

	lua_pushnumber(l, cb->m_nFlags);
	return 1;
}
LUA_FUNC(SetFlags)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 2) { lua_pushnil(l); return 1; }
	ConCommandBase *cb = (ConCommandBase*)lua_touserdata(l, 1);
	if (cb == 0) { lua_pushnil(l); return 1; }

	int newflags = (int)lua_tointeger(l, 2);
	cb->m_nFlags = newflags;

	return 0;
}
LUA_FUNC(GetName)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	ConCommandBase *cb = (ConCommandBase*)lua_touserdata(l, 1);
	if (cb == 0) { lua_pushnil(l); return 1; }

	lua_pushstring(l, cb->m_pszName);
	return 1;
}
LUA_FUNC(SetName)
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
LUA_FUNC(GetHelpString)
{
	if (g_ICvar == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 1) { lua_pushnil(l); return 1; }
	ConCommandBase *cb = (ConCommandBase*)lua_touserdata(l, 1);
	if (cb == 0) { lua_pushnil(l); return 1; }

	lua_pushstring(l, cb->m_pszHelpString);
	return 1;
}
LUA_FUNC(SetHelpString)
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

LUA_FUNC(NC_GetNetChannel)
{
	if (g_IVEngineCleint == 0) { lua_pushnil(l); return 1; }
	INetChannel *nc = (INetChannel*)g_IVEngineCleint->GetNetChannelInfo();
	lua_pushlightuserdata(l, nc);
	return 1;
}
LUA_FUNC(NC_RequestFile)
{
	if (g_IVEngineCleint == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 2) { lua_pushnil(l); return 1; }
	INetChannel *nc = (INetChannel*)lua_touserdata(l, 1);
	if (nc == 0) { lua_pushnil(l); return 1; }

	const char *str = lua_tostring(l, 2);
	int res = nc->RequestFile(str);
	lua_pushinteger(l, res);

	return 1;
}
LUA_FUNC(NC_SendFile)
{
	if (g_IVEngineCleint == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 2) { lua_pushnil(l); return 1; }
	INetChannel *nc = (INetChannel*)lua_touserdata(l, 1);
	if (nc == 0) { lua_pushnil(l); return 1; }

	const char *str = lua_tostring(l, 2);
	bool res = nc->SendFile(str, 1);
	lua_pushboolean(l, res);

	return 1;
}
LUA_FUNC(NC_SetFileTransmissionMode)
{
	if (g_IVEngineCleint == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 2) { lua_pushnil(l); return 1; }
	INetChannel *nc = (INetChannel*)lua_touserdata(l, 1);
	if (nc == 0) { lua_pushnil(l); return 1; }

	bool mode = lua_toboolean(l, 2);
	nc->SetFileTransmissionMode(mode);

	return 0;
}
LUA_FUNC(NC_SetCompressionMode)
{
	if (g_IVEngineCleint == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 2) { lua_pushnil(l); return 1; }
	INetChannel *nc = (INetChannel*)lua_touserdata(l, 1);
	if (nc == 0) { lua_pushnil(l); return 1; }

	bool mode = lua_toboolean(l, 2);
	nc->SetCompressionMode(mode);

	return 1;
}
LUA_FUNC(NC_SetRemoteFramerate)
{
	if (g_IVEngineCleint == 0) { lua_pushnil(l); return 1; }
	if (lua_gettop(l) != 3) { lua_pushnil(l); return 1; }
	INetChannel *nc = (INetChannel*)lua_touserdata(l, 1);
	if (nc == 0) { lua_pushnil(l); return 1; }

	float frametime = lua_tonumber(l, 2);
	float stddeviation = lua_tonumber(l, 3);
	nc->SetRemoteFramerate(frametime, stddeviation);

	return 1;
}

CON_COMMAND(NC_SetRemoteFramerate, "call INetChannel::SetRemoteFramerate\nfirst arg: FrameTime, second arg FrameTimeStdDeviation")
{
	if (g_ICvar == 0) return;
	if (g_IVEngineCleint == 0) return;
	if (!g_IVEngineCleint->IsInGame()) return;
	INetChannel *nc = (INetChannel*)g_IVEngineCleint->GetNetChannelInfo();
	float frametime = (float)atof(args.Arg(1));
	float stddeviation = (float)atof(args.Arg(2));
	g_ICvar->ConsolePrintf("Calling INetChannel::SetRemoteFramerate(%f,%f)...\n", frametime, stddeviation);
	nc->SetRemoteFramerate(frametime, stddeviation);
}
CON_COMMAND(NC_SendFile, "call INetChannel::SendFile\nfirst arg: File Path")
{
	if (g_ICvar == 0) return;
	if (g_IVEngineCleint == 0) return;
	if (!g_IVEngineCleint->IsInGame()) return;
	INetChannel *nc = (INetChannel*)g_IVEngineCleint->GetNetChannelInfo();
	const char *str = args.Arg(1);
	g_ICvar->ConsolePrintf("Calling INetChannel::SendFile(%s,1)...\n", str);
	bool res = nc->SendFile(str, 1);
	g_ICvar->ConsolePrintf("\tReturned: %s\n", (res) ? "TRUE" : "FALSE");
}

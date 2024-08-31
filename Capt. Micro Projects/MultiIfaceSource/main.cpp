#include "main.h"

lua_State *g_LuaState;

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DWORD dwThreadId = 0;
		HANDLE hThread = CreateThread(0, 0,
			MultiFaceSource, 0, 0, &dwThreadId);
	}
	return TRUE;
}

DWORD WINAPI MultiFaceSource(LPVOID lpParam)
{
	lua_State *l = 0;
	l = lua_open();
	luaL_openlibs(l);
	
	lwin_import(l);
	lconvar_import(l);
	lentlist_import(l);
	lcliententity_import(l);

	char *RootPath = (char*)GlobalAlloc(GMEM_ZEROINIT, MAX_PATH);
	ExpandEnvironmentStringsA("%SystemDrive%\\MIS\\luascripts", RootPath, MAX_PATH);
	char *OldPath = (char*)GlobalAlloc(GMEM_ZEROINIT, MAX_PATH);
	GetCurrentDirectoryA(MAX_PATH, OldPath);
	SetCurrentDirectoryA(RootPath);
	GlobalFree(RootPath);
	int err = luaL_dofile(l, "__keys__.lua");
	int err = luaL_dofile(l, "__init__.lua");
	if (err == 1)
	{
		MessageBoxA(0, lua_tostring(l, -1), "MultiIfaceSource", MB_OK);
	}
	g_LuaState = l;

	while (!GetAsyncKeyState(VK_PAUSE)) Sleep(50);

	SetCurrentDirectoryA(OldPath);
	GlobalFree(OldPath);
	lua_close(l);
	return 0;
}

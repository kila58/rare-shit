#include "main.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	AllocConsole();
	SetConsoleTitleA("Lua Hack Kit");
	
	char b0mbrd[] = "---------------------------------------\n"
					"--- bombTECH Research & Development ---\n"
					"--- the best tools, hacks, and mods ---\n"
					"---------------------------------------\n"
					" Lua Hack Kit [VER 1.6] by Capt. Micro \n"
					"\n";
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwBytesWriteen = 0;
	WriteFile(hstdout, b0mbrd, lstrlenA(b0mbrd), &dwBytesWriteen, NULL);

	lua_State *l;
	l = lua_open();
	luaL_openlibs(l);

	l_win_globals(l);
	l_fann_globals(l);
	l_lhkpubdrv_globals(l);
	l_threads_register(l);

	l_win_register(l);
	l_fann_register(l);
	l_lhkpubdrv_register(l);
	l_threads_register(l);

	int err = 1;
	/*if (lstrlenA(lpCmdLine) == 0)
		err = luaL_dofile(l, "__init__.lua");
	else err = luaL_dofile(l, lpCmdLine);*/

	err = luaL_dofile(l, "__init__.lua");
	
	if (err == 1)
	{
		MessageBoxA(0, lua_tostring(l, -1), "LHK Error!", MB_OK);
	}
	lua_close(l);

	l_lhkpubdrv_unregister(l);
	ExitProcess(0);
	return 0;
}

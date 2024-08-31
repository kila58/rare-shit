#include "l_threads.h"

#include "l_win.h"
#include "l_fann.h"
#include "l_lhkpubdrv.h"

void l_threads_register(lua_State *l)
{
	LUA_REG(l, ThreadCreate);
	LUA_REG(l, ThreadResume);
	LUA_REG(l, ThreadSuspend);
	LUA_REG(l, ThreadTerminate);
	LUA_REG(l, ThreadGetExitCode);
}

void l_threads_globals(lua_State *l)
{
	
}

DWORD WINAPI l_thread_fn(LPVOID param)
{
	L_THREAD_PARAMS *ltp = (L_THREAD_PARAMS*)param;
	if (ltp == 0) return 1;
	
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

	int err = luaL_dofile(l, ltp->luafile);
	if (err == 1)
	{
		MessageBoxA(0, lua_tostring(l, -1), "LHK Error!", MB_OK);
	}
	lua_close(l);

	l_lhkpubdrv_unregister(l);
	ExitThread(0);
}

LUA_FUNC(ThreadCreate)
{
	char *luafile = (char*)lua_tostring(l, 1);

	L_THREAD_PARAMS ltp;
	memset(&ltp, 0, sizeof(L_THREAD_PARAMS));
	lstrcpyA(ltp.luafile, luafile);

	DWORD dwThreadId = 0;
	HANDLE hThread = CreateThread(0, 0, l_thread_fn,
		(LPVOID)&ltp, CREATE_SUSPENDED, &dwThreadId);

	lua_pushinteger(l, (lua_Integer)hThread);
	return 1;
}

LUA_FUNC(ThreadResume)
{
	HANDLE hThread = (HANDLE)lua_tointeger(l, 1);

	DWORD dwPrevSuspendCount = ResumeThread(hThread);

	lua_pushinteger(l, (lua_Integer)dwPrevSuspendCount);
	return 1;
}

LUA_FUNC(ThreadSuspend)
{
	HANDLE hThread = (HANDLE)lua_tointeger(l, 1);

	DWORD dwPrevSuspendCount = SuspendThread(hThread);

	lua_pushinteger(l, (lua_Integer)dwPrevSuspendCount);
	return 1;
}

LUA_FUNC(ThreadTerminate)
{
	HANDLE hThread = (HANDLE)lua_tointeger(l, 1);
	DWORD dwExitCode = (DWORD)lua_tointeger(l, 2);

	BOOL success = TerminateThread(hThread, dwExitCode);

	lua_pushinteger(l, (lua_Integer)success);
	return 1;
}

LUA_FUNC(ThreadGetExitCode)
{
	HANDLE hThread = (HANDLE)lua_tointeger(l, 1);

	DWORD dwExitCode = 0;
	GetExitCodeThread(hThread, &dwExitCode);

	lua_pushinteger(l, (lua_Integer)dwExitCode);
	return 1;
}
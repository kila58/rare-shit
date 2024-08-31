#ifndef _l_threads_h_
#define _l_threads_h_

#include "winlite.h"

typedef struct {
	char luafile[MAX_PATH];
} L_THREAD_PARAMS;

void l_threads_register(lua_State *l);
void l_threads_globals(lua_State *l);

LUA_FUNC(ThreadCreate);
LUA_FUNC(ThreadResume);
LUA_FUNC(ThreadSuspend);
LUA_FUNC(ThreadTerminate);
LUA_FUNC(ThreadGetExitCode);

#endif

#include "CLuaInterface.h"
#include "CLuaShared.h"

cLuaShared *g_pLuaShared = NULL; // null ptr to luashared virtual method table
VT::CLuaInterface *g_pLuaInterface = NULL; // null ptr to luainterface vmt

typedef void *(__stdcall *CreateLuaInterfaceFn)(unsigned char, bool);
CreateLuaInterfaceFn oCreateLuaInterface;

typedef void *(__stdcall *RunStringFn)(const char *, const char*, const char*, bool, bool);
RunStringFn oRunString;


typedef void(__stdcall* RunString)(char const*, char const*, char const*, bool, bool);
RunString Original_RunString;




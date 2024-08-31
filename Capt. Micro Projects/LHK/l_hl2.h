#ifndef _l_hl2_h_
#define _l_hl2_h_

#include "winlite.h"

/* BASE SOURCESDK/ */
#include <public/tier1/interface.h>
#include <public/cdll_int.h>
#include <public/icliententitylist.h>
#include <public/iprediction.h>
#include <public/igameevents.h>
#include <public/ivrenderview.h>
#include <public/ienginevgui.h>
#include <public/iefx.h>
#include <public/filesystem.h>
#include <public/icvar.h>
#include <public/istudiorender.h>
#include <public/vphysics_interface.h>
#include <public/engine/ivmodelinfo.h>
#include <public/engine/ivdebugoverlay.h>
#include <public/engine/IEngineTrace.h>
#include <public/engine/ivmodelrender.h>
#include <public/engine/IEngineSound.h>
#include <public/vgui/ISurface.h>
#include <public/vgui/IPanel.h>
#include <public/vgui/IVGui.h>
#include <public/materialsystem/imaterialsystem.h>

void l_hl2_register(lua_State *l);
void l_hl2_globals(lua_State *l);

typedef HMODULE (WINAPI *_LoadLibraryA)(char *lpFileName);
typedef FARPROC (WINAPI *_GetProcAddress)(HMODULE hModule, char *lpProcName);
typedef VOID (WINAPI *_Sleep)(DWORD dwMilliseconds);

#define HL2_MAX_PKT_SZ 1024

typedef struct {
	DWORD dwCommandCode;
	BYTE bData[HL2_MAX_PKT_SZ];
	DWORD dwDataLen;
	DWORD dwReturnCode;
} HL2INJPKT;

typedef struct {
	_LoadLibraryA LoadLibraryA;
	_GetProcAddress GetProcAddress;
	_Sleep Sleep;
	HL2INJPKT *PKT;
} HL2INJDAT;

DWORD WINAPI IVEngineClient_CodeCave(LPVOID param);
LUA_FUNC(HL2_IVEngineClient_Init);
LUA_FUNC(HL2_IVEngineClient_ConCmd);

#endif

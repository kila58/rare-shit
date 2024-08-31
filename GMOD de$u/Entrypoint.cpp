#include "Entrypoint.h"
#include "WriteUserCmdDelta.h"
#include <stdio.h>
#include <minwindef.h>
#include <fileapi.h>
#include <stdarg.h>


PseudoRandomFn PseudoRandom;
MsgFn Msg;
RandomSeedFn RandomSeed;
RandomFloatFn RandomFloat;

void InitHook()
{
	HookVirtual(*(dword**)cl.mode,(dword*)&HookedCreateMove,21);
	GetContents = (GetContentsFn)HookVirtual(*(dword**)cl.trace, (dword*)&HookedGetContents, 0);
	PaintTraverse = (PaintTraverseFn)HookVirtual(*(dword**)cl.panel,(dword*)&HookedPaintTraverse,41);
}

void InitThread()
{
	cl.clientbase = (dword)GetModuleHandleA("client.dll");
	cl.enginebase = (dword)GetModuleHandleA("engine.dll");
	FactoryFn client = GetFactory((HMODULE)cl.clientbase);
	FactoryFn engine = GetFactory((HMODULE)cl.enginebase);
	FactoryFn vgui = GetFactory(GetModuleHandleA("vgui2.dll"));
	FactoryFn surface = GetFactory(GetModuleHandleA("vguimatsurface.dll"));
	FactoryFn material = GetFactory(GetModuleHandleA("materialsystem.dll"));
	cl.base = QueryInterface("VClient",client);
	cl.ents = (ClientEntityList*)QueryInterface("VClientEntityList",client);
	cl.pred = QueryInterface("VClientPrediction",client);
	cl.engine = (BaseEngine*)QueryInterface("VEngineClient",engine);
	cl.mdl = (EngineModel*)QueryInterface("VModelInfoClient",engine);
	cl.trace = (EngineTrace*)QueryInterface("EngineTraceClient",engine);
	cl.panel = QueryInterface("VGUI_Panel",vgui);
	cl.vgui = (EngineVGUI*)QueryInterface("VEngineVGui",engine);
	cl.surface = (GameSurface*)QueryInterface("VGUI_Surface",surface);
	cl.mode = **(void***)((*(dword**)cl.base)[10] + 5);
	HMODULE vst = GetModuleHandleA("vstdlib.dll");
	RandomSeed = (RandomSeedFn)GetProcAddress(vst,"RandomSeed");
	RandomFloat = (RandomFloatFn)GetProcAddress(vst,"RandomFloat");
	Msg = (MsgFn)GetProcAddress(GetModuleHandleA("tier0.dll"),"Msg");// becuase fuck red
	Msg("!de$u!\n");
	InitHook();
}





bool DLLInit(int,dword CallReason,int)
{
	if (CallReason == 1)
		CreateThread(0,0,(PTHREAD_START_ROUTINE)InitThread,0,0,0);
	return true;
}
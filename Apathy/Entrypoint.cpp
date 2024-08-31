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
	//HookVirtual(*(dword**)cl.input, (dword*)&HookedGetUserCmd, 8);
	//HookVirtual(*(dword**)cl.input, (dword*)&HookedWriteUsercmdDeltaToBuffer, 23);
	//HookVirtual(*(dword**)cl.mode,(dword*)&HookedCreateMove,21);
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
	cl.input = **(void***)((*(dword**)cl.base)[14] + 0x2);
	cl.mode = *(void**)(cl.clientbase + 0x6B7384);
	HMODULE vst = GetModuleHandleA("vstdlib.dll");
	RandomSeed = (RandomSeedFn)GetProcAddress(vst,"RandomSeed");
	RandomFloat = (RandomFloatFn)GetProcAddress(vst,"RandomFloat");
	//Msg = (MsgFn)GetProcAddress(GetModuleHandleA("tier0.dll"),"Warning");
	PseudoRandom = (PseudoRandomFn)(cl.clientbase + 0x383D40);
	//Msg("!Apathy!\n");
	InitHook();
}





bool DLLInit(int,dword CallReason,int)
{
	if (CallReason == 1)
		CreateThread(0,0,(PTHREAD_START_ROUTINE)InitThread,0,0,0);
	return true;
}
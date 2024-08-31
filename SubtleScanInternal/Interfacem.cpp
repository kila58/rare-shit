#include "Interfacem.h"
IBaseClientDLL *Client;
EngineClientNew *Engine;
IClientEntityList *ClientEntList;
CInputNew *Input;
 CreateInterfaceFn					ClientFactory;
 ISurfaceNew *Surface;
 vgui::IPanel					*VPanel;
 IStudioRender *StudioRender;
 IVDebugOverlay *DebugOverlay;
 IVModelRender *ModelRender;
 IEngineTrace *Trace;
 ICvar *Cvar;
 IVModelInfo2 *ModelInfo;
 CGlobalVarsBaseNew *Globals;
#define INTERFACEVERSION_PLAYERINFOMANAGER			"PlayerInfoManager002"
 abstract_class IPlayerInfoManager
 {
 public:
	 virtual void *GetPlayerInfo(edict_t *pEdict) = 0;
	 
	 virtual CGlobalVars *GetGlobalVars() = 0;
 };
void CInterface::GetInterfaces()
{
	CreateInterfaceFn					MaterialFactory = NULL;
	CreateInterfaceFn					EngineFactory = NULL;
	CreateInterfaceFn					FileFactory = NULL;
	CreateInterfaceFn					StudioFactory = NULL;
	CreateInterfaceFn					PhysicsFactory = NULL;
	CreateInterfaceFn					VGUIFactory = NULL;
	CreateInterfaceFn					VGUIMatFactory = NULL;
	CreateInterfaceFn					SteamClientFactory = NULL;
	CreateInterfaceFn					InputFactory = NULL;
	CreateInterfaceFn					VStdFactory = NULL;
	CreateInterfaceFn					ServerFactory = NULL;

	ClientFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("client.dll"), "CreateInterface");
	EngineFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface");
	PhysicsFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("vphysics.dll"), "CreateInterface");
	StudioFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("StudioRender.dll"), "CreateInterface");
	MaterialFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("MaterialSystem.dll"), "CreateInterface");
	VGUIFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("vguimatsurface.dll"), "CreateInterface");
	VGUIMatFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("vgui2.dll"), "CreateInterface");
	InputFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("inputsystem.dll"), "CreateInterface");
	VStdFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("vstdlib.dll"), "CreateInterface");
	ServerFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandle("server.dll"), "CreateInterface");

	Client = (IBaseClientDLL*)GetPointer(ClientFactory, "VClient");
	Engine = (EngineClientNew*)GetPointer(EngineFactory, "VEngineClient");
	ClientEntList = (IClientEntityList*)GetPointer(ClientFactory, "VClientEntityList");
	//EngineTrace = (IEngineTrace*)GetPointer(EngineFactory, "EngineTraceClient");
	Surface = (ISurfaceNew*)GetPointer(VGUIFactory, "VGUI_Surface");
	VPanel = (IPanel*)VGUIMatFactory("VGUI_Panel009", 0);
	Input = *(CInputNew**)((*(DWORD**)Client)[15] + 0x1); //21 + 0x5F
	std::cout << std::hex << Input << std::endl;
	DebugOverlay = (IVDebugOverlay*)EngineFactory("VDebugOverlay004", 0);
	Cvar = (ICvar*)EngineFactory("VEngineCvar007", 0);
	Trace = (IEngineTrace*)EngineFactory("EngineTraceClient004", 0);
	ModelInfo = (IVModelInfo2*)GetPointer(EngineFactory, "VModelInfoClient");
	//http://www.unknowncheats.me/forum/960874-post340.html
	Globals = (CGlobalVarsBaseNew*)((DWORD)GetModuleHandle("engine.dll") + 0x5C6E40);
	std::cout << std::hex << Globals << std::endl;
	ModelRender = (IVModelRender*)GetPointer(EngineFactory, "VEngineModel");
}
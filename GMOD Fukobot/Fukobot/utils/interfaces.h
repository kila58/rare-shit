/*
	Credits to vechook for the bruteforcer.
*/

bool DataCompare(const BYTE* pData, const BYTE* bMask, const char* pszMask)
{
	for (; *pszMask; ++pszMask, ++pData, ++bMask)
		if (*pszMask == 'x' && *pData != *bMask)
			return false;
	return (*pszMask) == 0;
}

DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char * pszMask)
{
	for (DWORD i = 0; i < dwLen; i++)
		if (DataCompare((BYTE*)(dwAddress + i), bMask, pszMask))
			return (DWORD)(dwAddress + i);

	return 0;
}

class interfaces{
public:
	void GetInterfaces();
	void* GetPointer(CreateInterfaceFn, const char*);
	CreateInterfaceFn CreateInterface(const char*);

}; interfaces Interfaces;

CreateInterfaceFn					MaterialFactory			= NULL;
CreateInterfaceFn					EngineFactory			= NULL;
CreateInterfaceFn					ClientFactory			= NULL;
CreateInterfaceFn					FileFactory				= NULL;
CreateInterfaceFn					StudioFactory			= NULL;
CreateInterfaceFn					PhysicsFactory			= NULL;
CreateInterfaceFn					VGUIFactory				= NULL;
CreateInterfaceFn					VGUIMatFactory			= NULL;
CreateInterfaceFn					SteamClientFactory		= NULL;
CreateInterfaceFn					InputFactory			= NULL;
CreateInterfaceFn					VStdFactory				= NULL;
CreateInterfaceFn					LuaFactory				= NULL;

extern IMaterialSystem				*Material				= NULL;
extern IClientEntityList			*ClientEntList			= NULL;
extern IVEngineClient				*Engine					= NULL;
extern IFileSystem					*FileSystem				= NULL;
extern ICvar						*Cvar					= NULL;
extern IBaseClientDLL				*Client					= NULL;
extern IClientDLLSharedAppSystems	*ClientInterfaces		= NULL;
extern IPrediction					*Prediction				= NULL;
extern IEngineSound					*Sound					= NULL;
extern IGameEvent					*GameEventManager		= NULL;
extern IVModelRender				*ModelRender			= NULL;
extern IVRenderView					*RenderView				= NULL;
extern IEngineTrace					*EngineTrace			= NULL;
extern IEngineVGui					*EngineVGui				= NULL;
extern IVEfx						*Effects				= NULL;
extern IVModelInfoClient			*ModelInfo				= NULL;
extern IVDebugOverlay				*DebugOverlay			= NULL;
extern IStudioRender				*Studio					= NULL;
extern IPhysics						*Physics				= NULL;
extern IPhysicsSurfaceProps			*PhysicsSurfaceProps	= NULL;
extern vgui::ISurface				*Surface				= NULL;
extern vgui::IPanel					*VPanel					= NULL;
extern IUniformRandomStream			*Random					= NULL;
extern CGlobalVarsBase				*Globals				= NULL;
extern CInput						*Input					= NULL;
extern INetChannelInfo				*Net					= NULL;
extern CLuaShared					*LuaShared				= NULL;
void								*ClientMode				= NULL;

CreateInterfaceFn interfaces::CreateInterface(const char *pszModule)
{
	HMODULE hCreateInterface = GetModuleHandle(pszModule);

	return((CreateInterfaceFn)GetProcAddress(hCreateInterface, "CreateInterface"));
}

void *interfaces::GetPointer(CreateInterfaceFn Factory, const char *pszInterface)
{
	char szPossibleInterface[1024];

	void *m_pInterface = NULL;

	for (int i = 1; i < 100; i++)
	{
		if (i < 10)
		{
			sprintf(szPossibleInterface, "%s00%i", pszInterface, i);
		}

		if (i > 9)
		{
			sprintf(szPossibleInterface, "%s0%i", pszInterface, i);
		}

		m_pInterface = (void*)Factory(szPossibleInterface, 0);

		if (m_pInterface != NULL)
		{
			ConColorMsg(ColorFg, "[Fukobot] ");
			ConColorMsg(Color(200, 200, 200, 255), "Found: %s! \n", szPossibleInterface);
			break;
		}
	}

	return(m_pInterface);
}

void interfaces::GetInterfaces(){

	ClientFactory				= (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("client.dll"), "CreateInterface");
	EngineFactory				= (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface");
	PhysicsFactory				= (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("vphysics.dll"), "CreateInterface");
	StudioFactory				= (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("StudioRender.dll"), "CreateInterface");
	MaterialFactory				= (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("MaterialSystem.dll"), "CreateInterface");
	VGUIFactory					= (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("vguimatsurface.dll"), "CreateInterface");
	VGUIMatFactory				= (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("vgui2.dll"), "CreateInterface");
	InputFactory				= (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("inputsystem.dll"), "CreateInterface");
	VStdFactory					= (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("vstdlib.dll"), "CreateInterface");
	LuaFactory					= (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("lua_shared.dll"), "CreateInterface");

	//CLuaShared*	LUASHARED		= (CLuaShared*)LuaFactory("LUASHARED003", NULL);

	Material					= (IMaterialSystem*)GetPointer(MaterialFactory, "VMaterialSystem");
	Studio						= (IStudioRender*)GetPointer(StudioFactory, "VStudioRender");
	PhysicsSurfaceProps			= (IPhysicsSurfaceProps*)GetPointer(PhysicsFactory, "VPhysicsSurfaceProps");
	Surface						= (ISurface*)GetPointer(VGUIFactory, "VGUI_Surface");
	Engine						= (IVEngineClient*)GetPointer(EngineFactory, "VEngineClient");
	Random						= (IUniformRandomStream*)GetPointer(EngineFactory, "VEngineRandom");
	Sound						= (IEngineSound*)GetPointer(EngineFactory, "IEngineSoundClient");
	GameEventManager			= (IGameEvent*)GetPointer(EngineFactory, "GAMEEVENTSMANAGER");
	ModelRender					= (IVModelRender*)GetPointer(EngineFactory, "VEngineModel");
	RenderView					= (IVRenderView*)GetPointer(EngineFactory, "VEngineRenderView");
	EngineTrace					= (IEngineTrace*)GetPointer(EngineFactory, "EngineTraceClient");
	EngineVGui					= (IEngineVGui*)GetPointer(EngineFactory, "VEngineVGui");
	Effects						= (IVEfx*)GetPointer(EngineFactory, "VEngineEffects");
	ModelInfo					= (IVModelInfoClient*)GetPointer(EngineFactory, "VModelInfoClient");
	DebugOverlay				= (IVDebugOverlay*)GetPointer(EngineFactory, "VDebugOverlay");
	ClientEntList				= (IClientEntityList*)GetPointer(ClientFactory, "VClientEntityList");
	ClientInterfaces			= (IClientDLLSharedAppSystems*)GetPointer(ClientFactory, "VClientDllSharedAppSystems");
	Prediction					= (IPrediction*)GetPointer(ClientFactory, "VClientEntityList");
	Client						= (IBaseClientDLL*)GetPointer(ClientFactory, "VClient");
	VPanel						= (IPanel*)GetPointer(VGUIMatFactory, "VGUI_Panel");
	LuaShared					= (CLuaShared*)GetPointer(LuaFactory, "LUASHARED");
	Input						= **(CInput***)((*(DWORD**)Client)[14] + 0x2); // Thank you d3x
	ClientMode					= *(void **)((DWORD)GetModuleHandleA("client.dll") + 0x6C5B64); //0x6C5B64); // Thank you d3x OLD=0x6C6AC4

}
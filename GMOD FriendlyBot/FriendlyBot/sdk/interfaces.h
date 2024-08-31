typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);


class CInterfaceManager
{
private:
	void* GetPointer( const char*, const char* );
public:

	void Initialize();

	IMaterialSystem*			Material			 = NULL;
	IClientEntityList*			ClientEntList		 = NULL;
	IVEngineClient*				Engine				 = NULL;
	IFileSystem*				FileSystem			 = NULL;
	ICvar*						Cvar				 = NULL;
	IBaseClientDLL*				Client				 = NULL;
	IClientDLLSharedAppSystems* ClientInterfaces	 = NULL;
	IPrediction*				Prediction			 = NULL;
	IEngineSound*				Sound				 = NULL;
	IGameEvent*					GameEventManager	 = NULL;
	IVModelRender*				ModelRender			 = NULL;
	IVRenderView*				RenderView			 = NULL;
	IEngineTrace*				EngineTrace			 = NULL;
	IEngineVGui*				EngineVGui			 = NULL;
	IVEfx*						Effects				 = NULL;
	IVModelInfoClient*			ModelInfo			 = NULL;
	IVDebugOverlay*				DebugOverlay		 = NULL;
	IStudioRender*				Studio				 = NULL;
	IPhysics*					Physics				 = NULL;
	IPhysicsSurfaceProps*		PhysicsSurfaceProps	 = NULL;
	CSurface*					Surface				 = NULL;
	IPanel*						Panel				 = NULL;
	IUniformRandomStream*		Random				 = NULL;
	CGlobalVarsBase*			Globals				 = NULL;
	CInput*						Input				 = NULL;
	INetChannelInfo*			Net					 = NULL;
	void*						ClientMode			 = NULL;


}; CInterfaceManager InterfaceManager;


void* CInterfaceManager::GetPointer(const char* ModuleName, const char* InterfaceName)
{
	void* Interface = NULL;
	char PossibleInterfaceName[1024];

	CreateInterfaceFn CreateInterface = (CreateInterfaceFn)GetProcAddress( GetModuleHandleA(ModuleName), "CreateInterface" );

	for (int i = 1; i < 100; i++)
	{
		sprintf(PossibleInterfaceName, "%s0%i", InterfaceName, i);
		Interface = (void*)CreateInterface(PossibleInterfaceName, NULL);
		if (Interface != NULL) break;
		sprintf(PossibleInterfaceName, "%s00%i", InterfaceName, i);
		Interface = (void*)CreateInterface(PossibleInterfaceName, NULL);
		if (Interface != NULL) break;
	}

	Msg("%s\n", PossibleInterfaceName);

	return Interface;

}

void CInterfaceManager::Initialize()
{

	Material			= (IMaterialSystem*)GetPointer("MaterialSystem.dll", "VMaterialSystem");
	Studio				= (IStudioRender*)GetPointer("StudioRender.dll", "VStudioRender");
	Physics				= (IPhysics*)GetPointer("vphysics.dll", "VPhysics");
	PhysicsSurfaceProps = (IPhysicsSurfaceProps*)GetPointer("vphysics.dll", "VPhysicsSurfaceProps");
	Surface				= (CSurface*)GetPointer("vguimatsurface.dll", "VGUI_Surface");
	Engine				= (IVEngineClient*)GetPointer("engine.dll", "VEngineClient");
	Random				= (IUniformRandomStream*)GetPointer("engine.dll", "VEngineRandom");
	Sound				= (IEngineSound*)GetPointer("engine.dll", "IEngineSoundClient");
	GameEventManager    = (IGameEvent*)GetPointer("engine.dll", "GAMEEVENTSMANAGER");
	ModelRender			= (IVModelRender*)GetPointer("engine.dll", "VEngineModel");
	RenderView			= (IVRenderView*)GetPointer("engine.dll", "VEngineRenderView");
	EngineTrace			= (IEngineTrace*)GetPointer("engine.dll", "EngineTraceClient");
	EngineVGui			= (IEngineVGui*)GetPointer("engine.dll", "VEngineVGui");
	Effects				= (IVEfx*)GetPointer("engine.dll", "VEngineEffects");
	ModelInfo			= (IVModelInfoClient*)GetPointer("engine.dll", "VModelInfoClient");
	DebugOverlay		= (IVDebugOverlay*)GetPointer("engine.dll", "VDebugOverlay");
	ClientEntList		= (IClientEntityList*)GetPointer("client.dll", "VClientEntityList");
	ClientInterfaces	= (IClientDLLSharedAppSystems*)GetPointer("client.dll", "VClientDllSharedAppSystems");
	Prediction			= (IPrediction*)GetPointer("client.dll", "VClientEntityList");
	Client				= (IBaseClientDLL*)GetPointer("client.dll", "VClient");
	Panel				= (IPanel*)GetPointer("vgui2.dll", "VGUI_Panel");
	Cvar				= (ICvar*)GetPointer("vstdlib.dll", "VEngineCvar");
	Input				= **(CInput***)((*(DWORD**)Client)[14] + 0x2); // Thank you d3x
	ClientMode			= *(void **)((DWORD)GetModuleHandleA("client.dll") + 0x6C5B64); // thanks d3x again

}
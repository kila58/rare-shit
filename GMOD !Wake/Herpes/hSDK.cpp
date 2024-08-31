/*******************************************************
##     ## ######## ########  ########  ########  ######  
##     ## ##       ##     ## ##     ## ##       ##    ## 
##     ## ##       ##     ## ##     ## ##       ##       
######### ######   ########  ########  ######    ######  
##     ## ##       ##   ##   ##        ##             ## 
##     ## ##       ##    ##  ##        ##       ##    ## 
##     ## ######## ##     ## ##        ########  ###### 

Credits:
	ph0ne	- Helping me out on a lot of shit (hooks, nospread, offsets)
	noPE	- Calling me a dumb fuck when I dumb shit
	Xeno	- For the Zeus base
	s0beit	- His base and other help
	Chod	- A lot of help to
	fr1kin  - Creation
	NanoCat	- General help

NOTE: I recommend that you don't touch this unless you know what 
      you're doing, seriously, don't.
*********************************************************/

/* Libs */
#pragma warning( disable : 4311 )
#pragma warning( disable : 4312 )
#pragma warning( disable : 4541 )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4183 )

#pragma comment( lib, "tier0.lib" )
#pragma comment( lib, "tier1.lib" )
#pragma comment( lib, "tier2.lib" )
#pragma comment( lib, "tier3.lib" )
#pragma comment( lib, "vgui_controls.lib" )
#pragma comment( lib, "mathlib.lib" )
#pragma comment( lib, "vstdlib.lib" )

/* Includes */
#include "hSDK.h"
#include "vmthook.h"

#include "drawing.h"
#include "entity.h"
#include "Steam.h"

#include "cvars.h"

int wide, height;

#include "guibase.h"

std::vector<std::string> m_pPlayerNames;

#include "css_offsets.h"
#include "css_nospread.h"
#include "css_misc.h"
#include "css_aimbot.h"
#include "css_material.h"
#include "css_esp.h"
#include "Antileak.h"
#include "gmod_offsets.h"

#include "main.h"

#undef GetProp

/* CreateMove */

CVMTHook* gCreateMove;
DWORD dwOrgCreateMove;

//HMODULE loli;

CRC32_t GenerateCRC(CUserCmd *pCmd)
{
	CRC32_t crc;

	CRC32_Init(&crc);
	CRC32_ProcessBuffer(&crc, &pCmd->command_number, sizeof(pCmd->command_number));
	CRC32_ProcessBuffer(&crc, &pCmd->tick_count, sizeof(pCmd->tick_count));
	CRC32_ProcessBuffer(&crc, &pCmd->viewangles, sizeof(pCmd->viewangles));
	CRC32_ProcessBuffer(&crc, &pCmd->forwardmove, sizeof(pCmd->forwardmove));
	CRC32_ProcessBuffer(&crc, &pCmd->sidemove, sizeof(pCmd->sidemove));
	CRC32_ProcessBuffer(&crc, &pCmd->upmove, sizeof(pCmd->upmove));
	CRC32_ProcessBuffer(&crc, &pCmd->buttons, sizeof(pCmd->buttons));
	CRC32_ProcessBuffer(&crc, &pCmd->impulse, sizeof(pCmd->impulse));
	CRC32_ProcessBuffer(&crc, &pCmd->weaponselect, sizeof(pCmd->weaponselect));
	CRC32_ProcessBuffer(&crc, &pCmd->weaponsubtype, sizeof(pCmd->weaponsubtype));
	CRC32_ProcessBuffer(&crc, &pCmd->random_seed, sizeof(pCmd->random_seed));
	CRC32_ProcessBuffer(&crc, &pCmd->mousedx, sizeof(pCmd->mousedx));
	CRC32_ProcessBuffer(&crc, &pCmd->mousedy, sizeof(pCmd->mousedy));
	CRC32_Final(&crc);

	return crc;
}

CUserCmd *__fastcall Hooked_GetUserCmd(void *pThis, DWORD dwEDX, int sequence_number) {
	static CUserCmd* pCommands = *(CUserCmd **) ((DWORD) m_pInput + 0xC4);
	return &pCommands[sequence_number % MULTIPLAYER_BACKUP];
}

////void __stdcall new_CreateMove(int sequence_number, float input_sample_frametime, bool active)
////{
////	_asm pushad;
////	_asm
////	{
////		PUSH active
////			PUSH input_sample_frametime
////			PUSH sequence_number
////			CALL dwOrgCreateMove
////	}
////	_asm popad;
////
////	//ConMsgOn("tick\n");
////
////	void *__ebp = NULL;
////
////	_asm {
////		mov __ebp, ebp;
////	};
////
////	bool * bSendPacket = (bool *) (*(DWORD*) (__ebp) -0x1);
////	//*bSendPacket = true;
////
////
////	if (!m_pInput)
////		return;
////
////	CInput::CVerifiedUserCmd *pVerifiedCommands = *(CInput::CVerifiedUserCmd **)((DWORD) m_pInput + 0xC8);
////
////	if (!pVerifiedCommands)
////		return;
////
////	CInput::CVerifiedUserCmd *pVerified = &pVerifiedCommands[sequence_number % MULTIPLAYER_BACKUP];
////
////	if (!pVerified)
////		return;
////
////	CUserCmd *cmd = Hooked_GetUserCmd(NULL, NULL, sequence_number);
////
////
////	if (!cmd)
////		return;
////
////	if (GetLocalEntity()){
////		if (cvarAimbot == 1){
////			Aimbot(cmd);
////		}
////		if (cvarSeedNoSpread == 1){
////			static int fakeseed = 0;
////			static int ideal = MD5_PseudoRandom(142) & 255;
////			cmd->random_seed = MD5_PseudoRandom(cmd->command_number = fakeseed++);
////			int brute = 0;
////
////			for (int i = fakeseed + 1; !brute; i++)
////			if ((MD5_PseudoRandom(i) & 255) == ideal)
////				brute = i;
////
////			cmd->random_seed = MD5_PseudoRandom(cmd->command_number = fakeseed = brute) & 0x7FFFFFFF;
////		}
////		Bunnyhop(cmd);
////	}
////	pVerified->m_cmd = *cmd;
////	pVerified->m_crc = CRC32_ProcessSingleBuffer(cmd, sizeof(CUserCmd));
////}

void* nclient_mode;
typedef void(__fastcall *ClientModeCreateMoveFn)(void*, void*, float, CUserCmd*);
ClientModeCreateMoveFn cloriginalmove;
void __fastcall clientmode_createmove(void* _this, void* edx, float fInputSample, CUserCmd* cmd)
{
	if (cvarAimbot == 1)
	{
		Aimbot(cmd);	
	}
	
	
	cloriginalmove(_this, edx, fInputSample, cmd);
	Bunnyhop(cmd); 
	Autostrafe(cmd);
	
}

/*
typedef void* (__thiscall *CMatRenderContext_ReadPixelsFn)(void *_this, int x, int y, int w, int h, unsigned char *buffer, void *format);
CMatRenderContext_ReadPixelsFn orgReadPixel = 0;
CVMTHook* gReadPixel;

void *__fastcall CMatRenderContext_ReadPixels_Hook(IMatRenderContext *_this, void *, int x, int y, int w, int h, unsigned char *buffer, void *format)
{
	_this->ClearColor3ub(rand() % 256, rand() % 256, rand() % 256);
	_this->ClearBuffers(true, true);

	// TODO: Draw penis

	ConMsgOn("Someone tried to grab our screen!\n");

	return orgReadPixel(_this, x, y, w, h, buffer, format);
}
*/
/* PaintTraverse (HUD) */
typedef void(__thiscall* PaintTraverseFn)(void*, unsigned int, bool, bool);
PaintTraverseFn orgPaintTraverse = 0;
CVMTHook* gPaintTraverseHook;
void __fastcall Hooked_PaintTraverse (void* _this, void*, vgui::VPANEL vguiPanel , bool forceRepaint, bool allowForce )
{
	orgPaintTraverse(_this, vguiPanel, forceRepaint, allowForce);

	static bool font = false;
	if( !font )
	{
		FontInit();
		font = true;
	}
	

	const char* PanelName = m_pPanel->GetName( vguiPanel );
	if( !strcmp( PanelName, "OverlayPopupPanel" ) )
	{
			//LastFriendsResult = InitializeFriends();
			for( int i = 0; i <= m_pEngine->GetMaxClients(); i++ )
			{
				if (i == m_pEngine->GetLocalPlayer()) continue;
				if ( isCSS & m_pEngine->IsInGame() )
				{
					//DrawEntityESP( i );
					DrawPlayerESP( i );
					//GetSpectators( i );
					SpeedDraw();
				}
			}
		Crosshair();
		InitMenu();
		MenuDrawing();
	}
}


/* IsDrawingLoadingImage */
CVMTHook gIsDrawingLoadingImage;

bool __stdcall new_IsDrawingLoadingImage( void )
{
	gIsDrawingLoadingImage.UnHook();
	bool ret = m_pEngine->IsDrawingLoadingImage();
	gIsDrawingLoadingImage.ReHook();

	if( m_pEngine->IsInGame() )
	{
		if( GetLocalEntity() )
			SetMaterials();
	}
	return ret;
}

/* Render hook */
CVMTHook gDrawModel;

void __stdcall new_DrawModelExecute( const DrawModelState_t &pState, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld )
{
    gDrawModel.UnHook();
	const char* model = m_pModelInfo->GetModelName( pInfo.pModel );
	m_pModelRender->DrawModelExecute( pState, pInfo, pCustomBoneToWorld ); 
    gDrawModel.ReHook();
}


/* PE Headers */
bool DestroyHeaderPE( HANDLE Module )
{
	PIMAGE_DOS_HEADER pDosHeader = ( PIMAGE_DOS_HEADER ) Module;
	PIMAGE_NT_HEADERS pNtHeader = ( PIMAGE_NT_HEADERS ) ( ( DWORD ) pDosHeader + ( DWORD )pDosHeader->e_lfanew );
	DWORD Prot;

	WORD ProtSize = pNtHeader->FileHeader.SizeOfOptionalHeader;
	VirtualProtect( ( void* )Module, ProtSize, PAGE_EXECUTE_READWRITE, &Prot );
	ZeroMemory( ( void* ) Module, ProtSize );
	VirtualProtect( ( void* )Module, ProtSize, Prot, NULL );

	return true;
}


/* Load Hack */
DWORD WINAPI dwMainThread(LPVOID lpArguments)
{
	/*cAL *gAL = new cAL;
	if (!gAL->Verified()){
		//PrintMessage("Your HWID isn't in the database! Contact Kelse.\n");
		exit(0);
	}*/
	while( FindWindowA( "Valve001", NULL ) == NULL )
		Sleep( 100 );

	while( GetModuleHandleA( "engine.dll" ) == NULL || GetModuleHandleA( "client.dll" ) == NULL )
		Sleep( 100 );

	// Factories
	m_pClientFactory	= ( CreateInterfaceFn )GetProcAddress( GetModuleHandleA("client.dll"), "CreateInterface" );
	m_pEngineFactory	= ( CreateInterfaceFn )GetProcAddress( GetModuleHandleA("engine.dll"), "CreateInterface" );
	m_pPhysicsFactory	= ( CreateInterfaceFn )GetProcAddress( GetModuleHandleA("vphysics.dll"), "CreateInterface" );
	//m_pFileFactory		= ( CreateInterfaceFn )GetProcAddress( GetModuleHandleA("FileSystem_Steam.dll"), "CreateInterface" );
	m_pStudioFactory	= ( CreateInterfaceFn )GetProcAddress( GetModuleHandleA("StudioRender.dll"), "CreateInterface" );
	m_pMaterialFactory	= ( CreateInterfaceFn )GetProcAddress( GetModuleHandleA("MaterialSystem.dll"), "CreateInterface" );
	m_pVgui				= ( CreateInterfaceFn )GetProcAddress( GetModuleHandleA("vguimatsurface.dll"), "CreateInterface" );
	m_pVguiMat			= ( CreateInterfaceFn )GetProcAddress( GetModuleHandleA("vgui2.dll"), "CreateInterface" );
	m_pSteamClient		= (CreateInterfaceFn) GetProcAddress(GetModuleHandleA("steamclient.dll"), "CreateInterface");


	// Hook them
	m_pMaterialSystem		= (IMaterialSystem*)m_pMaterialFactory( "VMaterialSystem080", NULL );
	//m_pFileSystem			= (IFileSystem*)m_pFileFactory( FILESYSTEM_INTERFACE_VERSION, NULL );
	m_pStudioRender			= (IStudioRender*)m_pStudioFactory( STUDIO_RENDER_INTERFACE_VERSION, NULL );
	m_pPhysics				= (IPhysics*)m_pPhysicsFactory( VPHYSICS_INTERFACE_VERSION, NULL );
	m_pPhysicsSurfaceProps	= (IPhysicsSurfaceProps*)m_pPhysicsFactory( VPHYSICS_SURFACEPROPS_INTERFACE_VERSION, NULL );
	m_pSurface				= (vgui::ISurface*)m_pVgui( VGUI_SURFACE_INTERFACE_VERSION, NULL);
	m_pEngine				= (IVEngineClient*)m_pEngineFactory( VENGINE_CLIENT_INTERFACE_VERSION, NULL );
	m_pRandom				= (IUniformRandomStream *)m_pEngineFactory( VENGINE_SERVER_RANDOM_INTERFACE_VERSION, NULL );
	m_pSound				= (IEngineSound *)m_pEngineFactory( IENGINESOUND_CLIENT_INTERFACE_VERSION, NULL );
	m_pGameEventManager		= (IGameEvent *)m_pEngineFactory( INTERFACEVERSION_GAMEEVENTSMANAGER2, NULL );
	m_pModelRender			= (IVModelRender *)m_pEngineFactory( VENGINE_HUDMODEL_INTERFACE_VERSION, NULL );
	m_pRenderView			= (IVRenderView *)m_pEngineFactory( VENGINE_RENDERVIEW_INTERFACE_VERSION, NULL );
	m_pEngineTrace			= (IEngineTrace *)m_pEngineFactory( INTERFACEVERSION_ENGINETRACE_CLIENT, NULL );
	m_pEngineVGui			= (IEngineVGui *)m_pEngineFactory( VENGINE_VGUI_VERSION, NULL );
	m_pEffects				= (IVEfx *)m_pEngineFactory( VENGINE_EFFECTS_INTERFACE_VERSION, NULL );
	m_pModelInfo			= (IVModelInfoClient *)m_pEngineFactory( "VModelInfoClient006", NULL );
	m_pSound				= (IEngineSound *)m_pEngineFactory( IENGINESOUND_CLIENT_INTERFACE_VERSION, NULL );
	m_pDebugOverlay			= (IVDebugOverlay *)m_pEngineFactory( "VDebugOverlay003", NULL);
	m_pClientEntList		= ( IClientEntityList* )m_pClientFactory( VCLIENTENTITYLIST_INTERFACE_VERSION, NULL );
	m_pClientInterfaces		= (IClientDLLSharedAppSystems*)m_pClientFactory( CLIENT_DLL_SHARED_APPSYSTEMS, NULL );
	m_pPrediction			= (IPrediction*)m_pClientFactory( VCLIENT_PREDICTION_INTERFACE_VERSION, NULL );
	m_pClient				= (IBaseClientDLL*)m_pClientFactory( CLIENT_DLL_INTERFACE_VERSION, NULL );
	m_pPanel				= (vgui::IPanel*)m_pVguiMat( VGUI_PANEL_INTERFACE_VERSION, NULL );
	m_pClientSteam			= (ISteamClient012*) m_pSteamClient("SteamClient012", NULL);
	HSteamPipe pipe			= m_pClientSteam->CreateSteamPipe();
	HSteamUser user			= m_pClientSteam->ConnectToGlobalUser(pipe);
	m_pSteamFriends			= (ISteamFriends010*) m_pClientSteam->GetISteamFriends(user, pipe, "SteamFriends010");
	
	m_pDWClient = ( DWORD )GetModuleHandleA( "client.dll" );

	//loli = LoadLibrary("tamamo.dll");

	//((void(*)(const char *))GetProcAddress(loli, "gg"))("\x53\x8B\xDC\x83\xEC\x08\x83\xE4\xF0\x83\xC4\x04\x55\x8B\x6B\x04\x89\x6C\x24\x04\x8B\xEC\x81\xEC????\x56\x8B\x73\x08");

	if (1)
	{
		//ConnectTier1Libraries(&appSysFactory, 1);
		//ConnectTier2Libraries(&appSysFactory, 1);
		//ConnectTier3Libraries(&appSysFactory, 1);


		//m_pCVar = (ICvar *) ((CreateInterfaceFn)GetProcAddress(GetModuleHandle("vstdlib"), "CreateInterface"))("VEngineCvar004", NULL);
		//ConVar_Register(0);

		
		m_pGlobals = **(CGlobalVarsBase***) (FindPattern(**(DWORD**)m_pClient, 0x100, (BYTE*)"\x89\x0D", "xx") + 2);
	

		//ReplicateVars();
		//m_pEngine->ClientCmd("__sv_cheats 1");
		//m_pEngine->ClientCmd("__sv_consistency 0");

		m_pEngine->GetScreenSize(wide, height);

		HWND gameCSS = FindWindowA(NULL, (LPCSTR)"Counter-Strike Source");
		HWND gameGMOD = FindWindowA(NULL, (LPCSTR)"Garry's Mod");

		if (gameGMOD)
		{
			//PrintMessage((const tchar*)"Loaded for Garry's Mod!\n");
			isCSS = true;
		}
	}

	DWORD* pdwClientVMT = ( DWORD* )*( DWORD* )m_pClient;

	m_pDWClientFrameStage = pdwClientVMT[35];
	dwOrgCreateMove = pdwClientVMT[21];

	// PaintTraverse Hook
	gPaintTraverseHook = new CVMTHook((DWORD**) m_pPanel);
	orgPaintTraverse = (PaintTraverseFn)gPaintTraverseHook->HookMethod((DWORD) Hooked_PaintTraverse, 41);


	m_pInput = **(CInput***) (FindPattern( (DWORD) pdwClientVMT[21], 0x100, (BYTE *) "\x8B\x0D", "xx") + 0x02);
	//gCreateMove.Hook( ( DWORD )&new_CreateMove, ( PDWORD )m_pClient, 21 );


	

	/*gCreateMove = new CVMTHook((DWORD**) m_pClient);
	dwOrgCreateMove = gCreateMove->HookMethod((DWORD) new_CreateMove, 21);*/


	nclient_mode = *(void **)((DWORD)GetModuleHandleA("client.dll") + 0x06C9D14);
	static CVMTHook* hkclientmode_createmove_hook = new CVMTHook((DWORD**)nclient_mode);
	cloriginalmove = (ClientModeCreateMoveFn)hkclientmode_createmove_hook->HookMethod((DWORD)clientmode_createmove, 21);
	


	static CVMTHook* input = 0;
	input = new CVMTHook((DWORD**) m_pInput);
	input->HookMethod((DWORD) Hooked_GetUserCmd, 8);

	
	// TEST

	Netvars::Initialize();
	//Netvars::HookNetvar("*", "m_angEyeAngles[0]", AntiAntiAimX);
	//Netvars::HookNetvar("*", "m_nTickBase", fix_nTickBase);

	return 0;
}

/* Inject Hack */
BOOL WINAPI DllMain( HINSTANCE hInstance, DWORD dwReasonOfCall, LPVOID lpReserved )
{
	//DestroyHeaderPE( hInstance );
	if ( dwReasonOfCall == DLL_PROCESS_ATTACH )
	{
		DisableThreadLibraryCalls( (HMODULE)hInstance );
		CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)dwMainThread, NULL, 0, NULL );
	}
	TerminateThread( dwMainThread, NULL );

	return TRUE;
}
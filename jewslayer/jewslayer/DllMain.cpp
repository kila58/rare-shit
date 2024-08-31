#include "stdafx.h"
#include "Offsets.h"

// Engine hooks
#include "HudUpdate.h"
#include "KeyEvent.h"
#include "CreateMove.h"
#include "FrameStageNotify.h"
#include "PaintTraverse.h"
#include "RunCommand.h"
#include "DrawModelExecute.h"

// Hack stuff
#include "Aimbot.h"
#include "Menu.h"
#include "Misc.h"
#include "Visuals.h"
#include "GameEvents.h"

CVMTHookManager* g_pClientVMTHook = nullptr;
CVMTHookManager* g_pPredictionVMTHook = nullptr;
CVMTHookManager* g_pPanelVMTHook = nullptr;
CVMTHookManager* g_pModelRenderVMTHook = nullptr;

void AttachDebugConsole( void )
{
	if( FreeConsole( ) )
	{
		if( !AllocConsole( ) )
			return;
	}
	else if( !AllocConsole( ) )
		return;

	SetConsoleTitleA( "Jewslayer" );

	FILE* pCon = nullptr;
	freopen_s( &pCon, "CONOUT$", "w", stdout );
}

void ReleaseDebugConsole( void )
{
	FreeConsole( );

	HWND hWnd = FindWindowA( NULL, "Jewslayer" );
	if( hWnd )
	{
		DestroyWindow( hWnd );
		hWnd = NULL;
	}
}

__declspec( naked ) void __stdcall hkCreateMove( int sequence_number, float input_sample_frametime, bool active )
{
	__asm
	{
		PUSH	EBP
		MOV		EBP, ESP
		PUSH	EBX
		LEA		ECX, [ ESP ]
		PUSH	ECX
		PUSH	active
		PUSH	input_sample_frametime
		PUSH	sequence_number
		CALL	CreateMoveProxy
		POP		EBX
		POP		EBP
		RETN	0xC
	}
}

void DLL_Main_Thread( PVOID pParam )
{

	AttachDebugConsole( );
	g_pAimbot = new CAimbot( );
	g_pMenu = new CMenu( );
	g_pMisc = new CMisc( );
	g_pVisuals = new CVisuals( );
	g_pGameEvents = new CGameEvents( );
	
	InitCVars( );	

	g_pEntityList = ValveSDK::GetInterface< ValveSDK::CEntityList >( "client.dll", "VClientEntityList" );
	g_pGlobalVarsBase = ( ValveSDK::CGlobalVarsBase* )*( DWORD* )*( DWORD* )( g_pTools->FindPattern( "client.dll", ( PBYTE )"\xA1\x00\x00\x00\x00\x8B\x40\x10\x89\x41\x04", "x????xxxxxx", NULL, NULL ) + 0x1 );
	g_pGameMovement = ValveSDK::GetInterface< ValveSDK::IGameMovement >( "client.dll", "GameMovement" );
	g_pClient = ValveSDK::GetInterface< ValveSDK::CHLClient >( "client.dll", "VClient" );
	g_pPrediction = ValveSDK::GetInterface< ValveSDK::IPrediction >( "client.dll", "VClientPrediction" );
	g_pDebugOverlay = ValveSDK::GetInterface< ValveSDK::IDebugOverlay >( "engine.dll", "VDebugOverlay" );
	g_pEngine = ValveSDK::GetInterface< ValveSDK::IEngineClient >( "engine.dll", "VEngineClient" );
	g_pEngineTrace = ValveSDK::GetInterface< ValveSDK::IEngineTrace >( "engine.dll", "EngineTraceClient" );
	g_pGameEventManager = ValveSDK::GetInterface< ValveSDK::IGameEventManager2 >( "engine.dll", "GAMEEVENTSMANAGER", true );
	g_pModelInfo = ValveSDK::GetInterface< ValveSDK::IModelInfo >( "engine.dll", "VModelInfoClient" );
	g_pModelRender = ValveSDK::GetInterface< ValveSDK::IModelRender >( "engine.dll", "VEngineModel" );
	g_pRenderView = ValveSDK::GetInterface< ValveSDK::IRenderView >( "engine.dll", "VEngineRenderView" );
	g_pMaterialSystem = ValveSDK::GetInterface< ValveSDK::IMaterialSystem >( "materialsystem.dll", "VMaterialSystem" );
	g_pPhysSurface = ValveSDK::GetInterface< ValveSDK::IPhysicsSurfaceProps >( "vphysics.dll", "VPhysicsSurfaceProps" );
	g_pPanel = ValveSDK::GetInterface< ValveSDK::IPanel >( "vgui2.dll", "VGUI_Panel" );
	g_pSurface = ValveSDK::GetInterface< ValveSDK::ISurface >( "vguimatsurface.dll", "VGUI_Surface" );
	g_pRenderSurface = new ValveSDK::CRenderSurface( g_pSurface );

	PDWORD pdwClientVMT = *( PDWORD* )g_pClient;
	g_pInput = *( ValveSDK::CInput** )( pdwClientVMT[ 15 ] + 0x1 );
	g_pNetVars = new ValveSDK::CNetVars( g_pClient->GetFirstClass( ) );
	g_pTools = new ValveSDK::CTools( );

	int iScreenSize[ 2 ] = { 0 };
	g_pEngine->GetScreenSize( iScreenSize );


	if( g_pNetVars->Setup( ) )
	{
		InitOffsets( );
		Offsets::m_dwLoadFromBuffer = g_pTools->FindPattern( "client.dll", ( PBYTE )"\x55\x8B\xEC\x83\xE4\xF8\x83\xEC\x34\x53\x8B\x5D\x0C\x89", "xxxxxxxxxxxxxx", 0, 0 );

		//g_pNetVars->DumpNetVars( );

		g_pClientVMTHook = new CVMTHookManager( ( PDWORD* )g_pClient );
		g_pClientVMTHook->HookMethod( ( DWORD )hkHudUpdate, 11 );
		g_pClientVMTHook->HookMethod( ( DWORD )hkKeyEvent, 20 );
		g_pClientVMTHook->HookMethod( ( DWORD )hkCreateMove, 21 );
		g_pClientVMTHook->HookMethod( ( DWORD )hkFrameStageNotify, 36 );
		g_pClientVMTHook->ReHook( );

		g_pPanelVMTHook = new CVMTHookManager( ( PDWORD* )g_pPanel );
		g_pPanelVMTHook->HookMethod( ( DWORD )hkPaintTraverse, 41 );
		g_pPanelVMTHook->ReHook( );

		g_pPredictionVMTHook = new CVMTHookManager( ( PDWORD* )g_pPrediction );
		g_pPredictionVMTHook->HookMethod( ( DWORD )hkRunCommand, 19 );
		g_pPredictionVMTHook->ReHook( );

		g_pModelRenderVMTHook = new CVMTHookManager( ( PDWORD* )g_pModelRender );
		g_pModelRenderVMTHook->HookMethod( ( DWORD )hkDrawModelExecute, 21 );
		g_pModelRenderVMTHook->ReHook( );

		//g_pGameEvents->RegisterSelf( );
	}	
}

void Dll_Eject_Thread( LPARAM lpParam )
{
	while( !( GetKeyState( VK_END ) & 0x8000 ) )
		Sleep( 1 );

	Beep( 100, 100 );
	ReleaseDebugConsole( );

	// Delete all pointer otherwise memory leak
	SafeDelete( &g_pAimbot );
	SafeDelete( &g_pMenu );
	SafeDelete( &g_pMisc );
	SafeDelete( &g_pVisuals );
	SafeDelete( &g_pGameEvents );
	SafeDelete( &g_pNetVars );
	SafeDelete( &g_pRenderSurface );
	SafeDelete( &g_pTools );

	g_pClientVMTHook->UnHook( );
	g_pPanelVMTHook->UnHook( );
	g_pPredictionVMTHook->UnHook( );
	g_pModelRenderVMTHook->UnHook( );

	SafeDelete( &g_pClientVMTHook );
	SafeDelete( &g_pPanelVMTHook );
	SafeDelete( &g_pPredictionVMTHook );
	SafeDelete( &g_pModelRenderVMTHook );

	g_CVars.Release( );

	FreeLibraryAndExitThread( ( HMODULE )lpParam, 0 );
}

BOOL WINAPI DllMain( HMODULE hModule, DWORD dwReason, LPVOID lpReserved )
{
	
	switch( dwReason )
	{
	case DLL_PROCESS_ATTACH:
		_beginthread( DLL_Main_Thread, 0, NULL );
		CreateThread( NULL, 0, ( LPTHREAD_START_ROUTINE )Dll_Eject_Thread, hModule, 0, NULL );
		break;
	}
	return TRUE;
}
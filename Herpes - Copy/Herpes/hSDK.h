/*******************************************************
##     ## ######## ########  ########  ########  ######  
##     ## ##       ##     ## ##     ## ##       ##    ## 
##     ## ##       ##     ## ##     ## ##       ##       
######### ######   ########  ########  ######    ######  
##     ## ##       ##   ##   ##        ##             ## 
##     ## ##       ##    ##  ##        ##       ##    ## 
##     ## ######## ##     ## ##        ########  ###### 
********************************************************/

#define GAME_DLL
#define CLIENT_DLL
#define WIN32_LEAN_AND_MEAN

/* Includes */
#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <sstream>
#include <iostream>
#include <cstdio>


//#include <boost/lexical_cast.hpp>
//#include <boost/format.hpp>

#include <cdll_int.h>
#include "filesystem.h"
#include <cdll_client_int.h>
#include <mathlib\mathlib.h>
#include <iclientmode.h>
#include <iefx.h>
#include <engine\IEngineSound.h>
#include <ienginevgui.h>
#include <engine\ivdebugoverlay.h>
#include <vgui\ISurface.h>
#include <iprediction.h>
#include <igameevents.h>
#include <vgui\IVGui.h>
#include <input.h>
#include <con_nprint.h>
#include <game_controls\commandmenu.h>
#include <icvar.h>
#include <tier1.h>
#include <eiface.h>
#include <math.h>
#include <vstdlib/random.h>
#include "mathlib/vector.h"
#include <icliententity.h>
#include <icliententitylist.h>
#include <materialsystem/imaterial.h>
#include <materialsystem/imaterialsystem.h>
#include <inetchannelinfo.h>
#include <cdll_int.h>
#include <cdll_client_int.h>
#include <tier1/tier1.h>
#include <tier2/tier2.h>
#include <tier3/tier3.h>
#include <interface.h>
#include <mathlib\mathlib.h>
#include <cbase.h>

//#include <steam/isteamclient.h>
//#include <steam/isteamfriends.h>

CreateInterfaceFn m_pMaterialFactory = NULL;
CreateInterfaceFn m_pEngineFactory = NULL;
CreateInterfaceFn m_pClientFactory = NULL;
CreateInterfaceFn m_pFileFactory = NULL;
CreateInterfaceFn m_pStudioFactory = NULL;
CreateInterfaceFn m_pPhysicsFactory= NULL;
CreateInterfaceFn m_pVgui = NULL;
CreateInterfaceFn m_pVguiMat = NULL;
CreateInterfaceFn m_pSteamClient = NULL;

extern IMaterialSystem				*m_pMaterialSystem = NULL;
extern IClientEntityList			*m_pClientEntList = NULL;
extern IVEngineClient				*m_pEngine = NULL;
extern IFileSystem					*m_pFileSystem = NULL;
extern ICvar						*m_pCVar = NULL;
extern IBaseClientDLL				*m_pClient = NULL;
extern IClientDLLSharedAppSystems	*m_pClientInterfaces = NULL;
extern IPrediction					*m_pPrediction = NULL;
extern IEngineSound					*m_pSound = NULL;
extern IGameEvent					*m_pGameEventManager = NULL;
extern IVModelRender				*m_pModelRender = NULL;
extern IVRenderView					*m_pRenderView = NULL;
extern IEngineTrace					*m_pEngineTrace = NULL;
extern IEngineVGui					*m_pEngineVGui = NULL;
extern IVEfx						*m_pEffects = NULL;
extern IVModelInfoClient			*m_pModelInfo = NULL;
extern IVDebugOverlay				*m_pDebugOverlay = NULL;
extern IStudioRender				*m_pStudioRender = NULL;
extern IPhysics						*m_pPhysics = NULL;
extern IPhysicsSurfaceProps			*m_pPhysicsSurfaceProps = NULL;
extern vgui::ISurface				*m_pSurface = NULL;
extern vgui::IPanel					*m_pPanel = NULL;
extern IUniformRandomStream			*m_pRandom = NULL;
extern CGlobalVarsBase				*m_pGlobals = NULL;
extern IClientMode					*m_pClientMode = NULL;
extern CInput						*m_pInput = NULL;
extern INetChannelInfo				*m_pNet = NULL;
//extern ISteamFriends010             *m_pSteamFriends = NULL;
//extern ISteamClient012				*m_pClientSteam = NULL;
DWORD m_pFireBullets				= 0;
DWORD m_pDWClient					= 0;
DWORD m_pDWClientFrameStage			= 0;

bool DataCompare(const BYTE* pData, const BYTE* bMask, const char* pszMask)
{
	for(;*pszMask;++pszMask,++pData,++bMask)
		if(*pszMask=='x' && *pData!=*bMask ) 
			return false;
	return (*pszMask)==0;
}

DWORD FindPattern(DWORD dwAddress,DWORD dwLen,BYTE *bMask,char * pszMask)
{
	for(DWORD i=0; i < dwLen; i++)
		if( DataCompare( (BYTE*)( dwAddress+i ),bMask,pszMask ) )
			return ( DWORD )( dwAddress + i );
	
	return 0;
}

void PrintMessage( const tchar *text )
{
	static _iobuf* log = 0;
	if (!log)
	{
		log = fopen("C:/illya.txt", "w");

		//logging

	}

	ConColorMsg( Color( 0, 255, 0, 255 ), "[illya]: " );
	ConColorMsg( Color( 255, 255, 255, 255 ), text );

	fputs(text, log);
	fflush(log);
}

void NormalizeAngle(float &flAngle)
{
	while (flAngle > 180.f)
		flAngle -= 360.f;

	while (flAngle < -180.f)
		flAngle += 360.f;
}

void NormalizeAngles(QAngle &vecAngles)
{
	for (int iAxis = 0; iAxis < 3; iAxis++)
		NormalizeAngle(vecAngles[iAxis]);
}


void ConMsgOn(const tchar *text)
{
	ConColorMsg(Color(0, 255, 0, 255), "[illya]: ");
	ConColorMsg(Color(255, 255, 255, 255), text);
}
#ifndef _SDK_H_
#define _SDK_H_
#define CLIENT_DLL

#pragma warning( disable : 4311 )//disable shit error
#pragma warning( disable : 4312 )
#pragma warning( disable : 4541 )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4183 )

extern char DllPath[2048];

#define DO_ONCE( arg )				\
	static bool UnIqUe_ONC3 = false; \
if (UnIqUe_ONC3 == false)\
{									\
	UnIqUe_ONC3 = true;				\
	arg								\
}

#include <windows.h>//win32
#include <tlhelp32.h>
#include <winsock.h>
#include <algorithm>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <vector>
#include <fstream>
#include <istream>
#include <string.h>

#define SECURITY_WIN32
#define WIN32_LEAN_AND_MEAN
#pragma optimize("gsy",on)
#include <Security.h>
#include <shlwapi.h>

#include "cdll_int.h"//hack files (game sdk)
#include "iprediction.h"
#include "imessagechars.h"
#include "iclientmode.h"
#include "cliententitylist.h"
//#include "ccdll_client_int.h"
#include "cbase.h"
#include "bone_setup.h"
#include "c_baseanimating.h"
#include "c_basecombatweapon.h"
#include "c_baseplayer.h"
#include "enginesprite.h"
#include "icliententitylist.h"
#include "engine/ivmodelrender.h"
#include "engine/ivdebugoverlay.h"
#include "materialsystem/imaterialsystemstub.h"
#include "engine/ivmodelinfo.h"
#include "ienginevgui.h"
#include "networkstringtabledefs.h" //
#include "ispatialpartition.h" //
#include "engine/ishadowmgr.h" //
#include "engine/IStaticPropMgr.h" //
#include "engine/IEngineSound.h" //
#include "vgui/IClientPanel.h"
#include "vgui/IPanel.h"
#include "vgui/ISurface.h"
#include "vgui_controls/Panel.h"
#include "engine/IEngineTrace.h"
#include "IGameUIFuncs.h"
#include "VGuiMatSurface/IMatSystemSurface.h"
#include "input.h"
#include "usermessages.h"
#include "basecombatweapon_shared.h"
#include "takedamageinfo.h"
#include "dlight.h"
#include "iefx.h" 
#include "igameevents.h"
#include "materialsystem/itexture.h"
#include "materialsystem/IMaterialVar.h"
#include "vgui/ILocalize.h"
#include "view_shared.h"
#include "iviewrender.h"
#include "viewrender.h"
#include "game_controls/commandmenu.h"//ovmap
#include "istudiorender.h"
#include "hudelement.h"
//#include "IGameConsole.h"
#include "icvar.h"
#include "tier1/convar.h"
#include "inetchannelinfo.h"

#include <tchar.h>
#include "tier1/bitbuf.h"

extern char path[2048];//like dll main

//#pragma comment ( lib, "Winmm.lib")
/*#pragma comment ( lib, "SDK/ImportLibrarys/tier0.lib" )
#pragma comment ( lib, "SDK/ImportLibrarys/vstdlib.lib" )
#pragma comment ( lib, "SDK/ImportLibrarys/vgui_surfacelib.lib" )
#pragma comment ( lib, "SDK/ImportLibrarys/unitlib.lib" )
#pragma comment ( lib, "SDK/ImportLibrarys/vgui_controls.lib" )
#pragma comment ( lib, "SDK/ImportLibrarys/nvtc.lib" )
#pragma comment ( lib, "SDK/ImportLibrarys/vtf.lib" )
#pragma comment ( lib, "SDK/ImportLibrarys/unitlib.lib" )
#pragma comment ( lib, "SDK/ImportLibrarys/nvtristrip.lib" )
#pragma comment ( lib, "SDK/ImportLibrarys/appframework.lib" )
#pragma comment ( lib, "SDK/ImportLibrarys/vmpi.lib" )*/

#endif
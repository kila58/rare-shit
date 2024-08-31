// ur gay fegit
#pragma once

#ifndef CLIENT_DLL
#define CLIENT_DLL
#endif

#include <stdio.h>
#include <vector>
#include <string>
#include <time.h>
#include <iostream>
#include <sstream>
#include <windows.h>
#include <stringapiset.h>
#include <math.h>
#include <xstring>
#include <WinUser.h>
#include <stdio.h>
#include <wingdi.h>

#define SECURITY_WIN32
#define WIN32_LEAN_AND_MEAN

#include "cDrawing.h"
#include "public\\tier0\\wchartypes.h"

// Public
#include "public\\cdll_int.h"
#include "public\\iprediction.h"
#include "public\\bone_setup.h"
#include "public\\icliententitylist.h"
#include "public\\ienginevgui.h"
#include "public\\IGameUIFuncs.h"
#include "public\\dlight.h"
#include "public\\r_efx.h" 
#include "public\\igameevents.h"
#include "public\\view_shared.h"
#include "public\\inetchannelinfo.h"
#include "public\\iachievementmgr.h"
#include "public\\steam\\steam_api.h"
#include "public\\steam\\isteamuserstats.h"

// Client
#include "game\\client\\imessagechars.h"
#include "game\\client\\iclientmode.h"
#include "game\\client\\cliententitylist.h"
#include "game\\client\\cdll_client_int.h"
#include "game\\client\\cbase.h"
#include "game\\client\\c_baseanimating.h"
#include "game\\client\\c_basecombatweapon.h"
#include "game\\client\\c_baseplayer.h"
#include "game\\client\\enginesprite.h"
#include "game\\client\\input.h"
#include "game\\client\\c_playerresource.h"
#include "game\\client\\iviewrender.h"
#include "game\\client\\viewrender.h"
#include "game\\client\\game_controls\\commandmenu.h"
#include "game\\client\\hudelement.h"

// Engine
#include "public\\engine\\ivmodelrender.h"
#include "public\\engine\\ivdebugoverlay.h"
#include "public\\engine\\ivmodelinfo.h"
#include "public\\engine\\IEngineTrace.h"
#include "public\\engine\\IEngineSound.h"

// Material System
#include "public\\materialsystem\\imaterialsystemstub.h"
#include "public\\materialsystem\\itexture.h"
#include "public\\materialsystem\\IMaterialVar.h"
#include "public\\tier1\\checksum_md5.h"
#include "public\\materialsystem\\imaterial.h"
// VGUI
#include "public\\matsys_controls\\matsyscontrols.h"
#include "public\\vgui\\IClientPanel.h"
#include "public\\vgui\\IPanel.h"
#include "public\\vgui\\ISurface.h"
#include "public\\vgui\\ILocalize.h"
#include "public\\collisionutils.h"
#include "public\\vstdlib\\random.h"


// VGUI Controls
#include "public\\vgui_controls\\Panel.h"

// VGUI Material Surface
#include "public\\VGuiMatSurface\\IMatSystemSurface.h"
#include "public\\mathlib\\vector.h"
#include "C:\HL-SDK\public\public\mathlib\vector.h"

// Shared
#include "game\\shared\\usermessages.h"
#include "game\\shared\\basecombatweapon_shared.h"
#include "game\\shared\\takedamageinfo.h"
#include "game\\shared\\igamemovement.h"

#pragma comment(lib, "C:/HL-SDK/public/lib/public/tier0.lib")
#pragma comment(lib, "C:/HL-SDK/public/lib/public/tier1.lib")
#pragma comment(lib, "C:/HL-SDK/public/lib/public/tier2.lib")
#pragma comment(lib, "C:/HL-SDK/public/lib/public/tier3.lib")
#pragma comment(lib, "C:/HL-SDK/public/lib/public/mathlib.lib")
#pragma comment(lib, "C:/HL-SDK/public/lib/public/vstdlib.lib")


typedef void(__fastcall *tPaintTraverse)(void*, void*, unsigned int, bool, bool);

extern IBaseClientDLL* g_pClient;
extern vgui::ISurface* g_pSurface;
extern vgui::IPanel* g_pPanel;
extern IVEngineClient* g_pEngine;
extern IVModelInfo* g_pModelInfo;
extern IVDebugOverlay* g_pDebugOverlay;

typedef unsigned long HFont;

#define V_CLIENT_INTERFACE_VERSION "VClient017"
#define V_ENGLINE_CLIENT_INTERFACE_VERSION "VEngineClient015"

#pragma once

#define GAME_DLL
#define CLIENT_DLL

#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)  
#define IN_SPEED		(1 << 17)	
#define IN_WALK			(1 << 18)
#define IN_ZOOM			(1 << 19)	
#define IN_WEAPON1		(1 << 20)	
#define IN_WEAPON2		(1 << 21)
#define IN_BULLRUSH		(1 << 22)

// Some libraries
#include <stdio.h>
#include <vector>
#include <string>
#include <time.h>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <stdio.h>

// SDK
#include "public/tier0/wchartypes.h"
#include "public/cdll_int.h"
#include "public/iprediction.h"
#include "public/bone_setup.h"
#include "public/icliententitylist.h"
#include "public/ienginevgui.h"
#include "public/IGameUIFuncs.h"
#include "public/dlight.h"
#include "public/r_efx.h" 
#include "public/igameevents.h"
#include "public/view_shared.h"
#include "public/inetchannelinfo.h"
#include "public/iachievementmgr.h"
#include "public/steam/steam_api.h"
#include "public/steam/isteamuserstats.h"
#include "game/client/imessagechars.h"
#include "game/client/iclientmode.h"
#include "game/client/cliententitylist.h"
#include "game/client/cdll_client_int.h"
#include "game/client/cbase.h"
#include "game/client/c_baseanimating.h"
#include "game/client/c_basecombatweapon.h"
#include "game/client/c_baseplayer.h"
#include "game/client/enginesprite.h"
#include "game/client/input.h"
#include "game/client/c_playerresource.h"
#include "game/client/iviewrender.h"
#include "game/client/viewrender.h"
#include "game/client/game_controls/commandmenu.h"
#include "game/client/hudelement.h"
#include "public/engine/ivmodelrender.h"
#include "public/engine/ivdebugoverlay.h"
#include "public/engine/ivmodelinfo.h"
#include "public/engine/IEngineTrace.h"
#include "public/engine/IEngineSound.h"
#include "public/materialsystem/imaterialsystemstub.h"
#include "public/materialsystem/itexture.h"
#include "public/materialsystem/IMaterialVar.h"
#include "public/tier1/checksum_md5.h"
#include "public/matsys_controls/matsyscontrols.h"
#include "public/vgui/IClientPanel.h"
#include "public/vgui/IPanel.h"
#include "public/vgui/ISurface.h"
#include "public/vgui/ILocalize.h"
#include "public/collisionutils.h"
#include "public/vstdlib/random.h"
#include "public/vgui_controls/Panel.h"
#include "public/VGuiMatSurface/IMatSystemSurface.h"
#include "public/mathlib/vector.h"
#include "game/shared/usermessages.h"
#include "game/shared/basecombatweapon_shared.h"
#include "game/shared/takedamageinfo.h"
#include "game/shared/igamemovement.h"



// Libraries
#pragma comment(lib, "tier0.lib")
#pragma comment(lib, "tier1.lib")
#pragma comment(lib, "tier2.lib")
#pragma comment(lib, "tier3.lib")
#pragma comment(lib, "mathlib.lib")
#pragma comment(lib, "vstdlib.lib")
#define COL_CHEAT Color(150,0,250,255)
#define COL_WHITE Color(255,255,255,255)
#define COL_BLACK Color(0,0,0,255)

using namespace std;

//#include <Steamworks.h>
#include "sdk/sdk.h"
#include "utils/getvfunc.h"
#include <vector>
#include "sdk/lua_shared.h"


HFont FukoFont;
HFont FukoFontMenu;
HFont FukoFontMenuTitle;

//Color ColorFg = Color(200, 0, 0, 255); //Color(160, 32, 240, 255);
//Color ColorBg = Color(30, 30, 30, 255);

Color ColorFg = Color(50, 50, 50, 255);
Color ColorBg = Color(200, 200, 200, 255);
Color TextColor = Color(50, 50, 50, 255);

typedef void(__fastcall *OverrideViewFn)(void*, void*, CViewSetup*);
typedef void(__fastcall *PaintTraverseFn)(void*, void*, unsigned int, bool, bool);
typedef void(__fastcall *CreateMoveFn)(void*, void*, float, CUserCmd*);
typedef void(__fastcall *ClCreateMoveFn)(void*, void*, int sequence_number, float input_sample_frametime, bool active);

typedef void* (__stdcall* CreateLuaInterfaceFn)(char state, bool renew);
CreateLuaInterfaceFn oCreateInterface;

typedef void* (__stdcall* CloseLuaInterfaceFn)(ILuaInterface*);
CloseLuaInterfaceFn oCloseInterface;

typedef void(__fastcall *RunStringFn)(void*, void*, const char*, const char*, const char*, bool, bool);
RunStringFn oRunString;

typedef void(__fastcall *FireBulletsFn)(void*, void*, const FireBulletsInfo_t &info);
FireBulletsFn oFireBullets;

typedef CUserCmd*(__stdcall *GetUserCmdFn)(int);
GetUserCmdFn oGetUserCmd;

CreateInterfaceFn LuaFac = NULL;

OverrideViewFn oOverrideView;
PaintTraverseFn oPaintTraverse;
CreateMoveFn oCreateMove;
ClCreateMoveFn oClCreateMove;

#include "utils/interfaces.h"
#include "utils/netvars.h"
#include "libraries/vars.h"
#include "sdk/funcs.h"
#include "libraries/lua.h"
#include "libraries/console.h"
#include "libraries/draw.h"
#include "libraries/esp.h"
#include "nospread.h"
#include "libraries/aimbot.h"
#include "loliwork/loliwork.h"
#include "libraries/misc.h"
#include "utils/vmthook.h"
#include "utils/hookfuncs.h"
#include "utils/hooks.h"
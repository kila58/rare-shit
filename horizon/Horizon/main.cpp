#include "sdk.h"
#include "vmthook.h"
#include "cEsp.h"
#include "cDrawing.h"
#include "cMenu.h"
#include "detours.h"
#include "cMouse.h"

IBaseClientDLL*					g_pClient = NULL;
ISurface*						g_pSurface = NULL;
IPanel*							g_pPanel = NULL;
IVEngineClient*					g_pEngine = NULL;
IClientEntityList*				entitylist = NULL;
IEngineTrace*					g_pEngineTrace = NULL;
IVModelInfo*					g_pModelInfo = NULL;
CInput*							g_pInput = NULL;
IVDebugOverlay*					g_pDebugOverlay = NULL;


DETOUR_TRAMPOLINE(BOOL WINAPI PeekMessageA_t(LPMSG, HWND, UINT, UINT, UINT), PeekMessageA);
DETOUR_TRAMPOLINE(BOOL WINAPI SetCursorPos_t(int, int), SetCursorPos);
DETOUR_TRAMPOLINE(BOOL WINAPI GetCursorPos_t(LPPOINT), GetCursorPos);
//===================================================================================
BOOL WINAPI hkPeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
	if (!PeekMessageA_t(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg))
		return false;
	if (g_pEngine->IsInGame() && g_pEngine->IsConnected()){
		if (gMouse.peekMessage(lpMsg->message, lpMsg->wParam, lpMsg->lParam))
			return false;
	}
	return true;
}
//===================================================================================
BOOL WINAPI hkSetCursorPos(int x, int y)
{
	gMouse.oldPos[0] = x;
	gMouse.oldPos[1] = y;
	if (gMouse.active)
		return true;
	return SetCursorPos_t(x, y);
}
//===================================================================================
BOOL WINAPI hkGetCursorPos(LPPOINT lpPoint)
{
	BOOL ret = GetCursorPos_t(lpPoint);
	if (gMouse.active){
		ScreenToClient(GetForegroundWindow(), lpPoint);
		gMouse.mousePos[0] = lpPoint->x;
		gMouse.mousePos[1] = lpPoint->y;
		lpPoint->x = gMouse.oldPos[0];
		lpPoint->y = gMouse.oldPos[1];
	}
	return ret;
}

PVOID DetourFunc(BYTE *src, const BYTE *dst, const int len){
	BYTE *jmp = (BYTE*)malloc(len + 5);
	DWORD dwback;

	while (VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &dwback) == FALSE)
		Sleep(1);

	DWORD dwOld = 0;
	VirtualProtect(jmp, len, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy(jmp, src, len);
	VirtualProtect(jmp, len, dwOld, &dwOld);
	jmp += len;

	jmp[0] = 0xE9;
	*(DWORD*)(jmp + 1) = (DWORD)(src + len - jmp) - 5;

	src[0] = 0xE9;
	*(DWORD*)(src + 1) = (DWORD)(dst - src) - 5;

	VirtualProtect(src, len, dwback, &dwback);

	return (jmp - len);
}

tPaintTraverse		oPaintTraverse;

static bool bOnce = false;
void __fastcall hkPaintTraverse(void* thisptr, void* EDX, VPANEL vguiPanel, bool forceRepaint, bool allowForce)
{
	try
	{
		oPaintTraverse(thisptr, EDX, vguiPanel, forceRepaint, allowForce);

		static VPANEL OverlayPopupPanel;
		const char* pszPanelN = g_pPanel->GetClassName(vguiPanel);
		if (pszPanelN[0] == 'O' && pszPanelN[7] == 'P')
		{
			if (vguiPanel == OverlayPopupPanel)
				OverlayPopupPanel = vguiPanel;
			if (bOnce == false || !bOnce)
			{
				gDrawing.Init();
				bOnce = true;
			}
			gDrawing.DrawString(20, 20, COLORCODE(255, 0, 0, 255), "Horizon Hack Version: 1.0.0.0");

			if (g_pEngine->IsInGame() || g_pEngine->IsConnected())
			{
				gMenu.InitMenu();
				gMenu.DrawMenu();
				gEsp.DrawCrosshair();
				gMouse.buttons();
				gMouse.draw();
				gMouse.ClickHandler();

				for (int iIndex = 0; iIndex < entitylist->GetHighestEntityIndex(); iIndex++)
				{
					gEsp.DrawPlayerESP(iIndex);
				}
			}
		}
	}
	catch (...)
	{
		Beep(750, 2000);
	}
}

DWORD WINAPI init(LPVOID lpArguments)
{
	if (g_pClient == NULL)
	{
		CreateInterfaceFn EngineFactory = Sys_GetFactory("engine.dll");
		g_pEngine = (IVEngineClient*)EngineFactory("VEngineClient015", NULL);
		g_pEngineTrace = (IEngineTrace*)EngineFactory(INTERFACEVERSION_ENGINETRACE_CLIENT, NULL);
		g_pModelInfo = (IVModelInfo*)EngineFactory(VMODELINFO_CLIENT_INTERFACE_VERSION, NULL);
		g_pDebugOverlay = (IVDebugOverlay*)EngineFactory(VDEBUG_OVERLAY_INTERFACE_VERSION, NULL);

		CreateInterfaceFn ClientFactory = Sys_GetFactory("client.dll");
		entitylist = (IClientEntityList*)ClientFactory("VClientEntityList003", NULL);

		CreateInterfaceFn VGUIMatFactory = Sys_GetFactory("vguimatsurface.dll");
		g_pSurface = (ISurface*)VGUIMatFactory("VGUI_Surface030", NULL);

		CreateInterfaceFn VGUI2Factory = Sys_GetFactory("vgui2.dll");

		if (!g_pPanel)
		{
			g_pPanel = (IPanel*)VGUI2Factory("VGUI_Panel009", NULL);
			if (g_pPanel)
			{
				void __fastcall hkPaintTraverse(void* thisptr, void* EDX, VPANEL vguiPanel, bool forceRepaint, bool allowForce);
				oPaintTraverse = (tPaintTraverse)vtablehook_hook(g_pPanel, hkPaintTraverse, 41);
			}
		}

		DetourFunctionWithTrampoline((PBYTE)PeekMessageA_t, (PBYTE)hkPeekMessageA);
		DetourFunctionWithTrampoline((PBYTE)SetCursorPos_t, (PBYTE)hkSetCursorPos);
		DetourFunctionWithTrampoline((PBYTE)GetCursorPos_t, (PBYTE)hkGetCursorPos);

		g_pEngine->ClientCmd("toggleconsole");
		g_pEngine->ClientCmd("clear");
		g_pEngine->ClientCmd("echo Horizon Hack Information:");
		g_pEngine->ClientCmd("echo Version: 1.0.0.0");
		g_pEngine->ClientCmd("echo Up-Comign Features:");
		g_pEngine->ClientCmd("echo [+] Aimbot");
		g_pEngine->ClientCmd("echo     - Silent Aim");
		g_pEngine->ClientCmd("echo     - pSread");
		g_pEngine->ClientCmd("echo     - No Recoil");
		g_pEngine->ClientCmd("echo     - Anti-Aim");
		g_pEngine->ClientCmd("echo     - Silent Aim");
		g_pEngine->ClientCmd("echo [+] ESP");
		g_pEngine->ClientCmd("echo     - Box ESP (2D & 3D)");
		g_pEngine->ClientCmd("echo     - Information (Name, Health, Distance, Weapon)");
		g_pEngine->ClientCmd("echo     - Player Aura");
		g_pEngine->ClientCmd("echo     - Crosshair");
		g_pEngine->ClientCmd("echo     - Health Bar");
		g_pEngine->ClientCmd("echo     - Head Box");
		g_pEngine->ClientCmd("echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		g_pEngine->ClientCmd("echo Credits:");
		g_pEngine->ClientCmd("echo Sasha - Putting up with my bullshit questions and teaching me.");
		g_pEngine->ClientCmd("echo Kelse - Anwser my dumbass questions when sasha was not on.");
		g_pEngine->ClientCmd("echo Hafnium - Developing with me and helping me when I need it.");
		g_pEngine->ClientCmd("echo Skittles - Hooking help, esp help.");
		g_pEngine->ClientCmd("echo Grey Hellios - The internal hack.");

	}
	return 0;
}

// Horizon Hack //
// Credits Above //

DWORD WINAPI DllMain(HMODULE hDll, DWORD dwReasonForCall, LPVOID lpReserved)
{
	static HANDLE hThread = INVALID_HANDLE_VALUE;
	static DWORD dwExitCode;
	if (dwReasonForCall == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hDll);
		hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)init, NULL, 0, NULL);
		return (hThread != INVALID_HANDLE_VALUE);
	}
	return 0;
}
/*
=======================================================================
=  ######## ##     ## ##    ##  #######  ########   #######  ######## =
=  ##       ##     ## ##   ##  ##     ## ##     ## ##     ##    ##    =
=  ##       ##     ## ##  ##   ##     ## ##     ## ##     ##    ##    =
=  ######   ##     ## #####    ##     ## ########  ##     ##    ##    =
=  ##       ##     ## ##  ##   ##     ## ##     ## ##     ##    ##    =
=  ##       ##     ## ##   ##  ##     ## ##     ## ##     ##    ##    =
=  ##        #######  ##    ##  #######  ########   #######     ##    =
=======================================================================

SHOUT OUT TO:
	Hafnium
	Jay
	Mantis
	Chunkybear30
	D0SH
	Sadistic
	Im Friendly
	Cdriza
	SERVERMONEY
	Squishy loli
	Deagler
	D3X
	Function

	CREDITS:
	Hafnium
	Deagler
	d3x
	Function
	Daz

*/

#include <Windows.h>
#include "main.h"

void FukoThread()
{
	Interfaces.GetInterfaces();

	NVarManager = new CNetworkedVariableManager();

	//Msg("Offset: %x\n", NVarManager->GetOffset("DT_BasePlayer", "m_iHealth"));

	Vars->init();
	Hooks.GetHooks();

	for (;;)
	{
		if (GetAsyncKeyState(VK_INSERT))
			FukoMenu->Enabled = !FukoMenu->Enabled;
		

		Sleep(100);
	}

	//LuaShared->GetLuaInterface(0)->PushCFunction(GetSpreadVector);

}

void MenuThread()
{
	for (;;)
	{
		//Sleep(1);
		FukoMenu->Think();
	}
}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpvReserved){
	if (dwReason == DLL_PROCESS_ATTACH){
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)FukoThread, 0, 0, 0);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MenuThread, 0, 0, 0);
	}
	return TRUE;
}
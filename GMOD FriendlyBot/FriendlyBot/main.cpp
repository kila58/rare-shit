#include <Windows.h>
#include "sdk\hooks.h"
#include "sdk\sdk.h"
#include "sdk\interfaces.h"

#include "cheat\functions.h"
#include "cheat\visuals.h"
#include "cheat\aimbot.h"
#include "cheat\hooks.h"
 // 420
void FriendlyThread()
{
	InterfaceManager.Initialize();
	Hooks.Initialize();
}

BOOL __stdcall DllMain(HINSTANCE Instance, DWORD Reason, LPVOID Reserved)
{

	if ( Reason == DLL_PROCESS_ATTACH )
		CreateThread( NULL, NULL, (LPTHREAD_START_ROUTINE)FriendlyThread, NULL, NULL, NULL );
	
	return TRUE;

}

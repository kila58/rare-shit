#include "KeyEvent.h"
#include "Menu.h"

typedef int( __stdcall* oKeyEvent )( int, ValveSDK::ButtonCode_t, const char* );
int __stdcall hkKeyEvent( int eventcode, ValveSDK::ButtonCode_t KeyNum, const char* pszCurrentBinding )
{
	if( eventcode )
	{
		if( KeyNum != ValveSDK::BUTTON_CODE_INVALID )
		{
			g_pMenu->HandleInputChar( KeyNum );
		}
	}

	return g_pClientVMTHook->GetMethod< oKeyEvent >( 20 )( eventcode, KeyNum, pszCurrentBinding );
}
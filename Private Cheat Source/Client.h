#pragma once

#include "SDK.h"
typedef void* ( __stdcall* CreateMoveFn )( int, float, bool );
typedef void* ( __stdcall* IN_KeyEventFn )( int, int, const char * );



class ClientHook
{
public:
	void Init();
	int iInited;
};


void __stdcall Hooked_CreateMove( int sequence_number, float input_sample_frametime, bool active );
int __stdcall Hooked_IN_KeyEvent ( int eventcode, int keynum, const char *pszCurrentBinding );
//===================================================================================
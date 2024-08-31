#include "SDK.h"
#include "Client.h"
#include "CDrawManager.h"
#include "Color Manager.h"
#include "CGlobalVars.h"
#include "Player Manager.h"
#include "Control Variables.h"
#include "CreateMove.h"
#include "File Manager.h"

CreateMoveFn OriginalCreateMove;
IN_KeyEventFn OriginalKeyEvent;


CUserCmd* _pCommand;

void Init()
{
	ALX.pClientHook->iInited = NULL;
}

void __stdcall Hooked_CreateMove(int sequence_number, float input_sample_frametime, bool active)
{
	try
	{
		OriginalCreateMove(sequence_number, input_sample_frametime, active); //Call the original.

		CUserCmd* cmd = ALX.pInput->GetUserCmd(0,sequence_number);
		_pCommand = cmd;

	}
	catch (...)
	{
	
	}
}
//============================================================================================
void Hooked_Init()
{
	try
	{
		ALX.pPlayerVariables->FindOffset();

	    ALX.pDrawManager->Initialize();
		
		ALX.pCvar->Initialize();
		ALX.pFileManager->Initialize(ALX.pBaseAPI->GetDirectoryFile("Settings.ini"));
		ALX.pBaseAPI->LogToFile("Injection Successful"); //If the module got here without crashing, it is good day.

	}
	catch(...)
	{
		ALX.pBaseAPI->LogToFile("Failed Intro");
		ALX.pBaseAPI->ErrorBox("Failed Intro");
	}
}
//===================================================================================
int __stdcall Hooked_IN_KeyEvent ( int eventcode, int keynum, const char *pszCurrentBinding )
{
	
	return (int)OriginalKeyEvent(eventcode,keynum,pszCurrentBinding);
}
//===================================================================================
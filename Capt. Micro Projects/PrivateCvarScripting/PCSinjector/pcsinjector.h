#ifndef _PCSINJECTOR_H_
#define _PCSINJECTOR_H_

#include "winlite.h"
#include "tlhelp32.h"
#include "psapi.h"

#pragma comment(lib, "psapi.lib")

int CALLBACK WinMain(HINSTANCE hInst,
	HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow);

#endif //_PCSINJECTOR_H_
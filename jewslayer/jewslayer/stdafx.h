#ifndef __STDAFX_H__
#define __STDAFX_H__

#ifdef _MSC_VER
#pragma once
#endif

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <process.h>
#include <Mmsystem.h>
#pragma comment( lib, "Winmm.lib" )

#include "CVMTHookManager.h"
#include "CVarSystem.h"

template< class T > void SafeDelete( T** ppPointer )
{
	if( *ppPointer )
	{
		delete *ppPointer;
		*ppPointer = nullptr;
	}
}

#ifndef CONCAT_IMPL
#define CONCAT_IMPL(x, y) x##y
#ifndef MACRO_CONCAT
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#ifndef PAD
#define PAD(SIZE) BYTE MACRO_CONCAT(_pad, __COUNTER__)[SIZE];
#endif
#endif
#endif

extern CVMTHookManager* g_pClientVMTHook;
extern CVMTHookManager* g_pPredictionVMTHook;
extern CVMTHookManager* g_pPanelVMTHook;
extern CVMTHookManager* g_pModelRenderVMTHook;

#endif
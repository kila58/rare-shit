#ifndef __KEYEVENT_H__
#define __KEYEVENT_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"
#include "SDK.h"

extern int __stdcall hkKeyEvent( int eventcode, ValveSDK::ButtonCode_t KeyNum, const char* pszCurrentBinding );

#endif
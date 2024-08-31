#ifndef __PAINTTRAVERSE_H__
#define __PAINTTRAVERSE_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"
#include "SDK.h"

extern void __fastcall hkPaintTraverse( ValveSDK::IPanel* thisptr, int edx, unsigned int VGUIPanel, bool forceRepaint, bool allowForce );

#endif
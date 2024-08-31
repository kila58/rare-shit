#ifndef __RUNCOMMAND_H__
#define __RUNCOMMAND_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"
#include "SDK.h"

extern void __fastcall hkRunCommand( ValveSDK::IPrediction* thisptr, int edx, ValveSDK::CBaseEntity* pBaseEntity, ValveSDK::CUserCmd* pCmd, PVOID pMoveHelper );

#endif
#ifndef __AIMBOT_H__
#define __AIMBOT_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"
#include "SDK.h"

class CAimbot
{
private:
	bool IsAimKeyPressed( void );
	bool TraceTargetHitpoint( ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CBaseCombatWeapon* pLocalWeapon, ValveSDK::CBaseEntity* pBaseEntity, ValveSDK::Vector& vecHitPoint );
	int GetHitboxIndex( ValveSDK::CBaseEntity* pLocalEntity );
	int GetTargetData( ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CBaseCombatWeapon* pWeapon );

public:
	CAimbot( void );
	bool Main( ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CUserCmd* pCmd, bool& bSendPacket );
};

extern CAimbot* g_pAimbot;

#endif
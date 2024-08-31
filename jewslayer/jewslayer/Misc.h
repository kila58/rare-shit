#ifndef __MISC_H__
#define __MISC_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"
#include "SDK.h"

class CMisc
{
private:
	ValveSDK::QAngle	m_qOldViewPunch;
	ValveSDK::QAngle	m_qOldAimPunch;
	ValveSDK::QAngle*	m_pqViewPunch;
	ValveSDK::QAngle*	m_pqAimPunch;

private:
	bool EdgeAntiAim( ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CUserCmd* pCmd, float flWall, float flCornor );

public:
	CMisc( void );
	bool RemoveVisualsRecoil( ValveSDK::CBaseEntity* pLocalEntity );	
	void Pitch( ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CUserCmd* pCmd, bool& bSendPacket );
	void Yaw( ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CUserCmd* pCmd, bool& bSendPacket );
	void Bunnyhop( ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CUserCmd* pCmd );
	void RestoreVisualRecoil( void );
	void RemoveRecoil( ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CUserCmd* pCmd, bool bAimbotState );
	void RoundStartEvent( ValveSDK::IGameEvent* pGameEvent );
	void PlayerDeathEvent( ValveSDK::IGameEvent* pGameEvent );
};

extern CMisc* g_pMisc;

#endif
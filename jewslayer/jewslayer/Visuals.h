#ifndef __VISUALS_H__
#define __VISUALS_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"
#include "SDK.h"

class CVisuals
{
private:
	int						m_X;
	int						m_Y;
	int						m_W;
	int						m_H;
	ValveSDK::CBaseEntity*	m_pLocal;
	ValveSDK::Vector		m_vecFoot;
	ValveSDK::Vector		m_vecFootScreen;
	ValveSDK::Vector		m_vecHead;
	ValveSDK::Vector		m_vecHeadScreen;

private:
	void RenderPlayer( ValveSDK::CBaseEntity* pBaseEntity );

public:
	CVisuals( void );
	void Main( ValveSDK::CBaseEntity* pLocalEntity );

};

extern CVisuals* g_pVisuals;

#endif
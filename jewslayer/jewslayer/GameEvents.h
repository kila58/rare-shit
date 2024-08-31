#ifndef __GAMEEVENTS_H__
#define __GAMEEVENTS_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"
#include "SDK.h"

#define EVENT_DEBUG_ID_INIT			42

class CGameEvents : public ValveSDK::IGameEventListener2
{
public:

	std::vector< DWORD >	m_vHitMarks;
public:
	CGameEvents( );
	void FireGameEvent( ValveSDK::IGameEvent* event );
	void RegisterSelf( void );	
};

extern CGameEvents* g_pGameEvents;

#endif
#include "GameEvents.h"
#include "Misc.h"

CGameEvents::CGameEvents( void )
{
	m_nDebugId = EVENT_DEBUG_ID_INIT;
	m_vHitMarks.clear( );
}

void CGameEvents::FireGameEvent( ValveSDK::IGameEvent* event )
{
	std::string strEvent = event->GetName( );
	if( strEvent.empty( ) )
		return;

	if( event->GetName( ).empty( ) )
		return;
	
	g_pMisc->PlayerDeathEvent( event );
	g_pMisc->RoundStartEvent( event );
}

void CGameEvents::RegisterSelf( void )
{
	g_pGameEventManager->AddListener( this, "player_death", false );
	g_pGameEventManager->AddListener( this, "round_start", false );
}

CGameEvents* g_pGameEvents = nullptr;
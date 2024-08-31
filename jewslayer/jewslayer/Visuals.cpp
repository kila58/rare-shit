#include "Visuals.h"

void CVisuals::RenderPlayer( ValveSDK::CBaseEntity* pBaseEntity )
{
	m_H = int( m_vecFootScreen.y - m_vecHeadScreen.y );
	m_W = int( m_H / 4.5f ) * 2;
	m_X = int( m_vecHeadScreen.x - m_W / 2 );
	m_Y = int( m_vecHeadScreen.y );

	auto bVisible = g_pTools->IsVisible( m_pLocal->GetEyePosition( ), pBaseEntity->GetEyePosition( ), m_pLocal, pBaseEntity );
	auto color = pBaseEntity->GetTeamColor( bVisible );

	auto bOutlined = g_CVars.GetCVar( "vis_box_outlined" )->GetBool( );
	
	auto iBox = g_CVars.GetCVar( "vis_box" )->GetInt( );
	if( iBox > 0 )
	{
		switch( iBox )
		{
		case 1:
			if( bOutlined )
				g_pRenderSurface->BorderBoxOutlined( m_X, m_Y, m_W, m_H, 1, color, ValveSDK::Color( 0, 0, 0 ) );
			else g_pRenderSurface->BorderBox( m_X, m_Y, m_W, m_H, 1, color );
			break;
		case 2:
			g_pRenderSurface->CornerBox( m_X, m_Y, m_W, m_H, color, bOutlined );
			break;
		}
	}
	auto iWeapon = g_CVars.GetCVar( "vis_weapons" )->GetInt( );
	if( iWeapon > 0 )
	{
		auto pWeapon = pBaseEntity->GetWeapon( );
		if( pWeapon )
		{
			auto pWeaponData = pWeapon->GetWeaponData( );
			if( pWeaponData )
			{
				switch( iWeapon )
				{
				case 1:
					char pszBuffer[ 0x10 ];
					sprintf_s( pszBuffer, "%c", pWeaponData->m_pWeaponSIcon->m_szCharacter );
					int iFontSize[ 2 ] = { 0 };
					g_pRenderSurface->GetTextSize( 0xA1, pszBuffer, iFontSize[ 0 ], iFontSize[ 1 ] );
					g_pRenderSurface->String( m_X + ( m_W / 2 ) - ( iFontSize[ 0 ] / 2 ), m_Y + m_H + 2, ValveSDK::Color( 255, 255, 255 ), 0xA1, pszBuffer );
					break;
				}
			}
		}
		
	}
}

CVisuals::CVisuals( void )
{

}

void CVisuals::Main( ValveSDK::CBaseEntity* pLocalEntity )
{
	if( !g_CVars.GetCVar( "vis_active" )->GetBool( ) )
		return;

	m_pLocal = pLocalEntity;
	for( int i = 1; i < g_pEngine->GetMaxClients( ); i++ )
	{
		ValveSDK::CBaseEntity* pBaseEntity = g_pEntityList->GetBaseEntity( i );
		if( !pBaseEntity )
			continue;

		if( !pBaseEntity->IsValid( ) )
			continue;

		if( pLocalEntity == pBaseEntity )
			continue;

		if( g_CVars.GetCVar( "vis_enemyonly" )->GetBool( ) && pLocalEntity->GetTeam( ) == pBaseEntity->GetTeam( ) )
			continue;

		m_vecFoot = pBaseEntity->GetAbsOrigin( );
		if( ( pBaseEntity->GetFlags( ) & FL_DUCKING ) )
			m_vecHead = m_vecFoot + ValveSDK::Vector( 0.f, 0.f, 52.f );
		else m_vecHead = m_vecFoot + ValveSDK::Vector( 0.f, 0.f, 72.f );

		if( g_pTools->WorldToScreen( m_vecFoot, m_vecFootScreen ) && g_pTools->WorldToScreen( m_vecHead, m_vecHeadScreen ) )
		{
			RenderPlayer( pBaseEntity );
		}
	}
}

CVisuals* g_pVisuals = nullptr;
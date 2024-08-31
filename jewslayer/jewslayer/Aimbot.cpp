#include "Aimbot.h"
#include "Timer.h"

bool CAimbot::IsAimKeyPressed( void )
{
	static auto bAimKeyPressed = false;
	static auto AimTime = Timer( );
	auto iTime = g_CVars.GetCVar( "aim_time" )->GetInt( );

	if( g_CVars.GetCVar( "aim_autoshoot" )->GetBool( ) )
		return true;

	if( iTime > 0 )
	{
		if( GetKeyState( 1 ) & 0x8000 )
			bAimKeyPressed = true;
		else bAimKeyPressed = false;

		AimTime.SetTime( ( DWORD )iTime );

		if( bAimKeyPressed )
			AimTime.Run( );

		if( AimTime.finished( ) )
			bAimKeyPressed = false;
	}
	else
	{
		if( GetKeyState( 1 ) & 0x8000 )
			bAimKeyPressed = true;
		else bAimKeyPressed = false;
	}

	if( iTime > 0 && !bAimKeyPressed && !( GetKeyState( 1 ) & 0x8000 ) )
		AimTime.Reset( );

	return bAimKeyPressed;
}

bool CAimbot::TraceTargetHitpoint( ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CBaseCombatWeapon* pLocalWeapon, ValveSDK::CBaseEntity* pBaseEntity, ValveSDK::Vector& vecHitPoint )
{
	auto flMinDamage = g_CVars.GetCVar( "aim_autowall_damage" )->GetFloat( );
	auto vecCurPos = pLocalEntity->GetEyePosition( );

	ValveSDK::Vector vecHit;
	auto bDefaultHitbox = g_pTools->GetHitboxVector( pBaseEntity, GetHitboxIndex( pLocalEntity ), vecHit );
	if( bDefaultHitbox )
	{
		auto bIsVisible = g_pTools->IsVisible( vecCurPos, vecHit, pLocalEntity, pBaseEntity );
		if( bIsVisible )
		{
			vecHitPoint = vecHit;
			return true;
		}

		auto flDamage = 0.f;
		auto bPenetrate = ( g_CVars.GetCVar( "aim_autowall" )->GetBool( ) ) ? g_pTools->PenetrateWall( pLocalEntity, pLocalWeapon, vecHit, flDamage ) : false;

		if( bPenetrate && flDamage >= flMinDamage )
		{
			vecHitPoint = vecHit;
			return true;
		}
	}

	auto iHitScan = g_CVars.GetCVar( "aim_hitscan" )->GetInt( );
	if( iHitScan > 0 )
	{
		ValveSDK::matrix3x4 BoneMatrixArray[ 128 ];
		if( !pBaseEntity->SetupBones( BoneMatrixArray, 128, 0x100, 0.f ) )
			return false;

		for( int i = 0; i < 44; i++ )
		{
			ValveSDK::Vector vecHitscan;
			g_pTools->MatrixToVector( BoneMatrixArray[ i ], vecHitscan );

			if( g_pTools->IsVisible( vecCurPos, vecHitscan, pLocalEntity, pBaseEntity ) )
			{
				vecHitPoint = vecHitscan;
				return true;
			}

			if( iHitScan == 2 )
			{
				auto flDamage = 0.f;
				auto bPenetrate = g_pTools->PenetrateWall( pLocalEntity, pLocalWeapon, vecHitscan, flDamage );

				if( bPenetrate && flDamage >= flMinDamage )
				{
					vecHitPoint = vecHitscan;
					return true;
				}
			}
		}
	}

	return false;
}

int CAimbot::GetHitboxIndex( ValveSDK::CBaseEntity* pLocalEntity )
{
	auto iSmart = g_CVars.GetCVar( "aim_smart" )->GetInt( );
	if( iSmart > 0 && pLocalEntity->GetShotsFired( ) + 1 > iSmart )
		return g_CVars.GetCVar( "aim_smart_hitbox" )->GetInt( );

	return g_CVars.GetCVar( "aim_hitbox" )->GetInt( );
}

int CAimbot::GetTargetData( ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CBaseCombatWeapon* pWeapon )
{
	auto flMax = 9999.f;
	auto iBestTargetIndex = -1;
	auto iAimAt = g_CVars.GetCVar( "aim_at" )->GetInt( );

	ValveSDK::QAngle qClientViewAngles;
	g_pEngine->GetViewAngles( qClientViewAngles );

	for( int i = 1; i < g_pEngine->GetMaxClients( ); i++ )
	{
		auto pBaseEntity = g_pEntityList->GetBaseEntity( i );
		if( !pBaseEntity )
			continue;

		if( !pBaseEntity->IsValid( true ) )
			continue;

		if( iAimAt == 0 && pLocalEntity->GetTeam( ) == pBaseEntity->GetTeam( ) )
			continue;
		else if( iAimAt == 1 && pLocalEntity->GetTeam( ) != pBaseEntity->GetTeam( ) )
			continue;

		auto flFoV = g_pTools->GetFoV( qClientViewAngles, pLocalEntity->GetEyePosition( ), pBaseEntity->GetEyePosition( ) );
		if( flFoV < flMax )
		{
			flMax = flFoV;
			iBestTargetIndex = i;
		}
	}
	
	return iBestTargetIndex;
}

CAimbot::CAimbot( void )
{

}

bool CAimbot::Main( ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CUserCmd* pCmd, bool& bSendPacket )
{
	if( !g_CVars.GetCVar( "aim_active" )->GetBool( ) )
		return false;

	if( !pLocalEntity || !pCmd )
		return false;

	if( !IsAimKeyPressed( ) )
		return false;

	auto pLocalWeapon = pLocalEntity->GetWeapon( );
	if( !pLocalWeapon )
		return false;

	if( !pLocalWeapon->IsValid( true ) )
		return false;

	auto pLocalWeaponData = pLocalWeapon->GetWeaponData( );
	if( !pLocalWeaponData )
		return false;

	auto iIndex = GetTargetData( pLocalEntity, pLocalWeapon );
	if( iIndex == -1 )
		return false;
	
	auto pBaseEntity = g_pEntityList->GetBaseEntity( iIndex );
	if( !pBaseEntity )
		return false;

	ValveSDK::Vector vecAimFinal;
	if( !TraceTargetHitpoint( pLocalEntity, pLocalWeapon, pBaseEntity, vecAimFinal ) )
		return false;

	if( g_pTools->GetDistance( vecAimFinal, pLocalEntity->GetEyePosition( ) ) > pLocalWeaponData->m_flRange )
		return false;

	ValveSDK::QAngle qClientViewAngles;
	g_pEngine->GetViewAngles( qClientViewAngles );

	if( g_pTools->GetFoV( qClientViewAngles, pLocalEntity->GetEyePosition( ), vecAimFinal, g_CVars.GetCVar( "aim_distancebased" )->GetBool( ) ) > g_CVars.GetCVar( "aim_fov" )->GetFloat( ) )
		return false;

	ValveSDK::QAngle qAimAngles;
	g_pTools->CalcAngle( pLocalEntity->GetEyePosition( ), vecAimFinal, qAimAngles );

	auto iSilentAim = g_CVars.GetCVar( "aim_silent" )->GetInt( );
	auto flSmooth = g_CVars.GetCVar( "aim_smooth" )->GetFloat( );	

	if( g_CVars.GetCVar( "aim_rcs" )->GetBool( ) && pLocalWeapon->IsAutomatic( ) )
	{
		auto qPunchAngles = pLocalEntity->GetAimPunch( );
		qAimAngles -= qPunchAngles * 2.f;
		qAimAngles.z = 0.f;

		g_pTools->NormalizeVector( qAimAngles );
	}
	if( flSmooth > 0.f && !iSilentAim )
	{
		g_pTools->NormalizeVector( qClientViewAngles );

		auto qDelta = qClientViewAngles - qAimAngles;
		g_pTools->NormalizeVector( qDelta );

		auto qSmooth = qClientViewAngles - qDelta / flSmooth;
		g_pTools->NormalizeVector( qDelta );

		qAimAngles = qSmooth;
	}

	g_pTools->NormalizeVector( qAimAngles );
	g_pTools->ClampAngles( qAimAngles );

	pCmd->viewangles = qAimAngles;
	if( !iSilentAim )
		g_pEngine->SetViewAngles( qAimAngles );

	if( g_CVars.GetCVar( "aim_autoshoot" )->GetBool( ) )
		pCmd->buttons |= IN_ATTACK;

	return true;
}

CAimbot* g_pAimbot = nullptr;
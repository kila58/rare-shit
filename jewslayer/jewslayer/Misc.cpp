#include "Misc.h"

bool CMisc::EdgeAntiAim( ValveSDK::CBaseEntity* pLocalBaseEntity, ValveSDK::CUserCmd* cmd, float flWall, float flCornor )
{
	ValveSDK::IEngineTrace::Ray_t ray;
	ValveSDK::IEngineTrace::trace_t tr;

	ValveSDK::IEngineTrace::CTraceFilter traceFilter;
	traceFilter.pSkip = pLocalBaseEntity;

	auto bRetVal = false;
	auto vecCurPos = pLocalBaseEntity->GetEyePosition( );

	for( float i = 0; i < 360; i++ )
	{
		ValveSDK::Vector vecDummy( 10.f, cmd->viewangles.y, 0.f );
		vecDummy.y += i;

		g_pTools->NormalizeVector( vecDummy );

		ValveSDK::Vector vecForward;
		g_pTools->AngleVectors( vecDummy, vecForward );

		auto flLength = ( ( 16.f + 3.f ) + ( ( 16.f + 3.f ) * sin( DEG2RAD( 10.f ) ) ) ) + 7.f;
		vecForward *= flLength;

		ray.Init( vecCurPos, ( vecCurPos + vecForward ) );
		g_pEngineTrace->TraceRay( ray, MASK_SHOT, ( ValveSDK::IEngineTrace::CTraceFilter * )&traceFilter, &tr );

		if( tr.fraction != 1.0f )
		{
			ValveSDK::QAngle qAngles;
			auto vecNegate = tr.plane.normal;

			vecNegate *= -1.f;
			g_pTools->VectorAngles( vecNegate, qAngles );

			vecDummy.y = qAngles.y;

			g_pTools->NormalizeVector( vecDummy );
			ValveSDK::IEngineTrace::trace_t leftTrace, rightTrace;

			ValveSDK::Vector vecLeft;
			g_pTools->AngleVectors( vecDummy + ValveSDK::Vector( 0.f, 30.f, 0.f ), vecLeft );

			ValveSDK::Vector vecRight;
			g_pTools->AngleVectors( vecDummy - ValveSDK::Vector( 0.f, 30.f, 0.f ), vecRight );

			vecLeft *= ( flLength + ( flLength * sin( DEG2RAD( 30.f ) ) ) );
			vecRight *= ( flLength + ( flLength * sin( DEG2RAD( 30.f ) ) ) );

			ray.Init( vecCurPos, ( vecCurPos + vecLeft ) );
			g_pEngineTrace->TraceRay( ray, MASK_SHOT, ( ValveSDK::IEngineTrace::CTraceFilter* )&traceFilter, &leftTrace );

			ray.Init( vecCurPos, ( vecCurPos + vecRight ) );
			g_pEngineTrace->TraceRay( ray, MASK_SHOT, ( ValveSDK::IEngineTrace::CTraceFilter* )&traceFilter, &rightTrace );

			if( ( leftTrace.fraction == 1.f ) && ( rightTrace.fraction != 1.f ) )
				vecDummy.y -= flCornor; // left
			else if( ( leftTrace.fraction != 1.f )	&& ( rightTrace.fraction == 1.f ) )
				vecDummy.y += flCornor; // right			

			cmd->viewangles.y = vecDummy.y;
			cmd->viewangles.y -= flWall;
			bRetVal = true;
		}
	}
	return bRetVal;
}

CMisc::CMisc( void )
{

}

bool CMisc::RemoveVisualsRecoil( ValveSDK::CBaseEntity* pLocalEntity )
{
	if( !g_CVars.GetCVar( "misc_visnorecoil" )->GetBool( ) )
		return false;

	m_pqAimPunch = ( ValveSDK::QAngle* )( ( DWORD )pLocalEntity + Offsets::m_aimPunchAngle );
	m_pqViewPunch = ( ValveSDK::QAngle* )( ( DWORD )pLocalEntity + Offsets::m_viewPunchAngle );

	if( m_pqAimPunch && m_pqViewPunch )
	{
		m_qOldAimPunch = *m_pqAimPunch;
		m_qOldViewPunch = *m_pqViewPunch;

		m_pqAimPunch->Zero( );
		m_pqViewPunch->Zero( );

		return true;
	}

	return false;
}

void CMisc::Pitch( ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CUserCmd* pCmd, bool& bSendPacket )
{
	if( !pLocalEntity || !pCmd )
		return;

	CVar* pCVar = g_CVars.GetCVar( "misc_pitch" );
	if( !pCVar )
		return;

	auto iPitchType = pCVar->GetInt( );
	if( iPitchType == 0 )
		return;

	switch( iPitchType )
	{
	case 1:
		pCmd->viewangles.x = 89.f;
		break;
	}
}

void CMisc::Yaw( ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CUserCmd* pCmd, bool& bSendPacket )
{
	if( !pLocalEntity || !pCmd )
		return;

	CVar* pCVar = g_CVars.GetCVar( "misc_yaw" );
	if( !pCVar )
		return;

	// 0: off
	// 1: fdynamic
	int iYawType = pCVar->GetInt( );
	if( iYawType == 0 )
		return;

	static auto iChokedPackets = 0;
	switch( iYawType )
	{
	case 1:
		auto bEdge = EdgeAntiAim( pLocalEntity, pCmd, 0.f, 82.f );
		if( bEdge )
			return;

		iChokedPackets++;
		if( pCmd->buttons & IN_DUCK )
		{
			if( iChokedPackets < 6 )
			{
				bSendPacket = false;
				pCmd->viewangles.y = g_pTools->GetAntiAimAngles( pLocalEntity ).y - 102.159843f;
			}
			else
			{
				bSendPacket = true;
				pCmd->viewangles.y = g_pTools->GetAntiAimAngles( pLocalEntity ).y + 124.545463f;
				iChokedPackets = 0;
			}
		}
		else
		{
			if( iChokedPackets < 4 )
			{
				bSendPacket = false;
				pCmd->viewangles.y = g_pTools->GetAntiAimAngles( pLocalEntity ).y - 71.2513121f;
			}
			else
			{
				bSendPacket = true;
				pCmd->viewangles.y = g_pTools->GetAntiAimAngles( pLocalEntity ).y + 86.1294557f;
				iChokedPackets = 0;
			}
		}
		break;
	}
}

void CMisc::Bunnyhop( ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CUserCmd* pCmd )
{
	if( !pLocalEntity || !pCmd )
		return;

	CVar* pCVar = g_CVars.GetCVar( "misc_bunnyhop" );
	if( !pCVar )
		return;

	if( !pCVar->GetBool( ) )
		return;

	static bool bLastJumped = false, bShouldFake = false;
	if( !bLastJumped && bShouldFake )
	{
		bShouldFake = false;
		pCmd->buttons |= IN_JUMP;
	}
	else if( pCmd->buttons & IN_JUMP )
	{
		if( pLocalEntity->GetFlags( ) & FL_ONGROUND )
		{
			bLastJumped = true;
			bShouldFake = true;
		}
		else
		{
			pCmd->buttons &= ~IN_JUMP;
			bLastJumped = false;
		}
	}
	else
	{
		bLastJumped = false;
		bShouldFake = false;
	}
}

void CMisc::RestoreVisualRecoil( void )
{
	if( m_pqAimPunch && m_pqViewPunch )
	{
		*m_pqAimPunch = m_qOldAimPunch;
		*m_pqViewPunch = m_qOldViewPunch;
	}
}

void CMisc::RemoveRecoil( ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CUserCmd* pCmd, bool bAimbotState )
{
	if( !pLocalEntity || !pCmd )
		return;

	if( !g_CVars.GetCVar( "aim_norecoil" )->GetBool( ) )
		return;

	auto pWeapon = pLocalEntity->GetWeapon( );
	if( !pWeapon )
		return;

	if( !pWeapon->IsValid( ) )
		return;

	if( pCmd->buttons & IN_ATTACK )
	{
		if( g_CVars.GetCVar( "aim_rcs" )->GetBool( ) && bAimbotState && pWeapon->IsAutomatic( ) )
			return;

		auto qPunchAngles = pLocalEntity->GetAimPunch( );
		auto qAimAngles = pCmd->viewangles;
		qAimAngles -= qPunchAngles * 2.f;
		g_pTools->NormalizeVector( qAimAngles );
		g_pTools->ClampAngles( qAimAngles );

		pCmd->viewangles = qAimAngles;
	}	
}

void CMisc::RoundStartEvent( ValveSDK::IGameEvent* pGameEvent )
{
	if( !pGameEvent )
		return;

	auto bRoundStart = g_CVars.GetCVar( "spam_roundstart" )->GetBool( );
	if( !pGameEvent->GetName( ).compare( "round_start" ) )
	{
		if( bRoundStart )
			g_pEngine->ClientCmd( "say Jewslayer rage hake by kidua & reactiion" );
	}
}

void CMisc::PlayerDeathEvent( ValveSDK::IGameEvent* pGameEvent )
{
	if( !pGameEvent )
		return;

	auto b1Tap = g_CVars.GetCVar( "spam_1tap" )->GetBool( );
	auto bSound = g_CVars.GetCVar( "spam_sound" )->GetBool( );

	if( b1Tap || bSound )
	{
		if( !pGameEvent->GetName( ).compare( "player_death" ) )
		{
			auto userid = g_pEngine->GetPlayerForUserID( pGameEvent->GetInt( "userid" ) );
			auto attacker = g_pEngine->GetPlayerForUserID( pGameEvent->GetInt( "attacker" ) );
			auto iLocalPlayer = g_pEngine->GetLocalPlayer( );
			auto headshot = pGameEvent->GetBool( "headshot" );

			if(  attacker == iLocalPlayer && userid != iLocalPlayer )
			{
				if( headshot )
				{
					if( b1Tap )
						g_pEngine->ClientCmd( "say 1TAP" );

					if( bSound )
					{
						char pszPath[ MAX_PATH ];
						sprintf_s( pszPath, "%s\\sound\\hitler.wav", g_pEngine->GetGameDirectory( ).c_str( ) );
						PlaySoundA( pszPath, NULL, SND_FILENAME | SND_ASYNC | SND_NOWAIT );
					}					
				}
				else
					if( b1Tap )
						g_pEngine->ClientCmd( "say noob" );
			}
			else if( b1Tap && userid == iLocalPlayer && !headshot )
			{
				ValveSDK::IEngineClient::player_info_t info;
				if( g_pEngine->GetPlayerInfo( attacker, &info ) )
				{
					char pszBuffer[ 64 ];
					sprintf_s( pszBuffer, "say %s b1g bodyaimer", info.name );
					g_pEngine->ClientCmd( pszBuffer );
				}
			}
		}
	}	
}

CMisc* g_pMisc = nullptr;
#include "CreateMove.h"
#include "Aimbot.h"
#include "Misc.h"

CVMTHookManager* g_pCreateMoveVMTHook = nullptr;
typedef void( __stdcall* oCreateMove )( int, float, bool );

void __stdcall CreateMoveProxy( int sequence_number, float input_sample_frameTime, bool active, bool& bSendPacket )
{
	g_pClientVMTHook->GetMethod< oCreateMove >( 21 )( sequence_number, input_sample_frameTime, active );

	auto pCmd = &( *( ValveSDK::CUserCmd** )( ( DWORD_PTR )g_pInput + 0xEC ) )[ sequence_number % 150 ];
	if( !pCmd )
		return;

	auto pVerifiedCmd = &( *( ValveSDK::CInput::CVerifiedUserCmd** )( ( DWORD_PTR )g_pInput + 0xF0 ) )[ sequence_number % 150 ];
	if( !pVerifiedCmd )
		return;

	auto pLocalEntity = g_pTools->GetLocalPlayer( );
	if( pLocalEntity && pLocalEntity->IsValid( ) )
	{
		g_pMisc->Bunnyhop( pLocalEntity, pCmd );
		
		auto bAimbotSucceeded = g_pAimbot->Main( pLocalEntity, pCmd, bSendPacket );
		g_pMisc->RemoveRecoil( pLocalEntity, pCmd, bAimbotSucceeded );
		
		auto bUseAA = ( g_CVars.GetCVar( "misc_pitch" )->GetInt( ) > 0 || g_CVars.GetCVar( "misc_yaw" )->GetInt( ) > 0 );
		if( bUseAA )
		{
			static auto iChokedPackets = 0;
			iChokedPackets++;
			if( pCmd->buttons & IN_ATTACK && iChokedPackets < 6 && g_pTools->IsAbleToShoot( pLocalEntity, pLocalEntity->GetWeapon( ) ) )
			{

				bSendPacket = false;
			}
			else
			{
				bSendPacket = true;
				iChokedPackets = 0;

				ValveSDK::Vector vMove( pCmd->forwardmove, pCmd->sidemove, pCmd->upmove );
				float flSpeed = sqrt( vMove.x * vMove.x + vMove.y * vMove.y ), flYaw;
				ValveSDK::Vector v2ndMove;
				ValveSDK::Vector vView( pCmd->viewangles );
				g_pTools->VectorAngles( vMove, v2ndMove );

				g_pMisc->Pitch( pLocalEntity, pCmd, bSendPacket );
				g_pMisc->Yaw( pLocalEntity, pCmd, bSendPacket );

				flYaw = DEG2RAD( pCmd->viewangles.y - vView.y + v2ndMove.y );
				pCmd->forwardmove = cos( flYaw ) * flSpeed;
				pCmd->sidemove = sin( flYaw ) * flSpeed;
			}
		}
		
	}

	g_pTools->ClampAngles( pCmd->viewangles );

	pVerifiedCmd->m_cmd = *pCmd;
	pVerifiedCmd->m_crc = pCmd->GetChecksum( );
}
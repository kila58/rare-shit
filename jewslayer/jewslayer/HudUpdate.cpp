#include "HudUpdate.h"

CVMTHookManager* g_pHudUpdateVMTHook = nullptr;
typedef void( __stdcall* oHudUpdate )( bool );

void PitchFix( const ValveSDK::CRecvProxyData *pData, void* pStruct, void* pOut )
{
	float flPitch = pData->m_Value.m_Float;

	*( float* )pOut = flPitch;
}

void YawFix( const ValveSDK::CRecvProxyData *pData, void* pStruct, void* pOut )
{
	float flYaw = pData->m_Value.m_Float;

	*( float* )pOut = flYaw;
}

void __stdcall hkHudUpdate( bool bActive )
{
	//g_pHudUpdateVMTHook->GetMethod< oHudUpdate >( 11 )( bActive );
	g_pClientVMTHook->GetMethod< oHudUpdate >( 11 )( bActive );
}
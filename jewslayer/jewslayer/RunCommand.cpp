#include "RunCommand.h"

typedef void( __thiscall* oRunCommand )( ValveSDK::IPrediction*, ValveSDK::CBaseEntity*, ValveSDK::CUserCmd*, PVOID );
void __fastcall hkRunCommand( ValveSDK::IPrediction* thisptr, int edx, ValveSDK::CBaseEntity* pBaseEntity, ValveSDK::CUserCmd* pCmd, PVOID pMoveHelper )
{
	g_pPredictionVMTHook->GetMethod< oRunCommand >( 19 )( thisptr, pBaseEntity, pCmd, pMoveHelper );
	g_pMoveHelper = ( ValveSDK::IMoveHelper* )pMoveHelper;
}
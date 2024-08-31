#include "FrameStageNotify.h"
#include "Misc.h"

int m_iKnifeItemIndexes[ ] =
{
	ValveSDK::WEAPON_KNIFE_T,
	ValveSDK::WEAPON_KNIFE_CT,
	ValveSDK::WEAPON_KNIFE_BAYONET,
	ValveSDK::WEAPON_KNIFE_FLIP,
	ValveSDK::WEAPON_KNIFE_GUT,
	ValveSDK::WEAPON_KNIFE_KARAMBIT,
	ValveSDK::WEAPON_KNIFE_M9BAYONET,
	ValveSDK::WEAPON_KNIFE_HUNTSMAN,
	ValveSDK::WEAPON_KNIFE_BUTTERFLY,
	ValveSDK::WEAPON_KNIFE_FALCHION,
};

std::string m_strKnifeModels[ ] =
{
	"models/weapons/v_knife_default_t.mdl",
	"models/weapons/v_knife_default_ct.mdl",
	"models/weapons/v_knife_bayonet.mdl",
	"models/weapons/v_knife_flip.mdl",
	"models/weapons/v_knife_gut.mdl",
	"models/weapons/v_knife_karam.mdl",
	"models/weapons/v_knife_m9_bay.mdl",
	"models/weapons/v_knife_tactical.mdl",
	"models/weapons/v_knife_butterfly.mdl",
	"models/weapons/v_knife_falchion_advanced.mdl",
	"models/weapons/v_knife_gg.mdl"
};

int m_nModelIndexPatched = 0; // return the new model index
void KnifeModelChangerProxy( const ValveSDK::CRecvProxyData* pData, PVOID pStruct, PVOID pOut )
{
	if( ( *( int* )( ( DWORD )pData + 0x8 ) == g_pModelInfo->GetModelIndex( "models/weapons/v_knife_default_t.mdl" ) ) || *( int* )( ( DWORD )pData + 0x8 ) == g_pModelInfo->GetModelIndex( "models/weapons/v_knife_default_ct.mdl" ) )
	{
// 			*( int* )( ( DWORD )pData + 0x8 ) = g_pModelInfo->GetModelIndex( "models/weapons/v_knife_default_t.mdl" );

// 			*( int* )( ( DWORD )pData + 0x8 ) = g_pModelInfo->GetModelIndex( "models/weapons/v_knife_default_ct.mdl" );

// 			*( int* )( ( DWORD )pData + 0x8 ) = g_pModelInfo->GetModelIndex( "models/weapons/v_knife_bayonet.mdl" );

// 			*( int* )( ( DWORD )pData + 0x8 ) = g_pModelInfo->GetModelIndex( "models/weapons/v_knife_flip.mdl" );

// 			*( int* )( ( DWORD )pData + 0x8 ) = g_pModelInfo->GetModelIndex( "models/weapons/v_knife_gut.mdl" );

			*( int* )( ( DWORD )pData + 0x8 ) = g_pModelInfo->GetModelIndex( "models/weapons/v_knife_karam.mdl" );

// 			*( int* )( ( DWORD )pData + 0x8 ) = g_pModelInfo->GetModelIndex( "models/weapons/v_knife_m9_bay.mdl" );

// 			*( int* )( ( DWORD )pData + 0x8 ) = g_pModelInfo->GetModelIndex( "models/weapons/v_knife_tactical.mdl" );

// 			*( int* )( ( DWORD )pData + 0x8 ) = g_pModelInfo->GetModelIndex( "models/weapons/v_knife_butterfly.mdl" );

// 			*( int* )( ( DWORD )pData + 0x8 ) = g_pModelInfo->GetModelIndex( "models/weapons/v_knife_falchion_advanced.mdl" );
	}
	*( int* )( ( DWORD )pOut ) = *( int* )( ( DWORD )pData + 0x8 );
}

typedef void( __stdcall* oFrameStageNotify )( ValveSDK::ClientFrameStage_t );
void __stdcall hkFrameStageNotify( ValveSDK::ClientFrameStage_t curStage )
{
	auto bVisNoRecoil = false;
	auto* pLocal = g_pTools->GetLocalPlayer( );
	if( pLocal && pLocal->IsValid( ) )
	{
		if( curStage == ValveSDK::FRAME_RENDER_START )
		{
			bVisNoRecoil = g_pMisc->RemoveVisualsRecoil( pLocal );
		}
		if( curStage == ValveSDK::FRAME_NET_UPDATE_POSTDATAUPDATE_START )
		{

		}
	}

	g_pClientVMTHook->GetMethod< oFrameStageNotify >( 36 )( curStage );

	if( bVisNoRecoil )
		g_pMisc->RestoreVisualRecoil( );

	if( curStage == ValveSDK::FRAME_NET_UPDATE_POSTDATAUPDATE_START && g_pEngine->GetLocalPlayer() > 0 )
	{

		ValveSDK::CBaseEntity* pLocal = g_pEntityList->GetBaseEntity( g_pEngine->GetLocalPlayer( ) );

		if( !pLocal )
			return;

		if( !pLocal->GetLifeState() == LIFE_ALIVE )
			return;

		ValveSDK::CBaseCombatWeapon* pWeapon = pLocal->GetWeapon();
		if( !pWeapon )
			return;

		pWeapon->SetPattern( 30, 99, 10, true, 1 );

		ValveSDK::ClientClass *pClass = g_pClient->GetFirstClass( );
		while( pClass )
		{
			const char *pszName = pClass->GetTable()->GetName();

			if( !strcmp( pszName, "DT_BaseViewModel" ) )
			{
				for( int i = 0; i < pClass->GetTable()->GetNumProps(); i++ )
				{
					ValveSDK::RecvProp *pProp = pClass->GetTable()->GetProp( i );

					if( !strcmp( pProp->GetName(), "m_nModelIndex" ) )
					{
						if( pWeapon->IsKnife() )
						{
							pProp->SetProxyFn( KnifeModelChangerProxy );

// 								*( int* )( ( DWORD )pWeapon + 0x1148 + 0x40 + 0x194 ) = 500;

// 								*( int* )( ( DWORD )pWeapon + 0x1148 + 0x40 + 0x194 ) = 505;

// 								*( int* )( ( DWORD )pWeapon + 0x1148 + 0x40 + 0x194 ) = 506;

								*( int* )( ( DWORD )pWeapon + 0x1148 + 0x40 + 0x194 ) = 507;

// 								*( int* )( ( DWORD )pWeapon + 0x1148 + 0x40 + 0x194 ) = 508;

// 								*( int* )( ( DWORD )pWeapon + 0x1148 + 0x40 + 0x194 ) = 509;

// 								*( int* )( ( DWORD )pWeapon + 0x1148 + 0x40 + 0x194 ) = 515;

// 								*( int* )( ( DWORD )pWeapon + 0x1148 + 0x40 + 0x194 ) = 512;
						}
					}
				}
			}

			pClass = pClass->GetNextClass();
		}
	}
}
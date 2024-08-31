#include "DrawModelExecute.h"

typedef void( __thiscall* oDrawModelExecute )( PVOID, PVOID, const ValveSDK::DrawModelState_t&, const ValveSDK::ModelRenderInfo_t&, ValveSDK::matrix3x4* );
void __fastcall hkDrawModelExecute( PVOID thisptr, int edx, PVOID pContext, const ValveSDK::DrawModelState_t& pState, const ValveSDK::ModelRenderInfo_t& pInfo, ValveSDK::matrix3x4* pCustomBoneToWorld )
{
	// Normal engine materials
	static ValveSDK::IMaterial* pNormalMaterial[ 4 ] =
	{
		g_pTools->CreateMaterial( false, false, false ),
		g_pTools->CreateMaterial( false, false, true ),
		g_pTools->CreateMaterial( false, true, false ),
		g_pTools->CreateMaterial( false, true, true )
	};

	// Engine materials witout Z buffer
	static ValveSDK::IMaterial* pIgnoreZMaterial[ 4 ] =
	{
		g_pTools->CreateMaterial( true, false, false ),
		g_pTools->CreateMaterial( true, false, true ),
		g_pTools->CreateMaterial( true, true, false ),
		g_pTools->CreateMaterial( true, true, true )
	};

	// Get the current model name
	auto strModelName = g_pModelInfo->GetModelName( pInfo.pModel );
	
	auto iChams = g_CVars.GetCVar( "vis_chams" )->GetInt( );
	if( iChams > 0 && strModelName.find( "models/player" ) != std::string::npos )
	{
		auto pLocalEntity = g_pEntityList->GetBaseEntity( g_pEngine->GetLocalPlayer( ) );
		auto pBaseEntity = g_pEntityList->GetBaseEntity( pInfo.entity_index );

		if( pLocalEntity && pBaseEntity && pBaseEntity->GetLifeState( ) == LIFE_ALIVE )
		{
			if( g_CVars.GetCVar( "vis_enemyonly" )->GetBool( ) && pBaseEntity->GetTeam( ) == pLocalEntity->GetTeam( ) )
			{
				g_pModelRenderVMTHook->GetMethod< oDrawModelExecute >( 21 )( thisptr, pContext, pState, pInfo, pCustomBoneToWorld );
				return;
			}

			auto bWireframe = g_CVars.GetCVar( "vis_chams_wireframe" )->GetBool( );
			auto color = pBaseEntity->GetTeamColor( );

			if( iChams == 1 )
				g_pTools->ForceMaterial( color, bWireframe ? pIgnoreZMaterial[ 1 ] : pIgnoreZMaterial[ 0 ] );
			else g_pTools->ForceMaterial( color, bWireframe ? pIgnoreZMaterial[ 3 ] : pIgnoreZMaterial[ 2 ] );

			g_pModelRenderVMTHook->GetMethod< oDrawModelExecute >( 21 )( thisptr, pContext, pState, pInfo, pCustomBoneToWorld );
			color = pBaseEntity->GetTeamColor( true );

			if( iChams == 1 )
				g_pTools->ForceMaterial( color, bWireframe ? pNormalMaterial[ 1 ] : pNormalMaterial[ 0 ] );
			else g_pTools->ForceMaterial( color, bWireframe ? pNormalMaterial[ 3 ] : pNormalMaterial[ 2 ] );

		}
	}
	

	if( g_CVars.GetCVar( "vis_hands" )->GetInt( ) > 0 )
	{
		if( strModelName.find( "models/weapons/ct_arms" ) != std::string::npos || strModelName.find( "models/weapons/t_arms" ) != std::string::npos )
		{
			auto pMaterial = g_pMaterialSystem->FindMaterial( strModelName.c_str( ), "Model textures" );

			if( g_CVars.GetCVar( "vis_hands" )->GetInt( ) == 1 )
				pMaterial->SetMaterialVarFlag( ValveSDK::MATERIAL_VAR_NO_DRAW, true );
			else
				pMaterial->SetMaterialVarFlag( ValveSDK::MATERIAL_VAR_NO_DRAW, false );

			if( g_CVars.GetCVar( "vis_hands" )->GetInt( ) == 2 )
				pMaterial->SetMaterialVarFlag( ValveSDK::MATERIAL_VAR_WIREFRAME, true );
			else
				pMaterial->SetMaterialVarFlag( ValveSDK::MATERIAL_VAR_WIREFRAME, false );

			g_pModelRender->ForcedMaterialOverride( pMaterial );
		}
	}

	g_pModelRenderVMTHook->GetMethod< oDrawModelExecute >( 21 )( thisptr, pContext, pState, pInfo, pCustomBoneToWorld );
	g_pModelRender->ForcedMaterialOverride( NULL );

}
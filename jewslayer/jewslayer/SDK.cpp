#include "SDK.h"

#define MAT( _TYPE_ ) "\"" + _TYPE_ + "\"\n{\n\t\"$basetexture\" \"vgui/white_additive\"\n\t\"$ignorez\" \"0\"\n\t\"$nofog\" \"1\"\n\t\"$halflambert\" \"1\"\n}"
#define MAT_IGNOREZ( _TYPE_ ) "\"" + _TYPE_ + "\"\n{\n\t\"$basetexture\" \"vgui/white_additive\"\n\t\"$ignorez\" \"1\"\n\t\"$nofog\" \"1\"\n\t\"$halflambert\" \"1\"\n}"

using namespace ValveSDK;

void GenerateRandomString( char *s, const int len ) {
	static const char alphanum[ ] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for( int i = 0; i < len; ++i ) {
		s[ i ] = alphanum[ rand( ) % ( sizeof( alphanum ) - 1 ) ];
	}

	s[ len ] = 0;
}

CTools::CTools( void )
{

}

bool CTools::GetHitboxVector( CBaseEntity* pBaseEntity, int iHitbox, Vector& vecHitbox )
{
	if( !pBaseEntity )
		return false;

	if( iHitbox >= HITBOX_MAX )
		return false;

	mstudiobbox_t* pHitbox = GetHitboxData( pBaseEntity, iHitbox );
	if( !pHitbox )
		return false;

	matrix3x4 BoneMatrixArray[ 128 ];
	if( !pBaseEntity->SetupBones( BoneMatrixArray, 128, 0x100, 0.f ) )
		return false;

	Vector vecMin;
	VectorTransform( pHitbox->bbmin, BoneMatrixArray[ pHitbox->bone ], vecMin );

	Vector vecMax;
	VectorTransform( pHitbox->bbmax, BoneMatrixArray[ pHitbox->bone ], vecMax );

	vecHitbox = ( vecMin + vecMax ) * 0.5f;

	return true;
}

bool CTools::IsAbleToShoot( CBaseEntity* pBaseEntity, CBaseCombatWeapon* pWeapon )
{
	if( !g_pGlobalVarsBase )
		return false;

	if( !pBaseEntity || !pWeapon )
		return false;

	auto flServerTime = ( float )pBaseEntity->GetTickBase( ) * g_pGlobalVarsBase->interval_per_tick;
	auto flNextPrimaryAttack = pWeapon->GetNextPrimaryAttack( );

	return( flNextPrimaryAttack < flServerTime );
}

bool CTools::IsBreakableEntity( CBaseEntity* pBaseEntity )
{
	if( !pBaseEntity )
		return false;

	if( pBaseEntity->GetCollisionGroup( ) != COLLISION_GROUP_PUSHAWAY && pBaseEntity->GetCollisionGroup( ) != COLLISION_GROUP_BREAKABLE_GLASS && pBaseEntity->GetCollisionGroup( ) != COLLISION_GROUP_NONE )
		return false;

	if( pBaseEntity->GetHealth( ) > 200 )
		return false;

	IMultiplayerPhysics* pPhysicsInterface = ( IMultiplayerPhysics* )pBaseEntity;
	if( pPhysicsInterface )
	{
		if( pPhysicsInterface->GetMultiplayerPhysicsMode( ) != PHYSICS_MULTIPLAYER_SOLID )
			return false;
	}
	else
	{
		if( !pBaseEntity->GetClientClass( )->GetName( ).compare( "func_breakable" ) || !pBaseEntity->GetClientClass( )->GetName( ).compare( "func_breakable_surf" ) )
		{
			if( !pBaseEntity->GetClientClass( )->GetName( ).compare( "func_breakable_surf" ) )
				if( pBaseEntity->IsBroken( ) )
					return false;
		}
		else if( pBaseEntity->PhysicsSolidMaskForEntity( ) & CONTENTS_PLAYERCLIP )
			return false;
	}

	IBreakableWithPropData* pBreakableInterface = ( IBreakableWithPropData* )pBaseEntity;
	if( pBreakableInterface )
		if( pBreakableInterface->GetDmgModBullet( ) <= 0.0f )
			return false;

	return true;
}

bool CTools::IsVisible( const Vector& vecStart, const Vector& vecEnd, CBaseEntity* pIgnore, CBaseEntity* pEntity )
{
	if( !g_pEngineTrace )
		return false;

	IEngineTrace::trace_t trace;
	UTIL_TraceLine( vecStart, vecEnd, 0x4600400B, pIgnore, &trace );

	if( TraceDidHitWorld( &trace ) )
		return false;

	return( trace.m_pEnt == pEntity || trace.fraction >= 1.f );
}

bool CTools::HandleBulletPenetration( CWeaponData* pWeaponData, FireBulletData& BulletData )
{
	if( !pWeaponData )
		return false;

	auto* pEnterSurfaceData = g_pPhysSurface->GetSurfaceData( BulletData.enter_trace.surface.surfaceProps );
	if( !pEnterSurfaceData )
		return false;

	int iEnterMaterial = pEnterSurfaceData->game.material;
	auto flEnterSurfacePenetrationModifier = pEnterSurfaceData->game.flPenetrationModifier;

	BulletData.trace_length += BulletData.enter_trace.fraction * BulletData.trace_length_remaining;
	BulletData.current_damage *= ( float )pow( pWeaponData->m_flRangeModifier, ( BulletData.trace_length * 0.002f ) );

	if( ( BulletData.trace_length > 3000.f ) || ( flEnterSurfacePenetrationModifier < 0.1f ) )
		BulletData.penetrate_count = 0;

	if( BulletData.penetrate_count <= 0 )
		return false;

	Vector vecTemp;
	IEngineTrace::trace_t ExitTrace;
	if( !TraceToExit( vecTemp, &BulletData.enter_trace, BulletData.enter_trace.endpos, BulletData.direction, &ExitTrace ) )
		return false;

	auto* pExitSurfaceData = g_pPhysSurface->GetSurfaceData( ExitTrace.surface.surfaceProps );
	if( !pExitSurfaceData )
		return false;

	int iExitMaterial = pExitSurfaceData->game.material;
	auto flExitSurfacePenetrationModifier = pExitSurfaceData->game.flPenetrationModifier;
	auto flDinalDamageModifier = 0.16f;
	auto flCombinedPenetrarionModifier = 0.f;

	if( ( ( BulletData.enter_trace.contents & CONTENTS_GRATE ) != 0 ) || ( iEnterMaterial == 89 ) || ( iEnterMaterial == 71 ) )
	{
		flCombinedPenetrarionModifier = 3.f;
		flDinalDamageModifier = 0.05f;
	}
	else flCombinedPenetrarionModifier = ( flEnterSurfacePenetrationModifier + flExitSurfacePenetrationModifier ) * 0.5f;

	if( iEnterMaterial == iExitMaterial )
	{
		if( iExitMaterial == 87 || iExitMaterial == 85 )
			flCombinedPenetrarionModifier = 3.f;
		else if( iExitMaterial == 76 )
			flCombinedPenetrarionModifier = 2.f;
	}

	auto flModifier = fmaxf( 0.f, 1.0f / flCombinedPenetrarionModifier );
	auto flTakenDamage = ( BulletData.current_damage * flDinalDamageModifier ) + flModifier * 3.f * fmaxf( 0.f, ( 3.f / pWeaponData->m_flPenetration ) * 1.25f );
	auto flThickness = Vector( ExitTrace.endpos - BulletData.enter_trace.endpos ).Length( );

	flThickness *= flThickness;
	flThickness *= flModifier;
	flThickness /= 24.f;

	auto flTravelDamage = fmaxf( 0.f, flTakenDamage + flThickness );

	if( flTravelDamage > BulletData.current_damage )
		return false;

	if( flTravelDamage >= 0.f )
		BulletData.current_damage -= flTravelDamage;

	if( BulletData.current_damage < 1.f )
		return false;

	BulletData.src = ExitTrace.endpos;
	BulletData.penetrate_count--;

	return true;
}

bool CTools::PenetrateWall( CBaseEntity* pBaseEntity, CBaseCombatWeapon* pWeapon, const Vector& vecPoint, float& flDamage )
{
	if( !pBaseEntity || !pWeapon )
		return false;

	auto BulletData = FireBulletData( pBaseEntity->GetEyePosition( ) );
	BulletData.filter.pSkip = pBaseEntity;

	QAngle qAngles;
	CalcAngle( BulletData.src, vecPoint, qAngles );
	AngleVectors( qAngles, BulletData.direction );
	VectorNormalize( BulletData.direction );
	

	if( !SimulateFireBullet( pBaseEntity, pWeapon, BulletData ) )
		return false;

	flDamage = BulletData.current_damage;

	return true;
}

bool CTools::SimulateFireBullet( CBaseEntity* pBaseEntity, CBaseCombatWeapon* pWeapon, FireBulletData& BulletData )
{
	if( !pBaseEntity || !pWeapon )
		return false;

	BulletData.penetrate_count = 4;
	BulletData.trace_length = 0.0f;
	auto* pCSWeaponData = pWeapon->GetWeaponData( );
	if( !pCSWeaponData )
		return false;

	BulletData.current_damage = ( float )pCSWeaponData->m_iDamage;

	while( ( BulletData.penetrate_count > 0 ) && ( BulletData.current_damage >= 1.0f ) )
	{
		BulletData.trace_length_remaining = pCSWeaponData->m_flRange - BulletData.trace_length;
		auto vecEnd = BulletData.src + BulletData.direction * BulletData.trace_length_remaining;
		UTIL_TraceLine( BulletData.src, vecEnd, 0x4600400B, pBaseEntity, &BulletData.enter_trace );

		if( BulletData.enter_trace.fraction == 1.0f )
			break;

		if( ( BulletData.enter_trace.hitgroup <= 7 ) && ( BulletData.enter_trace.hitgroup > 0 ) )
		{
			BulletData.trace_length += BulletData.enter_trace.fraction * BulletData.trace_length_remaining;
			BulletData.current_damage *= ( float )pow( pCSWeaponData->m_flRangeModifier, BulletData.trace_length * 0.002 );
			ScaleDamage( BulletData.enter_trace.hitgroup, BulletData.enter_trace.m_pEnt, pCSWeaponData->m_flWeaponArmorRatio, BulletData.current_damage );

			return true;
		}

		if( !HandleBulletPenetration( pCSWeaponData, BulletData ) )
			break;
	}

	return false;
}

bool CTools::TraceDidHitWorld( IEngineTrace::trace_t* pTrace )
{
	if( !g_pEntityList )
		return false;

	return( pTrace->m_pEnt == g_pEntityList->GetBaseEntity( 0 ) );
}

bool CTools::TraceDidHitNonWorldEntity( IEngineTrace::trace_t* pTrace )
{
	if( !pTrace )
		return false;

	if( pTrace->m_pEnt == NULL )
		return false;

	if( TraceDidHitWorld( pTrace ) )
		return false;

	return true;
}

bool CTools::TraceToExit( Vector& vecEnd, IEngineTrace::trace_t* pEnterTrace, Vector vecStart, Vector vecDir, IEngineTrace::trace_t* pExitTrace )
{
	auto flDistance = 0.f;
	while( flDistance <= 90.0f )
	{
		flDistance += 4.f;
		vecEnd = vecStart + vecDir * flDistance;

		auto iPointContents = g_pEngineTrace->GetPointContents( vecEnd, MASK_SHOT_HULL | CONTENTS_HITBOX, NULL );
		if( iPointContents & MASK_SHOT_HULL && ( !( iPointContents & CONTENTS_HITBOX ) ) )
			continue;

		auto vecNewEnd = vecEnd - ( vecDir * 4.0f );
		UTIL_TraceLine( vecEnd, vecNewEnd, 0x4600400B, 0, pExitTrace );

		if( !pExitTrace->m_pEnt )
			return false;

		if( pExitTrace->startSolid && pExitTrace->surface.flags & SURF_HITBOX )
		{
			UTIL_TraceLine( vecEnd, vecStart, 0x600400B, pExitTrace->m_pEnt, pExitTrace );
			if( ( pExitTrace->fraction < 1.0f || pExitTrace->allSolid ) && !pExitTrace->startSolid )
			{
				vecEnd = pExitTrace->endpos;
				return true;
			}
			continue;
		}

		if( !( pExitTrace->fraction < 1.0 || pExitTrace->allSolid || pExitTrace->startSolid ) || pExitTrace->startSolid )
		{
			if( pExitTrace->m_pEnt )
			{
				if( ! TraceDidHitNonWorldEntity( pEnterTrace ) && IsBreakableEntity( pEnterTrace->m_pEnt ) )
					return true;
			}
			continue;
		}

		if( ( ( pExitTrace->surface.flags >> 7 ) & 1 ) && !( ( pEnterTrace->surface.flags >> 7 ) & 1 ) )
			continue;


		if( pExitTrace->plane.normal.Dot( vecDir ) <= 1.0f )
		{
			auto flFraction = pExitTrace->fraction * 4.0f;
			vecEnd = vecEnd - ( vecDir * flFraction );
			return true;
		}
	}
	return false;
}

bool CTools::WorldToScreen( const Vector& vecOrigin, Vector& vecScreen )
{
	if( !g_pDebugOverlay )
		return false;

	return( g_pDebugOverlay->ScreenPoint( vecOrigin, vecScreen ) != 1 );
}

CBaseEntity* CTools::GetLocalPlayer( void )
{
	if( !g_pEntityList || !g_pEngine )
		return nullptr;

	int iIndex = g_pEngine->GetLocalPlayer( );
	if( iIndex <= 0 || iIndex > 64 )
		return nullptr;

	return g_pEntityList->GetBaseEntity( iIndex );
}

DWORD_PTR CTools::FindPattern( std::string strModuleName, PBYTE pbPattern, std::string strMask, DWORD_PTR nCodeBase, DWORD_PTR nSizeOfCode )
{
	BOOL bPatternDidMatch = FALSE;
	HMODULE hModule = GetModuleHandleA( strModuleName.c_str( ) );

	if( !hModule )
		return 0;

	PIMAGE_DOS_HEADER pDsHeader = PIMAGE_DOS_HEADER( hModule );
	PIMAGE_NT_HEADERS pPeHeader = PIMAGE_NT_HEADERS( LONG( hModule ) + pDsHeader->e_lfanew );
	PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pPeHeader->OptionalHeader;

	if( !nCodeBase )
		nCodeBase = ( ULONG )hModule + pOptionalHeader->BaseOfCode;

	if( !nSizeOfCode )
		nSizeOfCode = pOptionalHeader->SizeOfCode;

	std::size_t nMaskSize = strMask.length( );

	if( !nCodeBase || !nSizeOfCode || !nMaskSize )
		return 0;

	for( DWORD_PTR i = nCodeBase; i <= nCodeBase + nSizeOfCode; i++ )
	{
		for( size_t t = 0; t < nMaskSize; t++ )
		{
			if( *( ( PBYTE )i + t ) == pbPattern[ t ] || strMask.c_str( )[ t ] == '?' )
				bPatternDidMatch = TRUE;

			else
			{
				bPatternDidMatch = FALSE;
				break;
			}
		}

		if( bPatternDidMatch )
			return i;
	}

	return 0;
}

float CTools::DotProduct( const float *v1, const float *v2 )
{
	return v1[ 0 ] * v2[ 0 ] + v1[ 1 ] * v2[ 1 ] + v1[ 2 ] * v2[ 2 ];
}

float CTools::DotProduct( const Vector& v1, const Vector& v2 )
{
	return DotProduct( &v1.x, &v2.x );
}

float CTools::GetDistance( const Vector& vecOrigin, const Vector& vecOther )
{
	auto flDistance = sqrt( ( vecOrigin - vecOther ).Length( ) );
	if( flDistance < 1.0 )
		flDistance = 1.0;

	return flDistance;
}

float CTools::GetFoV( QAngle qAngles, Vector vecSource, Vector vecDestination, bool bDistanceBased )
{
	Vector ang, aim;
	double fov;

	CalcAngle( vecSource, vecDestination, ang );
	MakeVector( qAngles, aim );
	MakeVector( ang, ang );

	auto mag_s = sqrt( ( aim[ 0 ] * aim[ 0 ] ) + ( aim[ 1 ] * aim[ 1 ] ) + ( aim[ 2 ] * aim[ 2 ] ) );
	auto mag_d = sqrt( ( aim[ 0 ] * aim[ 0 ] ) + ( aim[ 1 ] * aim[ 1 ] ) + ( aim[ 2 ] * aim[ 2 ] ) );
	auto u_dot_v = aim[ 0 ] * ang[ 0 ] + aim[ 1 ] * ang[ 1 ] + aim[ 2 ] * ang[ 2 ];

	fov = acos( u_dot_v / ( mag_s*mag_d ) ) * ( 180.f / M_PI );

	if( bDistanceBased )
	{
		fov *= 1.4;
		float xDist = abs( vecSource[ 0 ] - vecDestination[ 0 ] );
		float yDist = abs( vecSource[ 1 ] - vecDestination[ 1 ] );
		float Distance = sqrt( ( xDist * xDist ) + ( yDist * yDist ) );

		Distance /= 650.f;

		if( Distance < 0.7f )
			Distance = 0.7f;

		if( Distance > 6.5 )
			Distance = 6.5;

		fov *= Distance;
	}

	return ( float )fov;
}

float CTools::GetHitgroupDamageMult( int iHitgroup )
{
	switch( iHitgroup )
	{
	case HITGROUP_GENERIC:
		return 1.f;
	case HITGROUP_HEAD:
		return 4.f;
	case HITGROUP_CHEST:
		return 1.f;
	case HITGROUP_STOMACH:
		return 1.5f;
	case HITGROUP_LEFTARM:
		return 1.f;
	case HITGROUP_RIGHTARM:
		return 1.f;
	case HITGROUP_LEFTLEG:
		return 0.75f;
	case HITGROUP_RIGHTLEG:
		return 0.75f;
	case HITGROUP_GEAR:
		return 1.f;
	default:
		break;
	}

	return 1.f;
}

IMaterial* CTools::CreateMaterial( bool bFullbright, bool bIgnorez )
{
	char pszMaterial[ 2048 ];

	std::string strMaterialType = ( bFullbright ? "UnlitGeneric" : "VertexLitGeneric" );
	std::string strMaterial( ( bIgnorez ? MAT_IGNOREZ( strMaterialType ) : MAT( strMaterialType ) ) );
	sprintf_s( pszMaterial, strMaterial.c_str( ) );

	auto pKeyValues = new KeyValues( strMaterialType.c_str( ) );

	char szMaterialName[ 128 ];
	GenerateRandomString( szMaterialName, 17 );
	strcat_s( szMaterialName, ".vmt" );

	pKeyValues->LoadFromBuffer( pKeyValues, szMaterialName, pszMaterial );

	auto pNewMaterial = g_pMaterialSystem->CreateMaterial( szMaterialName, pKeyValues );

	if( pNewMaterial )
		pNewMaterial->IncrementReferenceCount( );

	return pNewMaterial;
}

IMaterial* CTools::CreateMaterial( bool bShouldIgnoreZ, bool bFullBright, bool bIsWireframe )
{
	static int iCreated = 0;

	static const char szTmp[ ] =
	{
		"\"%s\"\
		\n{\
		\n\t\"$basetexture\" \"VGUI/white_additive\"\
		\n\t\"$model\" \"1\"\
		\n\t\"$nocull\" \"1\"\
		\n\t\"$nofog\" \"1\"\
		\n\t\"$ignorez\" \"%i\"\
		\n\t\"$znearer\" \"1\"\
		\n\t\"halflambert\" \"1\"\
		\n\t\"$wireframe\" \"%i\"\
		\n}\n"
	};

	char szMaterial[ 512 ];
	char szBaseType[ 64 ];

	if( bFullBright )
	{
		static const char pszBaseType[ ] = "UnlitGeneric";
		sprintf_s( szMaterial, sizeof( szMaterial ), szTmp, pszBaseType, ( bShouldIgnoreZ ) ? 1 : 0, ( bIsWireframe ) ? 1 : 0 );
		strcpy_s( szBaseType, pszBaseType );
	}
	else
	{
		static const char pszBaseType[ ] = "VertexLitGeneric";
		sprintf_s( szMaterial, sizeof( szMaterial ), szTmp, pszBaseType, ( bShouldIgnoreZ ) ? 1 : 0, ( bIsWireframe ) ? 1 : 0 );
		strcpy_s( szBaseType, pszBaseType );
	}	

	char szName[ 512 ];
	sprintf_s( szName, sizeof( szName ), "custom_material_%i.vmt", iCreated );

	++iCreated;

	auto pKeyValues = new KeyValues( szBaseType );
	pKeyValues->LoadFromBuffer( pKeyValues, szName, szMaterial );
	auto pCreatedMaterial = g_pMaterialSystem->CreateMaterial( szName, pKeyValues );
	pCreatedMaterial->IncrementReferenceCount( );
	return pCreatedMaterial;
}

mstudiobbox_t* CTools::GetHitboxData( CBaseEntity* pBaseEntity, int iHitbox )
{
	if( !g_pModelInfo )
		return nullptr;

	if( iHitbox >= HITBOX_MAX )
		return nullptr;

	const model_t* pModel = pBaseEntity->GetModel( );
	if( !pModel )
		return nullptr;

	studiohdr_t* pStudioHdr = g_pModelInfo->GetStudioModel( pModel );
	if( !pStudioHdr )
		return nullptr;

	return pStudioHdr->pHitbox( iHitbox, 0 );
}

PlayerData* CTools::GetPlayerData( int iIndex )
{
	for( int i = 0; i < 64; i++ )
		if( m_PlayerData[ i ].m_iIndex == iIndex )
			return &m_PlayerData[ i ];

	return nullptr;
}

QAngle CTools::GetAntiAimAngles( CBaseEntity* pBaseEntity, bool bEnemyOnly )
{
	if( !pBaseEntity )
		return QAngle( 0.f, 0.f, 0.f );

	auto flMaxDistance = 9999.f;
	auto qAntiAimAngles = QAngle( 0.f, -90.f, 0.f );

	for( int i = 1; i < g_pEngine->GetMaxClients( ); i++ )
	{
		CBaseEntity* pEntity = g_pEntityList->GetBaseEntity( i );
		if( !pEntity )
			continue;

		if( !pEntity->IsValid( ) )
			continue;

		if( bEnemyOnly && pBaseEntity->GetTeam( ) == pEntity->GetTeam( ) )
			continue;

		auto vecCurPos = pBaseEntity->GetAbsOrigin( );
		auto vecTargetPos = pEntity->GetAbsOrigin( );

		float flDistance = GetDistance( vecTargetPos, vecCurPos );
		if( flDistance < flMaxDistance )
		{
			flMaxDistance = flDistance;
			CalcAngle( vecCurPos, vecTargetPos, qAntiAimAngles );
			NormalizeVector( qAntiAimAngles );
		}
	}

	return qAntiAimAngles;
}

void CTools::AngleVectors( const QAngle& qAngles, Vector& vecForward )
{
	float sp, sy, cp, cy;
	SinCos( ( float )( qAngles[ 1 ] * ( M_PI / 180.f ) ), &sy, &cy );
	SinCos( ( float )( qAngles[ 0 ] * ( M_PI / 180.f ) ), &sp, &cp );

	vecForward[ 0 ] = cp*cy;
	vecForward[ 1 ] = cp*sy;
	vecForward[ 2 ] = -sp;
}

void CTools::CalcAngle( const Vector& vecSource, const Vector& vecDestination, QAngle& qAngles )
{
	QAngle delta = QAngle( ( vecSource[ 0 ] - vecDestination[ 0 ] ), ( vecSource[ 1 ] - vecDestination[ 1 ] ), ( vecSource[ 2 ] - vecDestination[ 2 ] ) );
	double hyp = sqrtf( delta[ 0 ] * delta[ 0 ] + delta[ 1 ] * delta[ 1 ] );
	qAngles[ 0 ] = ( float )( atan( delta[ 2 ] / hyp ) * ( 180.0 / M_PI ) );
	qAngles[ 1 ] = ( float )( atan( delta[ 1 ] / delta[ 0 ] ) * ( 180.0 / M_PI ) );
	qAngles[ 2 ] = 0.f;
	if( delta[ 0 ] >= 0.f )
		qAngles[ 1 ] += 180.f;
}

void CTools::ClampAngles( QAngle& qAngles )
{
	if( qAngles.x > 89.0f )
		qAngles.x = 89.0f;

	if( qAngles.x < -89.0f )
		qAngles.x = -89.0f;

	if( qAngles.y > 180 )
		qAngles.y = 180;

	if( qAngles.y < -180 )
		qAngles.y = -180;

	qAngles.z = 0;
}

void CTools::UTIL_TraceLine( const Vector& vecStart, const Vector& vecEnd, unsigned int nMask, CBaseEntity* pCSIgnore, IEngineTrace::trace_t* pTrace )
{
	IEngineTrace::CTraceFilter TraceFilter( pCSIgnore );
	IEngineTrace::Ray_t ray;
	ray.Init( vecStart, vecEnd );

	g_pEngineTrace->TraceRay( ray, nMask, &TraceFilter, pTrace );
}

void CTools::ForceFullUpdate( void )
{
	static PVOID pClientState = NULL;
	if( !pClientState )
		pClientState = **( PVOID** )( FindPattern( "engine.dll", ( PBYTE )"\x8B\x3D\x00\x00\x00\x00\x8A\xF9", "xx????xx" ) + 0x2 );

	if( !pClientState )
		return;

	static DWORD dwFreeEntityBaselines = 0;
	if( !dwFreeEntityBaselines )
		dwFreeEntityBaselines = FindPattern( "engine.dll",( PBYTE )"\xE8\x00\x00\x00\x00\x68\x00\x00\x00\x00\x68\x00\x00\x00\x00\xC7\x87\x00\x00\x00\x00\x00\x00\x00\x00", "x????x????x????xx????????" );

	if( !dwFreeEntityBaselines )
		return;

	static DWORD dwRelAddress = *( DWORD* )( dwFreeEntityBaselines + 0x1 );
	static DWORD sub_B5E60 = ( ( dwFreeEntityBaselines + 0x5 ) + dwRelAddress );

	__asm
	{
		PUSHAD
		MOV	EDI, pClientState
		LEA	ECX, DWORD PTR[ EDI + 0x8 ]
		CALL sub_B5E60
		MOV	DWORD PTR[ EDI + 0x154 ], 0xFFFFFFFF
		POPAD
	}
}

void CTools::ForceMaterial( Color color, IMaterial* material, bool useColor, bool forceMaterial )
{
	if( useColor )
	{
		float blend[ 3 ] = { color.R< float >( ) / 255, color.G< float >( ) / 255, color.B< float >( ) / 255 };
		float alpha = color.A< float >( ) / 255;

		g_pRenderView->SetBlend( alpha );
		g_pRenderView->SetColorModulation( blend );
	}

	if( forceMaterial )
		g_pModelRender->ForcedMaterialOverride( material );
}

void CTools::MakeVector( QAngle qAngles, Vector& vecOut )
{
	auto pitch = float( qAngles[ 0 ] * M_PI / 180.f );
	auto yaw = float( qAngles[ 1 ] * M_PI / 180.f );
	auto tmp = float( cos( pitch ) );
	vecOut[ 0 ] = float( -tmp * -cos( yaw ) );
	vecOut[ 1 ] = float( sin( yaw )*tmp );
	vecOut[ 2 ] = float( -sin( pitch ) );
}

void CTools::MatrixToVector( const matrix3x4& pMatrix, Vector& out )
{
	out[ 0 ] = pMatrix[ 0 ][ 3 ];
	out[ 1 ] = pMatrix[ 1 ][ 3 ];
	out[ 2 ] = pMatrix[ 2 ][ 3 ];
}

void CTools::NormalizeVector( Vector& vecIn )
{
	for( int axis = 0; axis < 3; ++axis )
	{
		while( vecIn[ axis ] > 180.f )
			vecIn[ axis ] -= 360.f;

		while( vecIn[ axis ] < -180.f )
			vecIn[ axis ] += 360.f;

	}

	vecIn[ 2 ] = 0.f;
}

void CTools::ScaleDamage( int iHitgroup, CBaseEntity* pBaseEntity, float flWeaponArmorRatio, float& flDamage )
{
	if( !pBaseEntity )
		return;

	flDamage *= GetHitgroupDamageMult( iHitgroup );

	if( pBaseEntity->GetArmorValue( ) > 0 )
	{
		if( iHitgroup == HITGROUP_HEAD )
		{
			if( pBaseEntity->HasHelmet( ) )
				flDamage *= ( flWeaponArmorRatio * 1.5f );
		}
		else flDamage *= ( flWeaponArmorRatio * 0.5f );
	}
}

void CTools::SinCos( float flRadians, float* pflSine, float* pflCosine )
{
	__asm
	{
		fld	DWORD PTR[ flRadians ]
		fsincos
		mov edx, DWORD PTR[ pflCosine ]
		mov eax, DWORD PTR[ pflSine ]
		fstp DWORD PTR[ edx ]
		fstp DWORD PTR[ eax ]
	}
}

void CTools::VectorAngles( const Vector &vecForward, Vector &vecAngles )
{
	Vector vecView;
	if( vecForward[ 1 ] == 0.f && vecForward[ 0 ] == 0.f )
	{
		vecView[ 0 ] = 0.f;
		vecView[ 1 ] = 0.f;
	}
	else
	{
		vecView[ 1 ] = atan2( vecForward[ 1 ], vecForward[ 0 ] ) * 180.f / M_PI;

		if( vecView[ 1 ] < 0.f )
			vecView[ 1 ] += 360.f;

		vecView[ 2 ] = sqrt( vecForward[ 0 ] * vecForward[ 0 ] + vecForward[ 1 ] * vecForward[ 1 ] );

		vecView[ 0 ] = atan2( vecForward[ 2 ], vecView[ 2 ] ) * 180.f / M_PI;
	}

	vecAngles[ 0 ] = -vecView[ 0 ];
	vecAngles[ 1 ] = vecView[ 1 ];
	vecAngles[ 2 ] = 0.f;
}

void CTools::VectorTransform( const float *in1, const matrix3x4& in2, float *out )
{
	Assert( in1 != out );
	out[ 0 ] = DotProduct( in1, in2[ 0 ] ) + in2[ 0 ][ 3 ];
	out[ 1 ] = DotProduct( in1, in2[ 1 ] ) + in2[ 1 ][ 3 ];
	out[ 2 ] = DotProduct( in1, in2[ 2 ] ) + in2[ 2 ][ 3 ];
}

void CTools::VectorTransform( const Vector& in1, const matrix3x4& in2, Vector& out )
{
	VectorTransform( &in1.x, in2, &out.x );
}

void CTools::ClearPlayerData( void )
{
	for( int i = 0; i < 64; i++ )
		m_PlayerData[ i ].Reset( );
}

ValveSDK::CEntityList* g_pEntityList = nullptr;
ValveSDK::CGlobalVarsBase* g_pGlobalVarsBase = nullptr;
ValveSDK::IGameMovement* g_pGameMovement = nullptr;
ValveSDK::CGlowObjectManager* g_pGlowObjectManager = nullptr;
ValveSDK::CHLClient* g_pClient = nullptr;
ValveSDK::CInput* g_pInput = nullptr;
ValveSDK::IMoveHelper* g_pMoveHelper = nullptr;
ValveSDK::IPrediction* g_pPrediction = nullptr;
ValveSDK::IDebugOverlay* g_pDebugOverlay = nullptr;
ValveSDK::IEngineClient* g_pEngine = nullptr;
ValveSDK::IEngineTrace* g_pEngineTrace = nullptr;
ValveSDK::IGameEventManager2* g_pGameEventManager = nullptr;
ValveSDK::IModelInfo* g_pModelInfo = nullptr;
ValveSDK::IModelRender* g_pModelRender = nullptr;
ValveSDK::IRenderView* g_pRenderView = nullptr;
ValveSDK::IMaterialSystem* g_pMaterialSystem = nullptr;
ValveSDK::IPhysicsSurfaceProps* g_pPhysSurface = nullptr;
ValveSDK::IPanel* g_pPanel = nullptr;
ValveSDK::ISurface* g_pSurface = nullptr;
ValveSDK::CRenderSurface* g_pRenderSurface = nullptr;
ValveSDK::CTools* g_pTools = nullptr;
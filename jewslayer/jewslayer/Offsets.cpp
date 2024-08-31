#include "Offsets.h"
#include "NetVars.h"

namespace Offsets
{
	DWORD m_bIsBroken = 0;
	DWORD m_bGunGameImmunity = 0;
	DWORD m_bIsDefusing = 0;
	DWORD m_bIsScoped = 0;
	DWORD m_bHasHelmet = 0;
	DWORD m_moveType = 0;
	DWORD m_fFlags = 0;
	DWORD m_lifeState = 0;
	DWORD m_hActiveWeapon = 0;
	DWORD m_hOwnerEntity = 0;
	DWORD m_ArmorValue = 0;
	DWORD m_CollisionGroup = 0;
	DWORD m_iAccount = 0;
	DWORD m_iShotsFired = 0;
	DWORD m_iTeamNum = 0;
	DWORD m_iHealth = 0;
	DWORD m_nHitboxSet = 0;
	DWORD m_nTickBase = 0;
	DWORD m_viewPunchAngle = 0;
	DWORD m_aimPunchAngle = 0;
	DWORD m_vecOrigin = 0;
	DWORD m_vecViewOffset = 0;
	DWORD m_vecVelocity = 0;
	DWORD m_iItemDefinitionIndex = 0;
	DWORD m_OriginalOwnerXuidLow = 0;
	DWORD m_OriginalOwnerXuidHigh = 0;
	DWORD m_nFallbackPaintKit = 0;
	DWORD m_nFallbackSeed = 0;
	DWORD m_flFallbackWear = 0;
	DWORD m_iItemIDHigh = 0;
	DWORD m_nFallbackStatTrak = 0;
	DWORD m_iClip1 = 0;
	DWORD m_iClip2 = 0;
	DWORD m_iState = 0;
	DWORD m_flNextPrimaryAttack = 0;
	DWORD m_flNextSecondaryAttack = 0;
	DWORD m_dwLoadFromBuffer = 0;
}

void InitOffsets( void )
{
	Offsets::m_bIsDefusing = g_pNetVars->GetOffset( "DT_CSPlayer", "m_bIsDefusing" );
	Offsets::m_bIsBroken = g_pNetVars->GetOffset( "DT_BreakableSurface", "m_bIsBroken" );
	Offsets::m_bIsScoped = g_pNetVars->GetOffset( "DT_CSPlayer", "m_bIsScoped" );
	Offsets::m_bGunGameImmunity = g_pNetVars->GetOffset( "DT_CSPlayer", "m_bGunGameImmunity" );
	Offsets::m_bIsDefusing = g_pNetVars->GetOffset( "DT_CSPlayer", "m_bIsDefusing" );
	Offsets::m_bHasHelmet = g_pNetVars->GetOffset( "DT_CSPlayer", "m_bHasHelmet" );
	Offsets::m_moveType = g_pNetVars->GetOffset( "DT_CSPlayer", "m_nRenderMode" ) + 0x1;
	Offsets::m_fFlags = g_pNetVars->GetOffset( "DT_CSPlayer", "m_fFlags" );
	Offsets::m_lifeState = g_pNetVars->GetOffset( "DT_CSPlayer", "m_lifeState" );
	Offsets::m_hActiveWeapon = g_pNetVars->GetOffset( "DT_BaseCombatCharacter", "m_hActiveWeapon" );
	Offsets::m_hOwnerEntity = g_pNetVars->GetOffset( "DT_CSPlayer", "m_hOwnerEntity" );
	Offsets::m_ArmorValue = g_pNetVars->GetOffset( "DT_CSPlayer", "m_ArmorValue" );
	Offsets::m_CollisionGroup = g_pNetVars->GetOffset( "DT_PlantedC4", "m_CollisionGroup" );
	Offsets::m_iShotsFired = g_pNetVars->GetOffset( "DT_CSPlayer", "m_iShotsFired" );
	Offsets::m_iAccount = g_pNetVars->GetOffset( "DT_CSPlayer", "m_iAccount" );
	Offsets::m_iTeamNum = g_pNetVars->GetOffset( "DT_CSPlayer", "m_iTeamNum" );
	Offsets::m_iHealth = g_pNetVars->GetOffset( "DT_CSPlayer", "m_iHealth" );
	Offsets::m_nHitboxSet = g_pNetVars->GetOffset( "DT_CSPlayer", "m_nHitboxSet" );
	Offsets::m_nTickBase = g_pNetVars->GetOffset( "DT_CSPlayer", "m_nTickBase" );
	Offsets::m_viewPunchAngle = g_pNetVars->GetOffset( "DT_CSPlayer", "m_viewPunchAngle" );
	Offsets::m_aimPunchAngle = g_pNetVars->GetOffset( "DT_CSPlayer", "m_aimPunchAngle" );
	Offsets::m_iItemDefinitionIndex = g_pNetVars->GetOffset( "DT_BaseCombatWeapon", "m_iItemDefinitionIndex" );
	Offsets::m_OriginalOwnerXuidLow = g_pNetVars->GetOffset( "DT_BaseCombatWeapon", "m_OriginalOwnerXuidLow" );
	Offsets::m_OriginalOwnerXuidHigh = g_pNetVars->GetOffset( "DT_BaseCombatWeapon", "m_OriginalOwnerXuidHigh" );
	Offsets::m_nFallbackPaintKit = g_pNetVars->GetOffset( "DT_BaseCombatWeapon", "m_nFallbackPaintKit" );
	Offsets::m_nFallbackSeed = g_pNetVars->GetOffset( "DT_BaseCombatWeapon", "m_nFallbackSeed" );
	Offsets::m_flFallbackWear = g_pNetVars->GetOffset( "DT_BaseCombatWeapon", "m_flFallbackWear" );
	Offsets::m_iItemIDHigh = g_pNetVars->GetOffset( "DT_BaseCombatWeapon", "m_iItemIDHigh" );
	Offsets::m_nFallbackStatTrak = g_pNetVars->GetOffset( "DT_BaseCombatWeapon", "m_nFallbackStatTrak" );
	Offsets::m_iClip1 = g_pNetVars->GetOffset( "DT_BaseCombatWeapon", "m_iClip1" );
	Offsets::m_iClip2 = g_pNetVars->GetOffset( "DT_BaseCombatWeapon", "m_iClip2" );
	Offsets::m_iState = g_pNetVars->GetOffset( "DT_BaseCombatWeapon", "m_iState" );
	Offsets::m_flNextPrimaryAttack = g_pNetVars->GetOffset( "DT_BaseCombatWeapon", "m_flNextPrimaryAttack" );
	Offsets::m_flNextSecondaryAttack = g_pNetVars->GetOffset( "DT_BaseCombatWeapon", "m_flNextSecondaryAttack" );
	Offsets::m_vecOrigin = 0x134;
	Offsets::m_vecViewOffset = 0x104;
	Offsets::m_vecVelocity = 0x110;
}
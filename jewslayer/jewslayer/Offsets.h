#ifndef __SDK_OFFSETS_H__
#define __SDK_OFFSETS_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"

namespace Offsets
{
	// Player
	extern DWORD m_bIsBroken;
	extern DWORD m_bGunGameImmunity;
	extern DWORD m_bIsDefusing;
	extern DWORD m_bIsScoped;
	extern DWORD m_bHasHelmet;
	extern DWORD m_moveType;
	extern DWORD m_fFlags;
	extern DWORD m_lifeState;
	extern DWORD m_hActiveWeapon;
	extern DWORD m_hOwnerEntity;
	extern DWORD m_ArmorValue;
	extern DWORD m_CollisionGroup;
	extern DWORD m_iAccount;
	extern DWORD m_iShotsFired;
	extern DWORD m_iTeamNum;
	extern DWORD m_iHealth;
	extern DWORD m_nHitboxSet;
	extern DWORD m_nTickBase;
	extern DWORD m_viewPunchAngle;
	extern DWORD m_aimPunchAngle;
	extern DWORD m_vecOrigin;
	extern DWORD m_vecViewOffset;
	extern DWORD m_vecVelocity;

	// Weapon / Item
	extern DWORD m_iItemDefinitionIndex;
	extern DWORD m_OriginalOwnerXuidLow;
	extern DWORD m_OriginalOwnerXuidHigh;
	extern DWORD m_nFallbackPaintKit;
	extern DWORD m_nFallbackSeed;
	extern DWORD m_flFallbackWear;
	extern DWORD m_iItemIDHigh;
	extern DWORD m_nFallbackStatTrak;
	extern DWORD m_iClip1;
	extern DWORD m_iClip2;
	extern DWORD m_iState;
	extern DWORD m_flNextPrimaryAttack;
	extern DWORD m_flNextSecondaryAttack;

	extern DWORD m_dwLoadFromBuffer;
}

extern void InitOffsets( void );

#endif
#pragma once

#include "main.h"

#define ptr( x, x1, x2 ) *(x*)( (DWORD)x1 + (DWORD)x2 )

class CBaseEntity {
public:
	inline void *renderable() {
		return this + 0x4;
	}
	inline void *networkable() {
		return this + 0x8;
	}

	inline Vector &GetAbsOrigin() {
		typedef Vector &(__thiscall *OrigFn)( void * );
		return getvFunc<OrigFn>(this, 10)( this );
	}
	inline Vector &GetAngles() {
		typedef Vector &(__thiscall *OrigFn)( void * );
		return getvFunc<OrigFn>(this, 11)( this );
	}
	inline void *GetModel() {
		typedef void *(__thiscall *OrigFn)( void * );
		return getvFunc<OrigFn>(this, 54)( this );
	}
	inline ClientClass *GetClientClass() {
		void *_this = networkable();
		typedef ClientClass *(__thiscall *OrigFn)( void * );
		return getvFunc<OrigFn>(_this, 2)( _this );
	}
	inline bool IsDormant() {
		void *_this = networkable();
		typedef bool (__thiscall *OrigFn)( void * );
		return getvFunc<OrigFn>(_this, 9)( _this );
	}
	inline int GetIndex() {
		void *_this = networkable();
		typedef int (__thiscall *OrigFn)( void * );
		return getvFunc<OrigFn>(_this, 10)( _this );
	}
	inline void DrawModel() {
		void *_this = renderable();
		typedef void (__thiscall *OrigFn)( void *, int, void * );
		getvFunc<OrigFn>(_this, 9)( _this, 1, 0 );
	}
	inline bool SetupBones( matrix3x4_t *pBoneToWorldOut ) {
		void *_this = renderable();
		typedef bool (__thiscall *OrigFn)( void *, matrix3x4_t *, int, int, float );
		return getvFunc<OrigFn>(_this, 13)( _this, pBoneToWorldOut, 128, 0x100, 0 );
	}
	inline void GetRenderBounds( Vector &mins, Vector &maxs ) {
		void *_this = renderable();
		typedef void (__thiscall *OrigFn)( void *, Vector &, Vector & );
		getvFunc<OrigFn>(_this, 17)( _this, mins, maxs );
	}
	inline matrix3x4_t &RenderableToWorldTransform() {
		void *_this = renderable();
		typedef matrix3x4_t &(__thiscall *OrigFn)( void * );
		return getvFunc<OrigFn>(_this, 31)( _this );
	}
	inline bool GetWeaponData( WeaponInfo &out ) {
		if( !this )
			return false;

		typedef void *(__thiscall *GetWeaponDataFn)( void * );
		void *data = getvFunc<GetWeaponDataFn>(this, 454)( this );
		if( !data )
			return false;

		//msg( "data: 0x%x, pen: 0x%x\n", data, (dword)data + 0x774 ); 0x1A0 // max speed

		out.pen = *(float *)( (DWORD)data + 0x774 );
		out.damage = *(int *)( (DWORD)data + 0x778 );
		out.range = *(float *)( (DWORD)data + 0x77C );
		out.rangeModifier = *(float *)( (DWORD)data + 0x780 );
		out.ratio = *(float *)( (DWORD)data + 0x760 );
		out.cycleTime = *(float *)( (DWORD)data + 0x788 );

		return true;
	}
	inline float GetInnacuracy() {
		typedef float (__thiscall *OrigFn)( void * );
		return getvFunc<OrigFn>(this, 478)( this );
	}
	inline float GetSpread() {
		typedef float (__thiscall *OrigFn)( void * );
		return getvFunc<OrigFn>(this, 479)( this );
	}
	inline void UpdateAccuracyPenalty() {
		typedef void (__thiscall *OrigFn)( void * );
		return getvFunc<OrigFn>(this, 480)( this );
	}

	/*
		Netvars
	*/
	inline int getHealth() {
		return ptr( int, this, netvars->m_iHealth );
	}
	inline int getTeam() {
		if( !this )
			return 0;

		return ptr( int, this, netvars->m_iTeamNum );
	}
	inline int getFlags() {
		return ptr( int, this, netvars->m_fFlags );
	}
	inline int GetMoveType() {
		if( !this )
			return 0;

		return ptr( int, this, 0x258 );
	}
	inline int getActiveWeapon() {
		return ptr( int, this, netvars->m_hActiveWeapon );
	}
	inline int getOwnerEnt() {
		return ptr( int, this, netvars->m_hOwnerEntity );
	}
	inline int getArmor() {
		return ptr( int, this, netvars->m_iArmor );
	}
	inline bool hasHelmet() {
		return ptr( bool, this, netvars->m_bHasHelmet );
	}
	inline int shotsFired() {
		return ptr( int, this, netvars->m_iShotsFired );
	}
	inline bool isScoped() {
		return ptr( bool, this, netvars->m_bIsScoped );
	}
	inline Color getColor() {
		return ptr( Color, this, netvars->m_clrRender );
	}
	//inline dword *getCurrentCommand() { // meme??
	//	return (dword *)( this + 0x16F4 );
	//}
	inline Vector &getVelocity() {
		return ptr( Vector, this, netvars->m_vecVelocity );
	}
	inline Vector getViewPunch() {
		return ptr( Vector, this, netvars->m_viewPunchAngle );
	}
	inline Vector getPunch() {
		return ptr( Vector, this, netvars->m_aimPunchAngle );
	}
	inline int getWeaponClip() {
		return ptr( int, this, netvars->m_iClip1 );
	}
	inline int getWeaponID() {
		return ptr( int, this, netvars->m_iItemDefinitionIndex );
	}
	inline int getPrimaryAmmoType() {
		return ptr( int, this, netvars->m_iPrimaryAmmoType );
	}
	inline int &getTickBase() {
		return ptr( int, this, netvars->m_nTickBase );
	}
	inline int getShotsFired() {
		return ptr( int, this, netvars->m_iShotsFired );
	}
	inline float getNextAttack() {
		return ptr( float, this, netvars->m_flNextAttack );
	}
	inline float getNextPrimaryAttack() {
		return ptr( float, this, netvars->m_flNextPrimaryAttack );
	}
	inline Vector getVecViewOffset() {
		return ptr( Vector, this, netvars->m_vecViewOffset );
	}
	inline Vector getHeadPos() {
		return GetAbsOrigin() + getVecViewOffset();
	}
	inline Vector getMins() {
		return ptr( Vector, this, netvars->m_vecMins );
	}
	inline Vector getMaxs() {
		return ptr( Vector, this, netvars->m_vecMaxs );
	}
	inline float getC4Blow() {
		return ptr( float, this, netvars->m_flC4Blow );
	}
	//inline int getGlowIndex() {
	//	return ptr( int, this, 0x1DCC );
	//}
};

#ifndef _PLAYER_ESP_H_
#define _PLAYER_ESP_H_

#include "SDK.h"

class CPlayerESP
{
public:
	void DrawPlayerESP( int iIndex );
	void DrawBones(int iIndex);
	void DrawRadarPoint(Vector vecOriginx, Vector vecOriginy, Vector vAngle);
	void DrawRadarBack();
	void DrawWorldESP( int iIndex );
	Vector GetEyePosition(CBaseEntity* pEntity);
	void NormalizeAngle(Vector &angles);
	void ClampAngles(Vector &angles);
	bool IsVisible(Vector& vecStart, Vector& vecEnd, CBaseEntity* pEntity);
	bool LifeA;
	//C_BaseCombatWeapon* GetBaseCombatActiveWeapon(CBaseEntity* pBaseEntity);
};


class Spreadz
{
public:
	C_BaseCombatWeapon* GetBaseCombatActiveWeapon(CBaseEntity* pLocal);
	void AngleToVectors(const Vector &angles, Vector *forward, Vector *right, Vector *up);
	void VectorAngles(Vector *forward, Vector *angles);
	float RandomFloat(float min, float max);
	void RandomSeed(UINT seed);
	float GetInaccuracy(C_BaseCombatWeapon *pWeapon);
	float GetSpread(C_BaseCombatWeapon *pWeapon);
	void UpdateAccuracyPenalty(C_BaseCombatWeapon *pWeapon);
	void AngleVectors(const Vector &angles, Vector *forward);
	bool CanShoot();
	void SpreadFactor(CUserCmd *pCmd, C_BaseCombatWeapon *pWeapon);
	Vector LegitAngle(Vector qaAng);
	void Spinbot(CUserCmd* _pCommand);
	void VectorAnglesZ(Vector forward, Vector angles);
	FLOAT FindDistanceZ(CBaseEntity *pPlayer, CBaseEntity *pLocal);
	bool KnifeBot(CBaseEntity *pBaseEntity, CBaseEntity *pLocalEntity);
	float VectorNormalize_Custom(Vector& vec);
	//void AngleVectors(const Vector &angles, Vector *forward);
};

extern Spreadz PSpreadz;
#endif
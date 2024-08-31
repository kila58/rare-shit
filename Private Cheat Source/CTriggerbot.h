#include "SDK.h"
#include "Player ESP.h"
#include "CDrawManager.h"
#include "Control Variables.h"

class CTrigger
{
public:

	//CTrigger();

	void intro(CBaseEntity*   pLocal, CUserCmd* pCmd, C_BaseCombatWeapon *pWeapon);
	bool Triggerbot(CBaseEntity*   pLocal, CUserCmd* cmd);
	bool Trigger(CUserCmd *pCommand, CBaseEntity *pLocal);
	bool IntersectRayWithOBB(const Vector &vecRayStart, const Vector &vecRayDelta, const matrix3x4 &matOBBToWorld, const Vector &vecOBBMins, const Vector &vecOBBMaxs);

	Vector vHead;

	player_info_t pInfo;

	Hitbox_t   Hitbox[21];
};
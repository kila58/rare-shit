#ifndef	_PROTATOR_H
#define	_PROTATOR_H

#include "SDK.h"



#define CONTENTS_MOVEABLE		0x4000

#define	CONTENTS_MONSTER		0x2000000
#define	CONTENTS_EMPTY			0		// No contents

#define	CONTENTS_SOLID			0x1		// an eye is never valid in a solid
#define	CONTENTS_WINDOW			0x2		// translucent, but not watery (glass)
#define	CONTENTS_AUX			0x4
#define	CONTENTS_GRATE			0x8		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define	CONTENTS_SLIME			0x10
#define	CONTENTS_WATER			0x20
#define	CONTENTS_BLOCKLOS		0x40	// block AI line of sight
#define CONTENTS_OPAQUE			0x80	// things that cannot be seen through (may be non-solid though)
#define	LAST_VISIBLE_CONTENTS	0x80
#define	CONTENTS_DEBRIS			0x4000000
#define	MASK_SOLID		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define	CONTENTS_MONSTERCLIP	0x20000
#define MASK_NPCWORLDSTATIC (CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP | CONTENTS_GRATE)

#define FLOW_OUTGOING	0

class PRotator
{
public:

	PRotator();
	//pAim = new PRotator();
	void StealthRotation(CBaseEntity* pLocal, CUserCmd* cmd);


	int		GetTrgtZ(void);
	void	DrapTrgtZ(void);

	float GetFOVZ(Vector& vMyView, Vector& vMyPos, Vector& vHitbox);
	float Get3DDistanceZ(Vector from, Vector to);
	void CalcAngleZ(Vector& src, Vector& dst, Vector &angles);
	void MakeVectorZ(Vector& pfIn, Vector& pfOut);

	void ApplyPrediction(Vector &vAim, Vector &vMe, Vector &vOut, CBaseEntity* pEnt, CBaseEntity* pLocal);
	void ApplySpeedPrediction(Vector &vAim, Vector &vOut, Vector &EntitySpeed, CBaseEntity* pLocal);
	int boneselector();
	bool boneviviblechecker(CBaseEntity* pEntity, CBaseEntity* pLocal);
	Vector GetVelocity(CBaseEntity* pEnt);
	Vector GetPredictedVelocity(CBaseEntity* pEnt);
	bool AutoWall(Vector vPos, CBaseEntity* pLocal, CBaseEntity* pEntity);
	bool HitScans(CBaseEntity* pLocal, CBaseEntity* pTarget, Vector &toAIM);
	bool EdgeAntiAim(CBaseEntity* pLocal, CUserCmd *cmd, float angle);
	BYTE m_MoveType(CBaseEntity* pLocal);
	float GetAntiAimAngles(CBaseEntity* pLocal);
	float GetAntiAimAngles2(CBaseEntity* pLocal);
	bool EdgeAntiAimZ(CBaseEntity *localPlayer, CUserCmd *cmd, float angle);
	Vector Randomize(Vector vAngles);
	void Smooth(Vector& flLocalAngles, float iSmooth);

	int		m_nTarget;
	float	flBestDist;
	bool bShoot;

	float lastX;

	float lastY;

	float destX;

	float destY;

	float curX;

	float curY;

	Vector vHead, vEyePos, vEyePs;
	player_info_t pInfo;
	Vector vAim, Hitbox;
	Vector vPredicted;
	Vector FOV;
	Vector  vSmooth;
	Vector	PredictedTargetPosition;
};


#endif
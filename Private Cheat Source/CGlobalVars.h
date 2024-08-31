#ifndef GLOBALVARS_H
#define GLOBALVARS_H
#include "SDK.h"

int getOffset_deep(char *szClassName, char *szVariable);
int getOffset_deep_sub(RecvTable* pTable,char *szClassName, char *szVariable);
void DumpTable(RecvTable *pTable,FILE* fp);
int getOffset( char *szClassName, char *szVariable );
void DumpOffset(char* file);

class CPlayerVariables
{
public:
	void FindOffset();

	int m_lifeState;
	int m_iHealth;
	bool m_bIsDefusing;
	int m_iClip1;
	int m_ArmorValue;
	int m_iAccount;
	int m_iTeamNum;
	int m_fFlags;
	int m_hOwnerEntity;
	int m_hActiveWeapon;
	int m_hMyWeapons;
	int m_movetype;
	int m_punch;
	int m_visualpunch;
	int m_kit1;
	int m_kit2;
	bool m_bGunGameImmunity;

	int m_CurrentStage;
	int m_flFlashDuration;
	int m_flFlashMaxAlpha;
	int m_CollisionGroup;
	int m_Collision;
	int m_iKills;
};

//extern CPlayerVariables gPlayerVars;

#endif
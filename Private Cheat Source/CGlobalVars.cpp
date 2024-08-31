#include "SDK.h"
#include "CGlobalVars.h"

void CPlayerVariables::FindOffset()
{

	// CTFPlayer
	this->m_iHealth			= getOffset("DT_BasePlayer", "m_iHealth");   // m_iAccount  = DT_CSPlayer
	this->m_iClip1			 = getOffset("DT_LocalWeaponData", "m_iClip1");
	this->m_bIsDefusing		= getOffset("DT_CSPlayer", "m_bIsDefusing");
	this->m_lifeState		= getOffset("DT_BasePlayer", "m_lifeState");
	this->m_iTeamNum		= getOffset("DT_BaseEntity", "m_iTeamNum");
	this->m_fFlags			= getOffset("DT_BasePlayer","m_fFlags");
	this->m_hOwnerEntity	= getOffset("DT_BaseEntity", "m_hOwnerEntity");
	this->m_flFlashDuration = getOffset("DT_CSPlayer","m_flFlashDuration");
	this->m_flFlashMaxAlpha = getOffset("DT_CSPlayer","m_flFlashMaxAlpha");
	this->m_CurrentStage	= getOffset("DT_ParticleSmokeGrenade","m_CurrentStage");
	this->m_ArmorValue		= getOffset("DT_CSPlayer", "m_ArmorValue");
	this->m_bGunGameImmunity = getOffset("DT_CSPlayer", "m_bGunGameImmunity");
	this->m_punch = getOffset("DT_BasePlayer", "m_aimPunchAngle");
	this->m_visualpunch = getOffset("DT_BasePlayer", "m_viewPunchAngle");

	this->m_kit1 = getOffset("DT_EconEntity", "m_nFallbackPaintKit");
	this->m_kit2 = getOffset("DT_BaseAttributableItem", "m_nFallbackPaintKit");
	this->m_CollisionGroup = getOffset("DT_BaseEntity", "m_CollisionGroup");
	this->m_Collision = getOffset("DT_BaseEntity", "m_Collision");
	this->m_iKills = getOffset("DT_CSPlayerResource", "m_iKills");
	this->m_movetype = getOffset("DT_BaseToggle", "m_movementType");
}

//===================================================================================
void DumpOffset(char* file)
{
	FILE *fp;
	fp = fopen ( file , "a+");

	ClientClass *pClass = ALX.pClient->GetAllClasses();

	for( ; pClass; pClass = pClass->NextClass() )
	{
		RecvTable *pTable = pClass->GetTable();

		fprintf(fp, "-- [ %s | [%i] ]\n", pClass->GetName(),pTable->GetNumProps());

		for(int i = 0; i < pTable->GetNumProps(); i++)
		{
			RecvProp *pProp = pTable->GetProp( i );

			if( !pProp ) continue;
			fprintf(fp," -- > %s [0x%.4X] [%s]\n",pProp->GetName(),pProp->GetOffset(),pTable->GetName());

			if (pProp->GetDataTable())
			{
				DumpTable(pProp->GetDataTable(),fp);
			}
		}
		fprintf(fp,"-- END [ %s | [%i] ]\n",pClass->GetName(),pTable->GetNumProps());
	}
	fclose(fp);
}
//===================================================================================
void DumpTable(RecvTable *pTable,FILE* fp)
{
	fprintf(fp, "	-- SUB [ %s | [%i] ]\n",pTable->GetName(),pTable->GetNumProps());

	for(int i = 0; i < pTable->GetNumProps(); i++)
	{
		RecvProp *pProp = pTable->GetProp( i );

		if( !pProp ) continue;
		fprintf(fp,"		-- -- > %s [0x%.4X] [%s]\n",pProp->GetName(),pProp->GetOffset(),pTable->GetName());
		if (pProp->GetDataTable())
			DumpTable(pProp->GetDataTable(),fp);
	}
	fprintf(fp, "	-- END SUB [ %s | [%i] ]\n",pTable->GetName(),pTable->GetNumProps());
}
//===================================================================================
// Currently it was 2 level deep, it was enough.
int getOffset( char *szClassName, char *szVariable )
{
	ClientClass *pClass = ALX.pClient->GetAllClasses();

	for( ; pClass; pClass = pClass->NextClass() )
	{
		RecvTable *pTable = pClass->GetTable();

		if( pTable->GetNumProps() <= 1 ) continue;

		for(int i = 0; i < pTable->GetNumProps(); i++)
		{
			RecvProp *pProp = pTable->GetProp( i );

			if( !pProp ) continue;

			if( streql( pTable->GetName(), szClassName ) && streql( pProp->GetName(), szVariable ) )
			{
#if DEBUG
				gBaseAPI.LogToConsole("Found Offset --> [%s --> 0x%.4X [%s]",pProp->GetName(),pProp->GetOffset(),pTable->GetName());
#endif
				return pProp->GetOffset();
			}
			if (pProp->GetDataTable())
			{
				RecvTable *pTable = pProp->GetDataTable();
				for(int i = 0; i < pTable->GetNumProps(); i++)
				{
					RecvProp *pProp = pTable->GetProp( i );

					if( !pProp ) continue;

					if(streql( pTable->GetName(), szClassName ) && streql( pProp->GetName(), szVariable ) )
					{
#if DEBUG
						gBaseAPI.LogToConsole("Found Offset --> [%s --> 0x%.4X] [%s]",pProp->GetName(),pProp->GetOffset(),pTable->GetName());
#endif
						return pProp->GetOffset();
					}
				}
			}
		} 
	}
	return 0;
}
//============================================================================================
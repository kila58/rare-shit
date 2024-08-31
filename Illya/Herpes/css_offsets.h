/*******************************************************
##     ## ######## ########  ########  ########  ######  
##     ## ##       ##     ## ##     ## ##       ##    ## 
##     ## ##       ##     ## ##     ## ##       ##       
######### ######   ########  ########  ######    ######  
##     ## ##       ##   ##   ##        ##             ## 
##     ## ##       ##    ##  ##        ##       ##    ## 
##     ## ######## ##     ## ##        ########  ###### 
********************************************************/

#include <xstring>

using namespace std;

// Offsets (CSS)

int cssACCURACY;
int cssHEALTH;
int cssOrigin;
int cssEYEPOS;
int cssOBTARG;
int cssCLIP1;
int cssGetFOV;
int cssACTIVEWEP;
int cssVELOCITY;
int cssFLAGS;
int cssPUNCHANGLE;
int cssLIFESTATE;
int cssTEAMNUM;
int cssTickBase;
int cssPrimary;
int cssAlpha;
int cssLocal;

namespace Netvars
{
	void Initialize();
	void ScanRecursively(RecvTable* recvTable);
	int GetHighestIndex();
	bool HookNetvar(const char* dt, const char* m, void* hook = NULL);
	int GetNetvar(const char* dt, const char* m);
}

RecvTable* recvTables[8192];

int Netvars::GetHighestIndex()
{
	for (int i = 0; i < (sizeof(recvTables) / 4); i++)
	if (!recvTables[i])
		return i;

	return 0;
}

void Netvars::ScanRecursively(RecvTable* recvTable)
{
	recvTables[GetHighestIndex()] = recvTable;

	for (int i = 0; i < recvTable->m_nProps; i++)
	{
		RecvProp* prop = &recvTable->m_pProps[i];

		if (prop->m_pDataTable)
		{
			bool hasvalue = false;
			for (int x = 0; x < GetHighestIndex(); x++)
			if (recvTables[x] == prop->m_pDataTable)
				hasvalue = true;

			if (!hasvalue)
				ScanRecursively(prop->m_pDataTable);
		}
	}
}

int Netvars::GetNetvar(const char* dt, const char* m)
{
	bool any = dt[0] == '*';

	for (int i = 0; i < GetHighestIndex(); i++)
	if (any || !strcmp(recvTables[i]->m_pNetTableName, dt))
	for (int x = 0; x < recvTables[i]->m_nProps; x++)
	if (!strcmp(recvTables[i]->m_pProps[x].m_pVarName, m))
		return recvTables[i]->m_pProps[x].m_Offset;

	return 0;
}

bool Netvars::HookNetvar(const char* dt, const char* m, void* fn)
{
	bool any = dt[0] == '*';

	for (int i = 0; i < GetHighestIndex(); i++)
	if (any || !strcmp(recvTables[i]->m_pNetTableName, dt))
	for (int x = 0; x < recvTables[i]->m_nProps; x++)
	if (!strcmp(recvTables[i]->m_pProps[x].m_pVarName, m))
		recvTables[i]->m_pProps[x].m_ProxyFn = (RecvVarProxyFn) fn;

	return true;
}

void Netvars::Initialize()
{
	memset(recvTables, 0, sizeof(recvTables));

	for (ClientClass* CC = m_pClient->GetAllClasses(); CC; CC = CC->m_pNext)
		ScanRecursively(CC->m_pRecvTable);

	#define RESOLVE(DT, VAR)VAR = GetNetvar(#DT, #VAR);
	#define RESOLVE2(DT, VAR, VAR2)VAR = GetNetvar(DT, VAR2);

	RESOLVE2("DT_WeaponPistol", cssACCURACY, "m_flAccuracyPenalty");
	RESOLVE2("DT_BasePlayer", cssHEALTH, "m_iHealth");
	RESOLVE2("DT_LocalActiveWeaponData", cssPrimary, "m_flNextPrimaryAttack");
	RESOLVE2("DT_LocalPlayerExclusive", cssTickBase, "m_nTickBase");
	RESOLVE2("DT_BaseEntity", cssOrigin, "m_vecOrigin");
	RESOLVE2("DT_LocalPlayerExclusive", cssEYEPOS, "m_vecViewOffset[0]");
	RESOLVE2("DT_BasePlayer", cssOBTARG, "m_hObserverTarget");
	RESOLVE2("DT_LocalWeaponData", cssCLIP1, "m_iClip1");
	RESOLVE2("DT_BasePlayer", cssGetFOV, "m_iFOV");
	RESOLVE2("DT_BaseCombatCharacter", cssACTIVEWEP, "m_hActiveWeapon");
	RESOLVE2("DT_BaseEntity", cssVELOCITY, "m_vecVelocity[0]");
	RESOLVE2("DT_BasePlayer", cssFLAGS, "m_fFlags");
	RESOLVE2("DT_Local", cssPUNCHANGLE, "m_vecPunchAngle");
	RESOLVE2("DT_BasePlayer", cssLIFESTATE, "m_lifeState");
	RESOLVE2("DT_BaseEntity", cssTEAMNUM, "m_iTeamNum");
	RESOLVE2("DT_BaseEntity", cssAlpha, "m_clrRender");
	RESOLVE2("DT_BaseEntity", cssAlpha, "m_clrRender");
	RESOLVE2("DT_LocalPlayerExclusive", cssLocal, "m_Local");
	RESOLVE2("DT_Local", cssPUNCHANGLE, "m_vecPunchAngle");

}

// Colors
#define CT_VIS			Color( 0, 0, 255, 255 )
#define CT_NOTVIS		Color( 0, 255, 0, 255 )
#define T_VIS			Color( 255, 255, 0, 255 )
#define T_NOTVIS		Color( 255, 0, 0, 255 )

// Weapons
#define WEAPON_NULL					0
#define WEAPON_AK47					1
#define WEAPON_AUG					2
#define WEAPON_AWP					3
#define WEAPON_DEAGLE				4
#define WEAPON_ELITES				5
#define WEAPON_FAMAS				6
#define WEAPON_FIVESEVEN			7
#define WEAPON_G3SG1				8
#define WEAPON_GALIL				9
#define WEAPON_GLOCK18				10
#define WEAPON_M249					11
#define WEAPON_M3					12
#define WEAPON_M4A1					13
#define WEAPON_MAC10				14
#define WEAPON_MP5					15
#define WEAPON_P228					16
#define WEAPON_P90					17
#define WEAPON_SCOUT				18
#define WEAPON_SG550				19  
#define WEAPON_SG552				20 
#define WEAPON_TMP					21
#define WEAPON_UMP45				22
#define WEAPON_USP45				23
#define WEAPON_XM1014				24
#define WEAPON_KNIFE				25
#define WEAPON_FLASHBANG			26 
#define WEAPON_HE_GRENADE			27
#define WEAPON_SMOKE_GRENADE		28 
#define WEAPON_C4					29

#define TRACE_FLAGS_ISVISIBLE 0x4600400B

// Easy to use
C_BaseEntity *GetPlayerObserverTarget( C_BaseEntity* pEnt )
{
	return ( C_BaseEntity* )( ( DWORD )pEnt + cssOBTARG );
}

int GetPlayerHealth( C_BaseEntity* pEnt )
{
	return *( int* )( ( DWORD )pEnt + cssHEALTH );
}

int GetPlayerTeamNumber( C_BaseEntity* pEnt )
{
	return *( int* )( ( DWORD )pEnt + cssTEAMNUM );
}

int GetPlayerFlags( C_BaseEntity* pEnt )
{
	return *( int* )( ( DWORD )pEnt + cssFLAGS );
}

int GetWeaponState( CBaseCombatWeapon* pWeap )
{
	//return *( int* )( ( DWORD )pWeap + cssWEPSTATE );
	return 0;
}

QAngle *GetPlayerPunchAngle( C_BaseEntity* pEnt )
{
	return ( QAngle* )( ( DWORD )pEnt + cssPUNCHANGLE );
}

QAngle* GetPunchAng(C_BaseEntity* pEnt)
{
	return (QAngle*) ((DWORD) pEnt + (cssLocal + cssPUNCHANGLE));
}

BYTE GetPlayerLifeState( C_BaseEntity* pEnt )
{
	return *( BYTE* )( ( DWORD_PTR )pEnt + cssLIFESTATE );
}

CBaseEntity* GetEntityByIndex( int idx )
{
	if( m_pClientEntList == NULL ) return NULL;

	IClientEntity *pClient = m_pClientEntList->GetClientEntity( idx );

	if( pClient == NULL ) return NULL;

	return pClient->GetBaseEntity();
}

CBaseEntity* GetLocalEntity()
{
	if( m_pEngine == NULL ) return NULL;

	return GetEntityByIndex( m_pEngine->GetLocalPlayer() );
}

bool GetBonePosition( int iBone, Vector& vecOrigin, QAngle qAngles, int index )
{
	if( iBone < 0 || iBone >= 20 )
		return false;
	matrix3x4_t pmatrix[MAXSTUDIOBONES];

	IClientEntity* ClientEntity = m_pClientEntList->GetClientEntity( index );
	if ( ClientEntity == NULL )
		return false;
	if ( ClientEntity->IsDormant() )
		return false;

	IClientRenderable* RenderEntity =  ClientEntity->GetClientRenderable();
	if(	RenderEntity == NULL )
		return false;
	if( RenderEntity->SetupBones( pmatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, m_pGlobals->curtime ) == false )
		return false;

	MatrixAngles( pmatrix[ iBone ], qAngles, vecOrigin );
		return true;
}

Vector GetEyePosition( C_BaseEntity* pEntity )
{
	Vector vecViewOffset;

	QAngle ang;
	if( !GetBonePosition( 14, vecViewOffset, ang, pEntity->index ) )
		return pEntity->GetAbsOrigin();

	return vecViewOffset;
}

Vector EyePos( C_BaseEntity* pEntity )
{
	Vector abs = *(Vector*) ((DWORD) (pEntity) + cssOrigin);//m_vecOrigin
	Vector view = *(Vector *) ((DWORD) (pEntity) + cssEYEPOS);//m_vecViewOffset[0]

	//ripped from Orion, i "made" this func anyway

	return (abs)+(view);
}


bool IsVisible( C_BaseEntity* pEntity )
{
	Ray_t	ray;
	trace_t tr;

	ray.Init( EyePos( GetLocalEntity() ), EyePos( pEntity ) );

	m_pEngineTrace->TraceRay( ray, TRACE_FLAGS_ISVISIBLE | CONTENTS_SOLID | CONTENTS_HITBOX, NULL, &tr );

	return ( tr.m_pEnt == pEntity || tr.fraction == 1.0f );
}

Color GetTeamColor( C_BaseEntity *pEntity )
{
	Color col = Color( 255, 255, 255, 255 );
	int iTeamNum = GetPlayerTeamNumber( pEntity );
	int myTeam = GetPlayerTeamNumber(GetLocalEntity());
	
	if( iTeamNum == myTeam )
	{
		if( IsVisible( pEntity ) )
			col = Color(cvarFriendlyVisibleRed, cvarFriendlyVisibleGreen, cvarFriendlyVisibleBlue, 255);
		else
			col = Color(cvarFriendlyInvisibleRed, cvarFriendlyInvisibleGreen, cvarFriendlyInvisibleBlue, 255);
	}
	else
	{
		if( IsVisible( pEntity ) )
			col = Color(cvarEnemyVisibleRed, cvarEnemyVisibleGreen, cvarEnemyVisibleBlue, 255);
		else
			col = Color(cvarEnemyInvisibleRed, cvarEnemyInvisibleGreen, cvarEnemyInvisibleBlue, 255);
	}

	return col;
}

Color GetHealthColor( float hp )
{
	float g = 2.55 * hp;
	float r = 255 - g;
	Color col( r, g, 0, 255 );
	
	return col;
}

C_BaseCombatWeapon* GetActiveWeapon( C_BaseEntity* pBaseEntity )
{
	/*C_BaseCombatWeapon* result = NULL;
	_asm pushad;
	_asm
	{
		MOV EAX, pBaseEntity;
		MOV EDI, EAX;
		MOV EAX, DWORD PTR DS :[EDI];
		MOV ECX, EDI;
		CALL DWORD PTR DS :[EAX+cssACTIVEWEP];
		MOV result, EAX;
	}
	_asm popad;
	return result;*/
		
	//return 0;// fuk it

	return (C_BaseCombatWeapon*) m_pClientEntList->GetClientEntityFromHandle(*(CBaseHandle*) ((DWORD) pBaseEntity + cssACTIVEWEP)); //(ReadPtr<CBaseHandle>((void*)this, /**/));
}

int GetWeaponID( C_BaseCombatWeapon* pEntity )
{
        std::string modelname = m_pModelInfo->GetModelName( pEntity->GetModel() );
 
        if( modelname.find( "_knife_" ) != string::npos )
                return WEAPON_KNIFE;
 
        if( modelname.find( "_pist_deagle.mdl" ) != string::npos )
                return WEAPON_DEAGLE;
 
        if( modelname.find( "_pist_elite.mdl" ) != string::npos )
                return WEAPON_ELITES;
 
        if( modelname.find( "_pist_fiveseven.mdl" ) != string::npos )
                return WEAPON_FIVESEVEN;
 
        if( modelname.find( "_pist_glock18.mdl" ) != string::npos )
                return WEAPON_GLOCK18;
 
        if( modelname.find( "_pist_p228.mdl" ) != string::npos )
                return WEAPON_P228;
 
        if( modelname.find( "_pist_usp" ) != string::npos )
                return WEAPON_USP45;
 
        if( modelname.find( "_rif_ak47.mdl" ) != string::npos )
                return WEAPON_AK47;
 
        if( modelname.find( "_rif_aug.mdl" ) != string::npos )
                return WEAPON_AUG;
 
        if( modelname.find( "_rif_m4a1" ) != string::npos )
                return WEAPON_M4A1;
 
        if( modelname.find( "_rif_famas.mdl" ) != string::npos )
                return WEAPON_FAMAS;
 
        if( modelname.find( "_rif_galil.mdl" ) != string::npos )
                return WEAPON_GALIL;
 
        if( modelname.find( "_rif_sg552.mdl" ) != string::npos )
                return WEAPON_SG552;
 
        if( modelname.find( "_mach_m249para.mdl" ) != string::npos )
                return WEAPON_M249;
 
        if( modelname.find( "_smg_tmp.mdl" ) != string::npos )
                return WEAPON_TMP;
 
        if( modelname.find( "_smg_mac10.mdl" ) != string::npos )
                return WEAPON_MAC10;
 
        if( modelname.find( "_smg_p90.mdl" ) != string::npos )
                return WEAPON_P90;
 
        if( modelname.find( "_smg_ump45.mdl" ) != string::npos )
                return WEAPON_UMP45;
 
        if( modelname.find( "_smg_mp5.mdl" ) != string::npos )
                return WEAPON_MP5;
 
        if( modelname.find( "_snip_g3sg1.mdl" ) != string::npos )
                return WEAPON_G3SG1;
 
        if( modelname.find( "_snip_scout.mdl" ) != string::npos )
                return WEAPON_SCOUT;
 
        if( modelname.find( "_snip_sg550.mdl" ) != string::npos )
                return WEAPON_SG550;
 
        if( modelname.find( "_snip_awp.mdl" ) != string::npos )
                return WEAPON_AWP;
 
        if( modelname.find( "_shot_xm1014.mdl" ) != string::npos )
                return WEAPON_XM1014;
 
        if( modelname.find( "_shot_m3super90.mdl" ) != string::npos )
                return WEAPON_M3;
 
        if( modelname.find( "_eq_flashbang.mdl" ) != string::npos )
                return WEAPON_FLASHBANG;
 
        if( modelname.find( "_eq_fraggrenade.mdl" ) != string::npos )
                return WEAPON_HE_GRENADE;
 
        if( modelname.find( "_eq_smokegrenade.mdl" ) != string::npos )
                return WEAPON_SMOKE_GRENADE;
 
        if( modelname.find( "_c4.mdl" ) != string::npos )
                return WEAPON_C4;
 
        return 0;
}

bool IsPistol()
{
	C_BaseEntity* pLocal = GetLocalEntity();

	if( !pLocal )
		return false;

	C_BaseCombatWeapon* pWeapon = GetActiveWeapon( pLocal );

	if( !pWeapon )
		return false;

	int WeaponID = GetWeaponID( pWeapon );

	if( !WeaponID )
		return false;

	if( WeaponID == WEAPON_DEAGLE ||
		WeaponID == WEAPON_ELITES ||
		WeaponID == WEAPON_FIVESEVEN ||
		WeaponID == WEAPON_GLOCK18 ||
		WeaponID == WEAPON_P228 ||
		WeaponID == WEAPON_USP45 )
	{
		return true;
	}
	return false;
}

bool BadWeapon()
{
	C_BaseEntity* pLocal = GetLocalEntity();

	if( !pLocal )
		return false;

	C_BaseCombatWeapon* pWeapon = GetActiveWeapon( pLocal );

	if( !pWeapon )
		return false;

	int WeaponID = GetWeaponID( pWeapon );

	if( !WeaponID )
		return false;

	if( WeaponID == WEAPON_KNIFE ||
		WeaponID == WEAPON_FLASHBANG ||
		WeaponID == WEAPON_HE_GRENADE ||
		WeaponID == WEAPON_SMOKE_GRENADE ||
		WeaponID == WEAPON_C4 )
	{
		return true;
	}
	return false;
}

int GetFOV( C_BaseEntity* pEntity )
{
	int iFOV = *( int* )( ( DWORD )pEntity + cssGetFOV );
	if( iFOV == 0 ) iFOV = 90;

	return iFOV;
}

bool HasAmmo()
{
	C_BaseEntity* pLocal = GetLocalEntity();

	if( !pLocal )
		return false;

	C_BaseCombatWeapon* pWeapon = GetActiveWeapon( pLocal );

	if( !pWeapon )
		return false;

	float clip1 = *( float* )( ( DWORD )pWeapon + cssCLIP1 );

	if( clip1 != 0 )
		return true;
	return false;
}

std::string WeaponSpriteName( const char* modelName )
{
	std::string name = "";
	if ( strstr( modelName, "w_pist_usp.mdl" ) )						{name = "a";}
	else if ( strstr( modelName, "w_pist_usp_silencer.mdl" ) )			{name = "a";}
	else if ( strstr( modelName, "w_rif_ak47.mdl" ) )					{name = "b";}
	else if ( strstr( modelName, "w_pist_glock18.mdl" ) )				{name = "c";}
	else if ( strstr( modelName, "w_smg_tmp.mdl" ) )					{name = "d";}
	else if ( strstr( modelName, "w_rif_aug.mdl" ) )					{name = "e";}
	else if ( strstr( modelName, "w_pist_deagle.mdl" ) )				{name = "f";}
	else if ( strstr( modelName, "w_eq_fraggrenade.mdl" ) )				{name = "h";}
	else if ( strstr( modelName, "w_eq_fraggrenade_thrown.mdl" ) )		{name = "h";}
	else if ( strstr( modelName, "w_eq_flashbang_thrown.mdl" ) )		{name = "P";}
	else if ( strstr( modelName, "w_eq_flashbang.mdl" ) )				{name = "P";}
	else if ( strstr( modelName, "w_snip_g3sg1.mdl" ) )					{name = "i";}
	else if ( strstr( modelName, "w_knife_ct.mdl" ) )					{name = "j";}
	else if ( strstr( modelName, "w_knife_t.mdl" ) )					{name = "j";}
	else if ( strstr( modelName, "w_shot_m3super90.mdl" ) )				{name = "k";}
	else if ( strstr( modelName, "w_smg_mac10.mdl" ) )					{name = "l";}
	else if ( strstr( modelName, "w_smg_p90.mdl" ) )					{name = "m";}
	else if ( strstr( modelName, "w_snip_scout.mdl" ) )					{name = "n";}
	else if ( strstr( modelName, "w_snip_sg550.mdl" ) )					{name = "o";}
	else if ( strstr( modelName, "w_eq_smokegrenade.mdl" ) )			{name = "Q";}
	else if ( strstr( modelName, "w_eq_smokegrenade_thrown.mdl" ) )		{name = "Q";}
	else if ( strstr( modelName, "w_smg_ump45.mdl" ) )					{name = "q";}
	else if ( strstr( modelName, "w_snip_awp.mdl" ) )					{name = "r";}
	else if ( strstr( modelName, "w_pist_elite.mdl" ) )					{name = "s";}
	else if ( strstr( modelName, "w_pist_elite_dropped.mdl" ) )			{name = "s";}
	else if ( strstr( modelName, "w_rif_famas.mdl" ) )					{name = "t";}
	else if ( strstr( modelName, "w_pist_fiveseven.mdl" ) )				{name = "u";}
	else if ( strstr( modelName, "w_rif_galil.mdl" ) )					{name = "v";}
	else if ( strstr( modelName, "w_rif_m4a1_silencer.mdl" ) )			{name = "w";}
	else if ( strstr( modelName, "w_rif_m4a1.mdl" ) )					{name = "w";}
	else if ( strstr( modelName, "w_smg_mp5.mdl" ) )					{name = "x";}
	else if ( strstr( modelName, "w_pist_p228.mdl" ) )					{name = "y";}
	else if ( strstr( modelName, "w_mach_m249para.mdl" ) )				{name = "z";}
	else if ( strstr( modelName, "w_rif_sg552.mdl" ) )					{name = "A";}
	else if ( strstr( modelName, "w_c4.mdl" ) )							{name = "C";}
	else if ( strstr( modelName, "w_c4_planted.mdl" ) )					{name = "I";}
	else if ( strstr( modelName, "w_shot_xm1014.mdl" ) )				{name = "B";}
	//else if ( strstr( modelName, "w_defuser.mdl" ) )					{other = "G";}
	
	return name;
}
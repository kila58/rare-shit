#include "SDK.h"
#include "Player ESP.h" // Base Header
#include "Player Manager.h" // gPlayers
#include "CDrawManager.h"
#include "Color Manager.h" // gDrawManager
#include "Control Variables.h"
#include "Menu.h"
#include "Extra Functions.h"


//===================================================================================

CSetupPlayer cSetup;

// In case this ever changes
#define M_PI			3.14159265358979323846



float DotProductT(const float* a, const float* b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}
void VectorTransformA(const float *in1, const matrix3x4_t& in2, float *out)
{

	out[0] = DotProductT(in1, in2[0]) + in2[0][3];
	out[1] = DotProductT(in1, in2[1]) + in2[1][3];
	out[2] = DotProductT(in1, in2[2]) + in2[2][3];
}

void VectorTransformA2(const float *in1, const matrix3x4& in2, float *out)
{

	out[0] = DotProductT(in1, in2[0]) + in2[0][3];
	out[1] = DotProductT(in1, in2[1]) + in2[1][3];
	out[2] = DotProductT(in1, in2[2]) + in2[2][3];
}

inline void VectorTransformZ2(const Vector& in1, const matrix3x4 &in2, Vector &out)
{
	VectorTransformA2(&in1.x, in2, &out.x);
}


inline void VectorTransformZ(const Vector& in1, const matrix3x4_t &in2, Vector &out)
{
	VectorTransformA(&in1.x, in2, &out.x);
}

void Draw3DBox(Vector* points,Color dat)
{
	Vector startPos, endPos;

	for (int i = 0; i < 3; i++)
	{
		if (ALX.pDrawManager->WorldToScreen(points[i], startPos))
		if (ALX.pDrawManager->WorldToScreen(points[i + 1], endPos))
			ALX.pDrawManager->DrawLine1(startPos.x, startPos.y, endPos.x, endPos.y, dat);
	}
	if (ALX.pDrawManager->WorldToScreen(points[0], startPos))
	if (ALX.pDrawManager->WorldToScreen(points[3], endPos))
		ALX.pDrawManager->DrawLine1(startPos.x, startPos.y, endPos.x, endPos.y, dat);

	for (int i = 4; i < 7; i++)
	{
		if (ALX.pDrawManager->WorldToScreen(points[i], startPos))
		if (ALX.pDrawManager->WorldToScreen(points[i + 1], endPos))
			ALX.pDrawManager->DrawLine1(startPos.x, startPos.y, endPos.x, endPos.y, dat);
	}
	if (ALX.pDrawManager->WorldToScreen(points[4], startPos))
	if (ALX.pDrawManager->WorldToScreen(points[7], endPos))
		ALX.pDrawManager->DrawLine1(startPos.x, startPos.y, endPos.x, endPos.y, dat);

	if (ALX.pDrawManager->WorldToScreen(points[0], startPos))
	if (ALX.pDrawManager->WorldToScreen(points[6], endPos))
		ALX.pDrawManager->DrawLine1(startPos.x, startPos.y, endPos.x, endPos.y, dat);

	if (ALX.pDrawManager->WorldToScreen(points[1], startPos))
	if (ALX.pDrawManager->WorldToScreen(points[5], endPos))
		ALX.pDrawManager->DrawLine1(startPos.x, startPos.y, endPos.x, endPos.y, dat);

	if (ALX.pDrawManager->WorldToScreen(points[2], startPos))
	if (ALX.pDrawManager->WorldToScreen(points[4], endPos))
		ALX.pDrawManager->DrawLine1(startPos.x, startPos.y, endPos.x, endPos.y, dat);

	if (ALX.pDrawManager->WorldToScreen(points[3], startPos))
	if (ALX.pDrawManager->WorldToScreen(points[7], endPos))
		ALX.pDrawManager->DrawLine1(startPos.x, startPos.y, endPos.x, endPos.y, dat);
}

void HitboxESP(CBaseEntity* pPlayer, matrix3x4* matrix, int bone, Vector max, Vector min,Color dat)
{
	Vector points[] = { Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z) };
	Vector pointsTransformed[8];



	for (int i = 0; i < 8; i++)
	{
		points[i].x *= 0.9;
		points[i].y *= 0.9;
		points[i].z *= 0.9;
		VectorTransformZ2(points[i], matrix[bone], pointsTransformed[i]);

	}
	Draw3DBox(pointsTransformed,dat);
}

void hitboxes(CBaseEntity* pPlayer,Color dat)
{
	matrix3x4 MatrixArray[128];

	if (!pPlayer->SetupBones(MatrixArray, 128, 0x00000100, ALX.pEngine->Time()))
		return;

	Hitbox_t    Hitbox[21];

	Vector minz, maxz;
	Hitbox[0].Setup(BONE_PELVIS, Vector(-6.42f, -5.7459f, -6.8587f), Vector(4.5796f, 4.5796f, 6.8373f));
	Hitbox[1].Setup(BONE_L_THIGH, Vector(1.819f, -3.959f, -2.14f), Vector(22.149002f, 3.424f, 4.5796f));
	Hitbox[2].Setup(BONE_L_CALF, Vector(2.0758f, -3.21f, -2.1507f), Vector(19.26f, 2.675f, 3.0495f));
	Hitbox[3].Setup(BONE_L_FOOT, Vector(1.8725f, -2.675f, -2.4075f), Vector(5.6175f, 9.694201f, 2.4075f));
	Hitbox[4].Setup(BONE_R_THIGH, Vector(1.819f, -3.7557f, -4.5796f), Vector(22.149002f, 3.424f, 2.14f));
	Hitbox[5].Setup(BONE_R_CALF, Vector(2.0758f, -3.21f, -2.8462f), Vector(19.26f, 2.675f, 2.247f));
	Hitbox[6].Setup(BONE_R_FOOT, Vector(1.8725f, -2.675f, -2.4075f), Vector(5.6175f, 9.694201, 2.4075f));
	Hitbox[7].Setup(BONE_SPINE2, Vector(-4.28f, -4.5796f, -6.3879f), Vector(3.21f, 5.885f, 6.2809f));
	Hitbox[8].Setup(BONE_SPINE3, Vector(-4.28f, -5.029f, -6.0883f), Vector(3.21f, 5.885f, 5.9813f));
	Hitbox[9].Setup(BONE_SPINE4, Vector(-4.28f, -5.35f, -5.885f), Vector(2.9211f, 5.1467f, 5.885f));
	Hitbox[10].Setup(BONE_NECK, Vector(0.3317f, -3.0174f, -2.4503f), Vector(3.4026f, 2.4182f, 2.354f));
	Hitbox[11].Setup(BONE_HEAD, Vector(-2.7713f, -2.8783f, -3.103f), Vector(6.955f, 3.5203f, 3.0067f));
	Hitbox[12].Setup(BONE_L_UPPER_ARM, Vector(-2.675f, -3.21f, -2.14f), Vector(12.84f, 3.21f, 2.14f));
	Hitbox[13].Setup(BONE_L_FOREARM, Vector(-0.f, -2.14f, -2.14f), Vector(9.63f, 2.14f, 2.14f));
	Hitbox[14].Setup(BONE_L_HAND, Vector(-1.7227f, -1.2198f, -1.3803f), Vector(4.4726f, 1.2198f, 1.3803f));
	Hitbox[15].Setup(BONE_R_UPPER_ARM, Vector(-2.675f, -3.21f, -2.14f), Vector(12.84f, 3.21f, 2.14f));
	Hitbox[16].Setup(BONE_R_FOREARM, Vector(-0.f, -2.14f, -2.14f), Vector(9.63f, 2.14f, 2.14f));
	Hitbox[17].Setup(BONE_R_HAND, Vector(-1.7227f, -1.2198f, -1.3803f), Vector(4.4726f, 1.2198f, 1.3803f));
	Hitbox[18].Setup(BONE_L_CLAVICLE, Vector(-0.f, -3.21f, -5.35f), Vector(7.49f, 4.28f, 3.21f));
	Hitbox[19].Setup(BONE_R_CLAVICLE, Vector(-0.f, -3.21f, -3.21f), Vector(7.49f, 4.28f, 5.35f));
	Hitbox[20].Setup(BONE_HEAD, Vector(-2.5038f, 2.009f, -1.1021f), Vector(6.3023f, 5.2965f, 0.9951f));
	Hitbox[21].Setup(BONE_SPINE4, Vector(-0.2996f, -6.0027f, -4.996901f), Vector(5.4998f, 2.5038f, 5.1039f));


	for (int i = 0; i < 21; i++)
	{

		int bone = Hitbox[i].iBone;
		Vector vMaxUntransformed = Hitbox[i].vMax;
		Vector vMinUntransformed = Hitbox[i].vMin;

		HitboxESP(pPlayer, MatrixArray, bone, vMaxUntransformed, vMinUntransformed,dat);
	}
}


void hitboxe_head(CBaseEntity* pPlayer, Color dat)
{
	matrix3x4 MatrixArray[128];

	if (!pPlayer->SetupBones(MatrixArray, 128, 0x00000100, ALX.pEngine->Time()))
		return;

	Hitbox_t    Hitbox[1];

	Vector minz, maxz;
	
	Hitbox[10].Setup(BONE_HEAD, Vector(-2.7713f, -2.8783f, -3.103f), Vector(6.955f, 3.5203f, 3.0067f));
	
	
		int bone = 10;
		Vector vMaxUntransformed = Hitbox[10].vMax;
		Vector vMinUntransformed = Hitbox[10].vMin;

		HitboxESP(pPlayer, MatrixArray, bone, vMaxUntransformed, vMinUntransformed, dat);
	
}


FLOAT Spreadz::FindDistanceZ(CBaseEntity *pPlayer, CBaseEntity *pLocal)
{
	return sqrtf(
		(pLocal->GetOrigin().x - pPlayer->GetOrigin().x) * (pLocal->GetOrigin().x - pPlayer->GetOrigin().x) +
		(pLocal->GetOrigin().y - pPlayer->GetOrigin().y) * (pLocal->GetOrigin().y - pPlayer->GetOrigin().y) +
		(pLocal->GetOrigin().z - pPlayer->GetOrigin().z) * (pLocal->GetOrigin().z - pPlayer->GetOrigin().z));
}

bool Spreadz::KnifeBot(CBaseEntity *pBaseEntity, CBaseEntity *pLocalEntity)
{
	float flDist = ALX.PSpreadz->FindDistanceZ(pLocalEntity, pBaseEntity);
	if (flDist < 6.7)
		return true;

	return false;
}

FLOAT FindDistance3(CBaseEntity *pPlayer, CBaseEntity *pLocal)
{
	return sqrtf(
		(pLocal->GetOrigin().x - pPlayer->GetOrigin().x) * (pLocal->GetOrigin().x - pPlayer->GetOrigin().x) +
		(pLocal->GetOrigin().y - pPlayer->GetOrigin().y) * (pLocal->GetOrigin().y - pPlayer->GetOrigin().y) +
		(pLocal->GetOrigin().z - pPlayer->GetOrigin().z) * (pLocal->GetOrigin().z - pPlayer->GetOrigin().z));
}

#include "DLLMain.h"

void DrawPlayerBox(CBaseEntity* pEntity, Color dat,int x, int y,player_info_t pInfo)
{
	if (!pEntity)
		return;


	DWORD m_rgflCoordinateFrame = (DWORD)ALX.pPlayerVariables->m_CollisionGroup - 0x30;//int 
	const matrix3x4_t& trnsf = *(matrix3x4_t*)((DWORD)pEntity + (DWORD)m_rgflCoordinateFrame);


	Vector min = *reinterpret_cast< Vector* >((DWORD)pEntity + (DWORD)ALX.pPlayerVariables->m_Collision + 0x8);//m_angEyeAngles[0] //0x239C)
	Vector max = *reinterpret_cast< Vector* >((DWORD)pEntity + (DWORD)ALX.pPlayerVariables->m_Collision + 0x14);



	Vector points[] = { Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z) };



	Vector pointsTransformed[8];
	for (int i = 0; i < 8; i++)
	{
		VectorTransformZ(points[i], trnsf, pointsTransformed[i]);
	}


	Vector pos = pEntity->GetOrigin();
	Vector flb;
	Vector brt;
	Vector blb;
	Vector frt;
	Vector frb;
	Vector brb;
	Vector blt;
	Vector flt;


	if (!ALX.pDrawManager->WorldToScreen(pointsTransformed[3], flb) || !ALX.pDrawManager->WorldToScreen(pointsTransformed[5], brt)
		|| !ALX.pDrawManager->WorldToScreen(pointsTransformed[0], blb) || !ALX.pDrawManager->WorldToScreen(pointsTransformed[4], frt)
		|| !ALX.pDrawManager->WorldToScreen(pointsTransformed[2], frb) || !ALX.pDrawManager->WorldToScreen(pointsTransformed[1], brb)
		|| !ALX.pDrawManager->WorldToScreen(pointsTransformed[6], blt) || !ALX.pDrawManager->WorldToScreen(pointsTransformed[7], flt))
		return;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;        // left
	float top = flb.y;        // top
	float right = flb.x;    // right
	float bottom = flb.y;    // bottom

	for (int i = 1; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (top < arr[i].y)
			top = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (bottom > arr[i].y)
			bottom = arr[i].y;
	}

	char playerName[32];
	sprintf(playerName, "%s", pInfo.name);


	if (ALX.pCvar->Name && ALX.pCvar->bbox)
	{
		ALX.pDrawManager->DrawStringM(AFont, true, flb.x, flb.y, colWhite, pInfo.name);
	}

	if (ALX.pCvar->bbox)
	{

		ALX.pDrawManager->DrawLine2D(Vector(left, bottom, 0), Vector(left, top, 0), dat);
		ALX.pDrawManager->DrawLine2D(Vector(left, top, 0), Vector(right, top, 0), dat);
		ALX.pDrawManager->DrawLine2D(Vector(right, top, 0), Vector(right, bottom, 0), dat);
		ALX.pDrawManager->DrawLine2D(Vector(right, bottom, 0), Vector(left, bottom, 0), dat);
	}

	if (ALX.pCvar->AABB)
	{

		ALX.pDrawManager->DrawLine2D(flb, flt, dat);
		ALX.pDrawManager->DrawLine2D(flt, frt, dat);
		ALX.pDrawManager->DrawLine2D(frt, frb, dat);
		ALX.pDrawManager->DrawLine2D(frb, flb, dat);
		ALX.pDrawManager->DrawLine2D(blb, blt, dat);
		ALX.pDrawManager->DrawLine2D(blt, brt, dat);
		ALX.pDrawManager->DrawLine2D(brt, brb, dat);
		ALX.pDrawManager->DrawLine2D(brb, blb, dat);
		ALX.pDrawManager->DrawLine2D(flb, blb, dat);
		ALX.pDrawManager->DrawLine2D(frb, brb, dat);
		ALX.pDrawManager->DrawLine2D(flt, blt, dat);
		ALX.pDrawManager->DrawLine2D(frt, brt, dat);
	}

}


int GetRank(int Index)
{
	int dwCompRank = 0x1a38;
	DWORD dwTemp = *(DWORD*)(ALX.pBaseAPI->GetModuleHandleSafe("client.dll") + 0x2E7D6DC);
	return *(int*)((DWORD)dwTemp + dwCompRank + (int)Index * 4);
}

int GetWins(int Index)
{
	int dwCompWins = 0x1b3c;
	DWORD dwTemp = *(DWORD*)(ALX.pBaseAPI->GetModuleHandleSafe("client.dll") + 0x2E7D6DC);
	return *(int*)((DWORD)dwTemp + dwCompWins + (int)Index * 4);
}

static char const *Ranks[] =
{
	"-",
	"Silver I",
	"Silver II",
	"Silver III",
	"Silver IV",
	"Silver Elite",
	"Silver Elite Master",

	"Gold Nova I",
	"Gold Nova II",
	"Gold Nova III",
	"Gold Nova Master",
	"Master Guardian I",
	"Master Guardian II",

	"Master Guardian Elite",
	"Distinguished Master Guardian",
	"Legendary Eagle",
	"Legendary Eagle Master",
	"Supreme Master First Class",
	"The Global Elite"
};

int GetKills(int Index)
{
	DWORD dwTemp = *(DWORD*)((DWORD)ALX.pBaseAPI->GetModuleHandleSafe("client.dll") + 0x2E7F6EC);
	return *(int*)((DWORD)dwTemp + ALX.pPlayerVariables->m_iKills + (int)Index * 4);
}


//===================================================================================
void CPlayerESP::DrawPlayerESP( int iIndex )
{
	player_info_t pInfo;
	//================================================================
	CSetupPlayer __pLocalBaseEntity = gPlayers[me];

	CBaseEntity* pLocalBaseEntity = __pLocalBaseEntity.BaseEnt();

	if( iIndex == pLocalBaseEntity->GetIndex() )
		return;
	//================================================================
	CSetupPlayer __pBaseEntity = gPlayers[iIndex];

	CBaseEntity* pBaseEntity = __pBaseEntity.BaseEnt();

	if( pBaseEntity == NULL )
		return;
	//================================================================

	
	if (!ALX.pCvar->DrawTeam && __pLocalBaseEntity.GetTeam() == __pBaseEntity.GetTeam())
		return;


 
	Vector vHead, vScreenHead, vScreenLeg;

	bool bIsVisible = ALX.pPlayerESP->IsVisible(vHead, vScreenHead,pBaseEntity);
	
	if( !ALX.pDrawManager->GetBonePosition( pBaseEntity, vHead, 10 ) )
		return;

	if (ALX.pCvar->noflash)
	{
		*MakePtr(float*,pLocalBaseEntity,ALX.pPlayerVariables->m_flFlashDuration) = 0.0f;
		*MakePtr(float*,pLocalBaseEntity,ALX.pPlayerVariables->m_flFlashMaxAlpha) = 0.0f;
	}


	if (__pBaseEntity.GetLifeState() == LIFE_ALIVE && !pBaseEntity->IsDormant() && ALX.pEngine->GetPlayerInfo(iIndex, &pInfo) && ALX.pDrawManager->WorldToScreen(vHead, vScreenHead) && ALX.pDrawManager->WorldToScreen(pBaseEntity->GetAbsOrigin(), vScreenLeg))
	{

		Vector vScreen;

		char playerDistance[32];
		int  Distance1 = FindDistance3(pBaseEntity, pLocalBaseEntity);

		char playerHealth[32];

		int playerHP = __pBaseEntity.GetHealth();

		sprintf(playerHealth, "%d", playerHP);
		

		sprintf(playerDistance, "[%d]", Distance1 / 36);

	
		float Height = abs(vScreenLeg.y - vScreenHead.y);
		float Width = Height / 1.7f;

		if (ALX.pDrawManager->WorldToScreen(pBaseEntity->GetAbsOrigin(), vScreen) == false)
			return;

		int *iTeamIndex = (int*)((DWORD)pBaseEntity + (DWORD)0xF0);
		float Distance = flGetDistance(pBaseEntity->GetAbsOrigin(), pLocalBaseEntity->GetAbsOrigin()) / 36;
		int iRadius = 450.0 / Distance;

		float pDistance = FindDistance3(pBaseEntity, pLocalBaseEntity);

	
		if (ALX.pCvar->Radar)
		{
			ALX.pPlayerESP->DrawRadarPoint(pBaseEntity->GetAbsOrigin(), pLocalBaseEntity->GetAbsOrigin(), pLocalBaseEntity->GetAbsAngles());
		}



		if (ALX.pCvar->hbarB)
		{
			ALX.pDrawManager->DrawPlayerHealthBox(pBaseEntity, Color(0, 0, 0, 255), __pBaseEntity.GetHealth(), 100);
		}
			if (*iTeamIndex == 2)
			{
				
				ALX.pDrawManager->DrawPlayerBox(pBaseEntity, bIsVisible ? colYellow : colCrimson,pInfo,iIndex);
			}
			else if (*iTeamIndex == 3)
			{
				ALX.pDrawManager->DrawPlayerBox(pBaseEntity, bIsVisible ? colGreen : colBlue,pInfo,iIndex);
				
			}
	

			

		if (ALX.pCvar->glow)
		{
			if (*iTeamIndex == 2)
			{
				ALX.pDrawManager->UpdateEntityGlow(pBaseEntity, bIsVisible ? 1.0f,1.0f,0.0f,1.0f : 0.5f,0.0f,0.0f,1.0f);
			}
			else if (*iTeamIndex == 3)
			{	
				ALX.pDrawManager->UpdateEntityGlow(pBaseEntity, bIsVisible ? 0.0f,0.5f,0.0f,1.0f : 0.0f,0.0f,0.5f,1.0f);	
			}
		}

		if (ALX.pCvar->Skeleton)
		{
			ALX.pPlayerESP->DrawBones(iIndex);
			
		}

		if (*iTeamIndex == 2)
		{
			DrawPlayerBox(pBaseEntity, bIsVisible ? colYellow : colCrimson,vScreenHead.x,vScreenHead.y,pInfo);
		}
		else if (*iTeamIndex == 3)
		{
			DrawPlayerBox(pBaseEntity, bIsVisible ? colGreen : colBlue, vScreenHead.x, vScreenHead.y,pInfo);
		}


		if (ALX.pCvar->esp)
		{
			if (*iTeamIndex == 2)
			{

				ALX.pDrawManager->OutlineRect1(vScreenHead.x - Width / 2, vScreenHead.y, Width, Height, bIsVisible ? colCrimson : colYellow);
			}
			else if (*iTeamIndex == 3)
			{

				ALX.pDrawManager->OutlineRect1(vScreenHead.x - Width / 2, vScreenHead.y, Width, Height, bIsVisible ? colBlue : colLightGreen);
			}

			ALX.pDrawManager->OutlineRect1(vScreenHead.x - Width / 2 - 1, vScreenHead.y - 1, Width + 2, Height + 2, colBlack);
		}

		

		if (ALX.pCvar->spotted)
		{
			
		}
	
		Vector vecForward;
		Vector vecStart;
		Vector vecEnd;


		if (ALX.pCvar->barrels)
		{

			Vector vecPlayerAngle = pBaseEntity->GetEyeAngles();  //( Vector )( pEntity + 0x239C );


			ALX.PSpreadz->AngleVectors(vecPlayerAngle, &vecForward);

			vecForward = (vecForward * 1024.0f) + vHead;//~120 -8291 len of line


			if (ALX.pDrawManager->WorldToScreen(vHead, vecStart) && ALX.pDrawManager->WorldToScreen(vecForward, vecEnd))
			{
				ALX.pDrawManager->DrawLine1(vecStart.x, vecStart.y, vecEnd.x, vecEnd.y, colBlue);
			}
		
		}

		if (ALX.pCvar->Health)
		{
			ALX.pDrawManager->DrawStringM(espfont,false, vScreenHead.x, vScreenHead.y + Height / 2, colGreen, playerHealth);
		}

		
	

		
		
		float fHealth = __pBaseEntity.GetHealth();

		/*if (ALX.pCvar->hbarL)
		{
			if (*iTeamIndex == 2)
			{
				ALX.pDrawManager->DrawHealthBox(vScreenHead.x -	Width / 2, vScreenHead.y, 255, 10, 20, 255, fHealth, 100,Width);
				
			}
			else if (*iTeamIndex == 3)
			{
				ALX.pDrawManager->DrawHealthBox(vScreenHead.x - Width / 2, vScreenHead.y, 0,110, 220, 255, fHealth, 100,Width);
			
			}

			
		
		}
		*/
		if (ALX.pCvar->Armor)
		{

		}
	}
}

void CPlayerESP::DrawRadarBack()
{
	int centerx = ALX.pOptions->Radar_X;
	int centery = ALX.pOptions->Radar_Y;
	int size = ALX.pOptions->Radar_Size;
	size -= 10;


	ALX.pDrawManager->FillRGBA(centerx - size, centery - size, 2 * size, 2 * size, Color(80,80,80,80));
	ALX.pDrawManager->FillRGBA(centerx, centery - size, 1, 2 * size, Color(0, 0, 0, 255));
	ALX.pDrawManager->FillRGBA(centerx - size, centery, 2 * size, 1, Color(0, 0, 0, 255));
	ALX.pDrawManager->OutlineRect1(centerx - size, centery - size, 2 * size, 2 * size, Color(0, 0, 0, 255));
	ALX.pDrawManager->FillRGBA(centerx - size, centery - size, 2 * size, 30, colDarkGrey);
	ALX.pDrawManager->DrawString1(false, centerx - size + 10, centery - size + 10, colGreen, "Radar");

}
void CPlayerESP::DrawRadarPoint(Vector vecOriginx, Vector vecOriginy, Vector vAngle)
{
	float dx = vecOriginx.x - vecOriginy.x;
	float dy = vecOriginx.y - vecOriginy.y;
	float flAngle = vAngle.y;
	float yaw = (flAngle)* (M_PI / 180.0);
	float mainViewAngles_CosYaw = cos(yaw);
	float mainViewAngles_SinYaw = sin(yaw);
	float x = dy*(-mainViewAngles_CosYaw) + dx*mainViewAngles_SinYaw;
	float y = dx*(-mainViewAngles_CosYaw) - dy*mainViewAngles_SinYaw;
	float range = ALX.pOptions->Radar_Size * ALX.pOptions->Radar_Range;
	if (fabs(x)>range || fabs(y)>range)
	{
		if (y>x)
		{
			if (y>-x) {
				x = range*x / y;
				y = range;
			}
			else  {
				y = -range*y / x;
				x = -range;
			}
		}
		else {
			if (y>-x) {
				y = range*y / x;
				x = range;
			}
			else  {
				x = -range*x / y;
				y = -range;
			}
		}
	}
	int ScreenX = ALX.pOptions->Radar_X + int(x / range*float(ALX.pOptions->Radar_Size));
	int ScreenY = ALX.pOptions->Radar_Y + int(y / range*float(ALX.pOptions->Radar_Size));
	ALX.pDrawManager->OutlineRect1(ScreenX - 1, ScreenY - 1, 5, 5, colGreen);
}

void CPlayerESP::DrawBones(int iIndex)
{
	CSetupPlayer __pLocalBaseEntity = gPlayers[me];

	CBaseEntity* pLocalBaseEntity = __pLocalBaseEntity.BaseEnt();

	if (iIndex == pLocalBaseEntity->GetIndex())
		return;
	//================================================================
	CSetupPlayer __pBaseEntity = gPlayers[iIndex];

	CBaseEntity* pBaseEntity = __pBaseEntity.BaseEnt();

	if (!pBaseEntity)
		return;



	Vector vHead, vScreenHead, vScreenLeg, vNeck, vNeckScreen, vPelvis, vPelvisScreen, vLCalvicle, vLCalvicleScreen,
		vRCalvicle, vRCalvicleScreen, vLCalf, vLCalfScreen, vRCalf, vRCalfScreen, vLCalfTwist, vLCalfTwistScreen, vRCalfTwist,
		vRCalfTwistScreen, vLFoot, vLFootScreen, vRFoot, vRFootScreen, vLUpperArm, vLUpperArmScreen, vRUpperArm, vRUpperArmScreen,
		vLUnderArm, vLUnderArmScreen, vRUnderArm, vRUnderArmScreen;

	if (!ALX.pDrawManager->GetBonePosition(pBaseEntity, vHead, 10))
		return;


	if (!ALX.pDrawManager->GetBonePosition(pBaseEntity, vNeck, 5))
		return;
	if (!ALX.pDrawManager->GetBonePosition(pBaseEntity, vPelvis, 0))
		return;
	if (!ALX.pDrawManager->GetBonePosition(pBaseEntity, vLCalvicle, 7))
		return;
	if (!ALX.pDrawManager->GetBonePosition(pBaseEntity, vRCalvicle, 13))
		return;
	if (!ALX.pDrawManager->GetBonePosition(pBaseEntity, vLCalf, 26))
		return;
	if (!ALX.pDrawManager->GetBonePosition(pBaseEntity, vRCalf, 23))
		return;
	if (!ALX.pDrawManager->GetBonePosition(pBaseEntity, vLCalfTwist, 27))
		return;
	if (!ALX.pDrawManager->GetBonePosition(pBaseEntity, vRCalfTwist, 24))
		return;
	if (!ALX.pDrawManager->GetBonePosition(pBaseEntity, vLFoot, 28))
		return;
	if (!ALX.pDrawManager->GetBonePosition(pBaseEntity, vRFoot, 25))
		return;
	if (!ALX.pDrawManager->GetBonePosition(pBaseEntity, vLUpperArm, 8))
		return;
	if (!ALX.pDrawManager->GetBonePosition(pBaseEntity, vRUpperArm, 14))
		return;
	if (!ALX.pDrawManager->GetBonePosition(pBaseEntity, vLUnderArm, 9))
		return;
	if (!ALX.pDrawManager->GetBonePosition(pBaseEntity, vRUnderArm, 15))
		return;


	if (__pBaseEntity.GetLifeState() == LIFE_ALIVE &&
		ALX.pDrawManager->WorldToScreen(vHead, vScreenHead) &&
		ALX.pDrawManager->WorldToScreen(vNeck, vNeckScreen) &&
		ALX.pDrawManager->WorldToScreen(vLCalvicle, vLCalvicleScreen) &&
		ALX.pDrawManager->WorldToScreen(vRCalvicle, vRCalvicleScreen) &&
		ALX.pDrawManager->WorldToScreen(vLCalf, vLCalfScreen) &&
		ALX.pDrawManager->WorldToScreen(vRCalf, vRCalfScreen) &&
		ALX.pDrawManager->WorldToScreen(vLCalfTwist, vLCalfTwistScreen) &&
		ALX.pDrawManager->WorldToScreen(vRCalfTwist, vRCalfTwistScreen) &&
		ALX.pDrawManager->WorldToScreen(vLFoot, vLFootScreen) &&
		ALX.pDrawManager->WorldToScreen(vRFoot, vRFootScreen) &&
		ALX.pDrawManager->WorldToScreen(vLUpperArm, vLUpperArmScreen) &&
		ALX.pDrawManager->WorldToScreen(vRUpperArm, vRUpperArmScreen) &&
		ALX.pDrawManager->WorldToScreen(vLUnderArm, vLUnderArmScreen) &&
		ALX.pDrawManager->WorldToScreen(vRUnderArm, vRUnderArmScreen) &&
		ALX.pDrawManager->WorldToScreen(vPelvis, vPelvisScreen))

	{

		

		ALX.pDrawManager->DrawLine1(vScreenHead.x, vScreenHead.y, vNeckScreen.x, vNeckScreen.y, colWhite);
		ALX.pDrawManager->DrawLine1(vNeckScreen.x, vNeckScreen.y, vPelvisScreen.x, vPelvisScreen.y, colWhite);
		ALX.pDrawManager->DrawLine1(vNeckScreen.x, vNeckScreen.y, vLCalvicleScreen.x, vLCalvicleScreen.y, colWhite);
		ALX.pDrawManager->DrawLine1(vNeckScreen.x, vNeckScreen.y, vRCalvicleScreen.x, vRCalvicleScreen.y, colWhite);
		ALX.pDrawManager->DrawLine1(vPelvisScreen.x, vPelvisScreen.y, vLCalfScreen.x, vLCalfScreen.y, colWhite);
		ALX.pDrawManager->DrawLine1(vPelvisScreen.x, vPelvisScreen.y, vRCalfScreen.x, vRCalfScreen.y, colWhite);
		ALX.pDrawManager->DrawLine1(vLCalfScreen.x, vLCalfScreen.y, vLCalfTwistScreen.x, vLCalfTwistScreen.y, colWhite);
		ALX.pDrawManager->DrawLine1(vRCalfScreen.x, vRCalfScreen.y, vRCalfTwistScreen.x, vRCalfTwistScreen.y, colWhite);
		ALX.pDrawManager->DrawLine1(vLCalfTwistScreen.x, vLCalfTwistScreen.y, vLFootScreen.x, vLFootScreen.y, colWhite);
		ALX.pDrawManager->DrawLine1(vRCalfTwistScreen.x, vRCalfTwistScreen.y, vRFootScreen.x, vRFootScreen.y, colWhite);
		ALX.pDrawManager->DrawLine1(vLCalvicleScreen.x, vLCalvicleScreen.y, vLUpperArmScreen.x, vLUpperArmScreen.y, colWhite);
		ALX.pDrawManager->DrawLine1(vRCalvicleScreen.x, vRCalvicleScreen.y, vRUpperArmScreen.x, vRUpperArmScreen.y, colWhite);
		ALX.pDrawManager->DrawLine1(vLUpperArmScreen.x, vLUpperArmScreen.y, vLUnderArmScreen.x, vLUnderArmScreen.y, colWhite);
		ALX.pDrawManager->DrawLine1(vRUpperArmScreen.x, vRUpperArmScreen.y, vRUnderArmScreen.x, vRUnderArmScreen.y, colWhite);



	}
}
//===================================================================================
void CPlayerESP::DrawWorldESP(int iIndex)
{

	CBaseEntity* pLocalBaseEntity = gPlayers[me].BaseEnt();

	CBaseEntity* pBaseEntity = ALX.pEntList->GetClientEntity(iIndex);

	if (pBaseEntity == NULL)
		return;

	if (pBaseEntity->IsDormant() == false)
	{
		Vector vScreen;
		int iTeamNum;

		if (ALX.pDrawManager->WorldToScreen(pBaseEntity->GetAbsOrigin(), vScreen) == false)
			return;

		DWORD dwTeamColor = ALX.pColorManager->dwGetColor(*MakePtr(int*, pBaseEntity, ALX.pPlayerVariables->m_iTeamNum));
		if (!(ALX.pEntList->GetClientEntityFromHandle(*MakePtr(int*, pBaseEntity, ALX.pPlayerVariables->m_hOwnerEntity))))
		{
			if (ALX.pCvar->Entity)
			{
				if (strstr(pBaseEntity->GetClientClass()->GetName(), "CWeapon"))
				{
					ALX.pDrawManager->DrawString1(false, vScreen.x, vScreen.y, colYellow, "%s", string(pBaseEntity->GetClientClass()->GetName()).substr(7).c_str());
			
				}
				if (streql(pBaseEntity->GetClientClass()->GetName(), "CAK47"))
				{
					ALX.pDrawManager->DrawString1(false, vScreen.x, vScreen.y, colYellow, "AK47");

				}

				if (streql(pBaseEntity->GetClientClass()->GetName(), "CDEagle"))
				{
					ALX.pDrawManager->DrawString1(false, vScreen.x, vScreen.y, colYellow, "Deagle");
				}

				if (streql(pBaseEntity->GetClientClass()->GetName(), "CKnife"))
				{
					ALX.pDrawManager->DrawString1(false, vScreen.x, vScreen.y, colYellow, "Knife");
				}

			}

			if (ALX.pCvar->c4esp)
			{
				if (streql(pBaseEntity->GetClientClass()->GetName(), "CC4"))
				{
					ALX.pDrawManager->DrawString1(false, vScreen.x, vScreen.y, colCyan, "C4");
				}
			}
		}

		if (ALX.pCvar->Chicken)
		{
			if (streql(pBaseEntity->GetClientClass()->GetName(), "CChicken"))
			{
				ALX.pDrawManager->DrawString1(false, vScreen.x - 10, vScreen.y, Color(255, 255, 255, 255), "Chicken");
				ALX.pDrawManager->DrawChickenBox(pBaseEntity, Color(255,255,255,255));
				ALX.pDrawManager->DrawChickenBox1(pBaseEntity, Color(000, 000, 000, 255), iIndex);
			}
		}

		//===================//
	}
}

Vector CPlayerESP::GetEyePosition(CBaseEntity* pEntity)
{
	Vector vecViewOffset = *reinterpret_cast< Vector* >(reinterpret_cast< int >(pEntity)+0x104);

	return pEntity->GetAbsOrigin() + vecViewOffset;
}


bool CPlayerESP::IsVisible(Vector& vecStart, Vector& vecEnd, CBaseEntity* pEntity)
{
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;
	filter.pSkip = ALX.pEntList->GetClientEntity(ALX.pEngine->GetLocalPlayer());

	ray.Init(GetEyePosition(ALX.pEntList->GetClientEntity(ALX.pEngine->GetLocalPlayer())), GetEyePosition(pEntity));
	ALX.pEngineTrace->TraceRay(ray, 0x46004003, &filter, &tr);

	return (tr.m_pEnt == pEntity || tr.fraction > 0.99f);
}


void CPlayerESP::NormalizeAngle(Vector &angles)
{
	int i;

	// Normalize angles to -180 to 180 range
	for (i = 0; i < 3; i++)
	{
		if (angles[i] > 180.0)
		{
			angles[i] -= 360.0;
		}
		else if (angles[i] < -180.0)
		{
			angles[i] += 360.0;
		}
	}



}

void CPlayerESP::ClampAngles(Vector &angles)//??? ? ?? ????? ??? ?????????? ????????, ?? ?????? ???????? ??? 89
{

	if (angles.x > 89)
	{
		angles.x = 89;
	}
	if (angles.x < -89)
	{
		angles.x = -89;
	}
	if (angles.y > 180)
	{
		angles.y = 180;
	}
	if (angles.y < -180)
	{
		angles.y = -180;
	}

	angles.z = 0;
}

#define WEAPON_SPREAD_OFFSET (1836/4)

C_BaseCombatWeapon* Spreadz::GetBaseCombatActiveWeapon(CBaseEntity* pBaseEntity)
{
	C_BaseCombatWeapon* pActiveWeapon;
	__asm
	{
		MOV ECX, pBaseEntity
			MOV EAX, [ECX]
			CALL DWORD PTR DS : [EAX + 0x3F0]//3D4 138 48  //localplayerweapon
			MOV pActiveWeapon, EAX
	}
	return pActiveWeapon;
}

void Spreadz::AngleToVectors(const Vector &angles, Vector *forward, Vector *right, Vector *up)
{
	float angle;
	static float sr, sp, sy, cr, cp, cy, cpi = (M_PI * 2 / 360);

	angle = angles.y * cpi;
	sy = sin(angle);
	cy = cos(angle);
	angle = angles.x * cpi;
	sp = sin(angle);
	cp = cos(angle);
	angle = angles.z * cpi;
	sr = sin(angle);
	cr = cos(angle);

	if (forward)
	{
		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	}

	if (right)
	{
		right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
		right->y = (-1 * sr*sp*sy + -1 * cr*cy);
		right->z = -1 * sr*cp;
	}

	if (up)
	{
		up->x = (cr*sp*cy + -sr*-sy);
		up->y = (cr*sp*sy + -sr*cy);
		up->z = cr*cp;
	}
}

void Spreadz::VectorAngles(Vector *forward, Vector *angles)
{
	float   tmp, yaw, pitch;

	if (forward->y == 0 && forward->x == 0)
	{
		yaw = 0;
		if (forward->z > 0)
			pitch = 90.0;
		else
			pitch = 270.0;
	}
	else
	{
		yaw = (float)(atan2(forward->y, forward->x) * 180.0 / M_PI);

		if (yaw < 0) yaw += 360.0;

		tmp = (float)sqrt(forward->x*forward->x + forward->y*forward->y);

		pitch = (float)(atan2(forward->z, tmp) * 180 / M_PI);
	}

	angles->x = -pitch;
	angles->y = yaw;
	angles->z = 0;
}

void Spreadz::VectorAnglesZ(Vector forward, Vector angles)
{
	float   tmp, yaw, pitch;

	if (forward.y == 0 && forward.x == 0)
	{
		yaw = 0;
		if (forward.z > 0)
			pitch = 90.0;
		else
			pitch = 270.0;
	}
	else
	{
		yaw = (float)(atan2(forward.y, forward.x) * 180.0 / M_PI);

		if (yaw < 0) yaw += 360.0;

		tmp = (float)sqrt(forward.x*forward.x + forward.y*forward.y);

		pitch = (float)(atan2(forward.z, tmp) * 180 / M_PI);
	}

	angles.x = -pitch;
	angles.y = yaw;
	angles.z = 0;
}

float Spreadz::RandomFloat(float min, float max)
{
	typedef float(*RandomFloat_t)(float, float);
	static RandomFloat_t m_RandomFloat = (RandomFloat_t)GetProcAddress(GetModuleHandle("vstdlib.dll"), "RandomFloat");
	return m_RandomFloat(min, max);
}

void Spreadz::RandomSeed(UINT seed)
{
	typedef void(*RandomSeed_t)(UINT);
	static RandomSeed_t m_RandomSeed = (RandomSeed_t)GetProcAddress(GetModuleHandle("vstdlib.dll"), "RandomSeed");
	m_RandomSeed(seed);
	return;
}



float Spreadz::GetInaccuracy(C_BaseCombatWeapon *pWeapon)
{
	DWORD dwInaccuracyVMT = (*reinterpret_cast< PDWORD_PTR* >(pWeapon))[464]; //459
	return ((float(__thiscall*)(C_BaseCombatWeapon*)) dwInaccuracyVMT)(pWeapon);
}

float Spreadz::GetSpread(C_BaseCombatWeapon *pWeapon)
{
	DWORD dwSpreadVMT = (*reinterpret_cast< PDWORD_PTR* >(pWeapon))[465]; //460
	return ((float(__thiscall*)(C_BaseCombatWeapon*)) dwSpreadVMT)(pWeapon);
}

void Spreadz::UpdateAccuracyPenalty(C_BaseCombatWeapon *pWeapon)
{
	DWORD dwUpdateVMT = (*reinterpret_cast< PDWORD_PTR* >(pWeapon))[466]; //461
	return ((void(__thiscall*)(C_BaseCombatWeapon*)) dwUpdateVMT)(pWeapon);
}


//6C0 432
#include "checksum_md5.h"




inline void CrossProductZ(const float* a, const float* b, float* r)
{
	r[0] = a[1] * b[2] - a[2] * b[1];
	r[1] = a[2] * b[0] - a[0] * b[2];
	r[2] = a[0] * b[1] - a[1] * b[0];
}
void Spreadz::SpreadFactor(CUserCmd *pCmd, C_BaseCombatWeapon *pWeapon)
{
	Vector vecForward, vecRight, vecDir, vecUp, vecAntiDir;
	float flSpread, flInaccuracy, flSpreadX, flSpreadY;

	Vector qAntiSpread;
	ALX.pPlayerESP->NormalizeAngle(pCmd->viewangles);
	ALX.pPlayerESP->ClampAngles(pCmd->viewangles);

	UpdateAccuracyPenalty(pWeapon);

	flSpread = GetSpread(pWeapon);

	flInaccuracy = GetInaccuracy(pWeapon);
	pCmd->random_seed = MD5_PseudoRandom(pCmd->command_number) & 0x7FFFFFFF;
	RandomSeed((pCmd->random_seed & 0xFF) + 1);


	float flRandPi_1 = RandomFloat(0.0f, 2.0f * M_PI);
	float flRandInaccuracy = RandomFloat(0.0f, flInaccuracy);
	float flRandPi_2 = RandomFloat(0.0f, 2.0f * M_PI);
	float flRandSpread = RandomFloat(0, flSpread);



	flSpreadX = cos(flRandPi_1) * flRandInaccuracy + cos(flRandPi_2) * flRandSpread;
	flSpreadY = sin(flRandPi_1) * flRandInaccuracy + sin(flRandPi_2) * flRandSpread;

	AngleToVectors(pCmd->viewangles, &vecForward, &vecRight, &vecUp);

	vecDir.x = (float)((float)(vecRight.x * flSpreadX) + vecForward.x) + (float)(vecUp.x * flSpreadY);
	vecDir.y = (float)((float)(flSpreadX * vecRight.y) + vecForward.y) + (float)(flSpreadY * vecUp.y);
	vecDir.z = (float)((float)(vecRight.z * flSpreadX) + vecForward.z) + (float)(vecUp.z * flSpreadY);

	//////var2///////////////////////////////////////////////////////////////
	//vecDir.x = vecForward.x + flSpreadX  * vecRight.x + flSpreadY * vecUp.x;
	//vecDir.y = vecForward.y + flSpreadX  * vecRight.y + flSpreadY * vecUp.y;
	//vecDir.z = vecForward.z + flSpreadX  * vecRight.z + flSpreadY * vecUp.z;
	//////////////////////////////////////////////////////////////////////////

	vecAntiDir = vecForward + (vecRight * -flSpreadX) + (vecUp * -flSpreadY);

	vecAntiDir.NormalizeInPlace();

	VectorAngles(&vecAntiDir, &qAntiSpread);

	pCmd->viewangles = qAntiSpread;
	ALX.pPlayerESP->NormalizeAngle(pCmd->viewangles);
	ALX.pPlayerESP->ClampAngles(pCmd->viewangles);


}





float Spreadz::VectorNormalize_Custom(Vector& vec)
{
	float radius = sqrtf(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);

	float iradius = 1.f / (radius + FLT_EPSILON);

	vec.x *= iradius;
	vec.y *= iradius;
	vec.z *= iradius;

	return radius;
}


void Normalize(Vector &vIn, Vector &vOut)
{
	float flLen = vIn.Length();

	if (flLen == 0)
	{
		vOut.Init(0, 0, 1);
		return;
	}

	flLen = 1 / flLen;

	vOut.Init(vIn.x * flLen, vIn.y * flLen, vIn.z * flLen);
}


void Spreadz::AngleVectors(const Vector &angles, Vector *forward)
{
	float    sp, sy, cp, cy;

	sy = sin(DEG2RAD(angles[1]));
	cy = cos(DEG2RAD(angles[1]));
	sp = sin(DEG2RAD(angles[0]));
	cp = cos(DEG2RAD(angles[0]));


	forward->x = cp*cy;
	forward->y = cp*sy;
	forward->z = -sp;
}

bool Spreadz::CanShoot()
{

	CBaseEntity* pLocalEntity = ALX.pEntList->GetClientEntity(ALX.pEngine->GetLocalPlayer());
	

	float flRate = 0.1f;

	C_BaseCombatWeapon *pWeapon = ALX.PSpreadz->GetBaseCombatActiveWeapon(pLocalEntity);

	int iUnknown0 = 0;

	float NextAttack = pWeapon->fNextAttack2();
	int iClip = pWeapon->m_Clip();

	while (pWeapon->fNextAttack2() <= ALX.pGlobals->curtime + flRate)
	{
		NextAttack = (NextAttack + flRate);

		iUnknown0++;
	}

	if (iUnknown0 > iClip)
	{
		iUnknown0 = iClip;
		iClip -= iUnknown0;
	}

	if (iUnknown0 <= ALX.pGlobals->interval_per_tick)
	{
		return true;
	}

	return false;

}


void Spreadz::Spinbot(CUserCmd* _pCommand)
{


	if (_pCommand->buttons & IN_ATTACK)
		return;

	Vector viewforward, viewright, viewup, aimforward, aimright, aimup;
	Vector qAimAngles;

	float forward = _pCommand->forwardmove;
	float right = _pCommand->sidemove;
	float up = _pCommand->upmove;

	qAimAngles.Init(0.0f, _pCommand->viewangles.y, 0.0f);
	AngleToVectors(qAimAngles, &viewforward, &viewright, &viewup);

	float fTime = ALX.pEngine->Time();
	_pCommand->viewangles.y = (vec_t)(fmod(fTime / 0.1f * 360.0f, 360.0f));
	qAimAngles.Init(0.0f, _pCommand->viewangles.y, 0.0f);

	AngleToVectors(qAimAngles, &aimforward, &aimright, &aimup);

	Vector vForwardNorm;
	Normalize(viewforward, vForwardNorm);
	Vector vRightNorm;
	Normalize(viewright, vRightNorm);
	Vector vUpNorm;
	Normalize(viewup, vUpNorm);

	_pCommand->forwardmove = DotProduct(forward * vForwardNorm, aimforward) + DotProduct(right * vRightNorm, aimforward) + DotProduct(up * vUpNorm, aimforward);
	_pCommand->sidemove = DotProduct(forward * vForwardNorm, aimright) + DotProduct(right * vRightNorm, aimright) + DotProduct(up * vUpNorm, aimright);
	_pCommand->upmove = DotProduct(forward * vForwardNorm, aimup) + DotProduct(right * vRightNorm, aimup) + DotProduct(up * vUpNorm, aimup);

	ALX.pPlayerESP->NormalizeAngle(_pCommand->viewangles);
	ALX.pPlayerESP->ClampAngles(_pCommand->viewangles);
}

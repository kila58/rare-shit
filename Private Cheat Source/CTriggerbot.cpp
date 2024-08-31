#include "CTriggerbot.h"


Vector GetEyePositionZ(CBaseEntity* pEntity)
{
	Vector vecViewOffset = *reinterpret_cast< Vector* >(reinterpret_cast< int >(pEntity)+0x104);

	return pEntity->GetAbsOrigin() + vecViewOffset;
}

float DotProductT2(const float* a, const float* b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

void VectorTransformA22(const float *in1, const matrix3x4& in2, float *out)
{

	out[0] = DotProductT2(in1, in2[0]) + in2[0][3];
	out[1] = DotProductT2(in1, in2[1]) + in2[1][3];
	out[2] = DotProductT2(in1, in2[2]) + in2[2][3];
}

inline void VectorTransformZ22(const Vector& in1, const matrix3x4 &in2, Vector &out)
{
	VectorTransformA22(&in1.x, in2, &out.x);
}


bool CTrigger::Trigger(CUserCmd *pCommand, CBaseEntity *pLocal)//call it instead old triger inside intro
{

	Vector Src, Dst, vAngle, min, max, delta;
	matrix3x4 matrix[128];
	//studiohdr_t* pStudioHdr;
	//mstudiohitboxset_t* pHitboxSet;
	//mstudiobbox_t* box;
	CBaseEntity* pEnemy;


	//Setup our "look Vector"
	Src = GetEyePositionZ(pLocal);
	vAngle = pCommand->viewangles;


	ALX.PSpreadz->AngleVectors(vAngle, &vAngle);
	ALX.PSpreadz->VectorNormalize_Custom(vAngle);

	Dst = vAngle * 8192 + Src;

	CTraceFilter filter;
	trace_t tr;
	Ray_t ray;
	filter.pSkip = pLocal;

	ray.Init(Src, Dst);
	ALX.pEngineTrace->TraceRay(ray, 0x4600400B, &filter, &tr);////0x4600400B 0x46004003

	//If we don't hit a human we return

	if (tr.allsolid)//|| tr.startsolid)
		return false;
	if (tr.DidHitWorld())
		return false;


	if (!tr.m_pEnt)
		return false;



	if (tr.m_pEnt->GetTeamNum() == pLocal->GetTeamNum())//check for team
		return false;

	if (!tr.m_pEnt->GetHealth() > 0)//check for static shit,  we need only enemies
		return false;
//
	//if (tr.m_pEnt->GetTeamNum() != pLocal->GetTeamNum())
		//return true;

	if (!tr.m_pEnt->SetupBones(matrix, 128, 0x00000100, ALX.pEngine->Time()))
		return false;


	//Create the delta
	VectorSubtract(Dst, Src, delta);

	

	Vector minz, maxz;


	//DO_ONCE(
	static bool drama = 0;
	if (drama == 0)
	{
		/*Hitbox[0].Setup(BONE_PELVIS, Vector(-6.42f, -5.7459f, -6.8587f), Vector(4.5796f, 4.5796f, 6.8373f));
		Hitbox[1].Setup(BONE_L_THIGH, Vector(1.819f, -3.959f, -2.14f), Vector(22.149002f, 3.424f, 4.5796f));
		Hitbox[2].Setup(BONE_L_CALF, Vector(2.0758f, -3.21f, -2.1507f), Vector(19.26f, 2.675f, 3.0495f));
		Hitbox[3].Setup(BONE_L_FOOT, Vector(1.8725f, -2.675f, -2.4075f), Vector(5.6175f, 9.694201f, 2.4075f));
		Hitbox[4].Setup(BONE_R_THIGH, Vector(1.819f, -3.7557f, -4.5796f), Vector(22.149002f, 3.424f, 2.14f));
		Hitbox[5].Setup(BONE_R_CALF, Vector(2.0758f, -3.21f, -2.8462f), Vector(19.26f, 2.675f, 2.247f));
		Hitbox[6].Setup(BONE_R_FOOT, Vector(1.8725f, -2.675f, -2.4075f), Vector(5.6175f, 9.694201, 2.4075f));
		Hitbox[7].Setup(BONE_SPINE2, Vector(-4.28f, -4.5796f, -6.3879f), Vector(3.21f, 5.885f, 6.2809f));
		Hitbox[8].Setup(BONE_SPINE3, Vector(-4.28f, -5.029f, -6.0883f), Vector(3.21f, 5.885f, 5.9813f));
		Hitbox[9].Setup(BONE_SPINE4, Vector(-4.28f, -5.35f, -5.885f), Vector(2.9211f, 5.1467f, 5.885f));*/
		//Hitbox[10].Setup(BONE_NECK, Vector(0.3317f, -3.0174f, -2.4503f), Vector(3.4026f, 2.4182f, 2.354f));
		Hitbox[11].Setup(BONE_HEAD, Vector(-2.7713f, -2.8783f, -3.103f), Vector(6.955f, 3.5203f, 3.0067f));
		/*Hitbox[12].Setup(BONE_L_UPPER_ARM, Vector(-2.675f, -3.21f, -2.14f), Vector(12.84f, 3.21f, 2.14f));
		Hitbox[13].Setup(BONE_L_FOREARM, Vector(-0.f, -2.14f, -2.14f), Vector(9.63f, 2.14f, 2.14f));
		Hitbox[14].Setup(BONE_L_HAND, Vector(-1.7227f, -1.2198f, -1.3803f), Vector(4.4726f, 1.2198f, 1.3803f));
		Hitbox[15].Setup(BONE_R_UPPER_ARM, Vector(-2.675f, -3.21f, -2.14f), Vector(12.84f, 3.21f, 2.14f));
		Hitbox[16].Setup(BONE_R_FOREARM, Vector(-0.f, -2.14f, -2.14f), Vector(9.63f, 2.14f, 2.14f));
		Hitbox[17].Setup(BONE_R_HAND, Vector(-1.7227f, -1.2198f, -1.3803f), Vector(4.4726f, 1.2198f, 1.3803f));
		Hitbox[18].Setup(BONE_L_CLAVICLE, Vector(-0.f, -3.21f, -5.35f), Vector(7.49f, 4.28f, 3.21f));
		Hitbox[19].Setup(BONE_R_CLAVICLE, Vector(-0.f, -3.21f, -3.21f), Vector(7.49f, 4.28f, 5.35f));
		Hitbox[20].Setup(BONE_HEAD, Vector(-2.5038f, 2.009f, -1.1021f), Vector(6.3023f, 5.2965f, 0.9951f));
		Hitbox[21].Setup(BONE_SPINE4, Vector(-0.2996f, -6.0027f, -4.996901f), Vector(5.4998f, 2.5038f, 5.1039f));*/

	}


	//for (int i = 0; i < 2; i++)
	//{

		int bone = Hitbox[11].iBone;
		Vector vMaxUntransformed = Hitbox[11].vMax;
		Vector vMinUntransformed = Hitbox[11].vMin;


		if (IntersectRayWithOBB(Src, delta, matrix[bone], vMinUntransformed, vMaxUntransformed))
			return true;
	//}


	//We didn't hit anything
	return false;


}




bool CTrigger::IntersectRayWithOBB(const Vector &vecRayStart, const Vector &vecRayDelta, const matrix3x4 &matOBBToWorld, const Vector &vecOBBMins, const Vector &vecOBBMaxs)
{


	
	Vector vecBoxExtents = (vecOBBMins + vecOBBMaxs) * 0.5;
	Vector vecBoxCenter;


	// transform to world space
	VectorTransformZ22(vecBoxExtents, matOBBToWorld, vecBoxCenter);


	// calc extents from local center
	vecBoxExtents = vecOBBMaxs - vecBoxExtents;


	// OPTIMIZE: This is optimized for world space.  If the transform is fast enough, it may make more
	// sense to just xform and call UTIL_ClipToBox() instead.  MEASURE THIS.


	// save the extents of the ray along 
	Vector extent, uextent;
	Vector segmentCenter = vecRayStart + vecRayDelta - vecBoxCenter;


	extent.x = extent.y = extent.z = 0.0f;


	// check box axes for separation
	for (int j = 0; j < 3; j++)
	{
		extent[j] = vecRayDelta.x * matOBBToWorld[0][j] + vecRayDelta.y * matOBBToWorld[1][j] + vecRayDelta.z * matOBBToWorld[2][j];
		uextent[j] = fabsf(extent[j]);
		float coord = segmentCenter.x * matOBBToWorld[0][j] + segmentCenter.y * matOBBToWorld[1][j] + segmentCenter.z * matOBBToWorld[2][j];
		coord = fabsf(coord);


		if (coord >(vecBoxExtents[j] + uextent[j]))
			return false;
	}


	// now check cross axes for separation
	float tmp, cextent;
	Vector cross;
	//D3DXVec3Cross(&cross, &vecRayDelta, &segmentCenter);// = vecRayDelta.Cross(segmentCenter);


	CrossProduct(vecRayDelta, segmentCenter,cross);

	cextent = cross.x * matOBBToWorld[0][0] + cross.y * matOBBToWorld[1][0] + cross.z * matOBBToWorld[2][0];
	cextent = fabsf(cextent);
	tmp = vecBoxExtents[1] * uextent[2] + vecBoxExtents[2] * uextent[1];
	if (cextent > tmp)
		return false;


	cextent = cross.x * matOBBToWorld[0][1] + cross.y * matOBBToWorld[1][1] + cross.z * matOBBToWorld[2][1];
	cextent = fabsf(cextent);
	tmp = vecBoxExtents[0] * uextent[2] + vecBoxExtents[2] * uextent[0];
	if (cextent > tmp)
		return false;


	cextent = cross.x * matOBBToWorld[0][2] + cross.y * matOBBToWorld[1][2] + cross.z * matOBBToWorld[2][2];
	cextent = fabsf(cextent);
	tmp = vecBoxExtents[0] * uextent[1] + vecBoxExtents[1] * uextent[0];
	if (cextent > tmp)
		return false;


	return true;
}

bool CTrigger::Triggerbot(CBaseEntity*   pLocal, CUserCmd* cmd)
{

	Vector vDir;
	Vector vecStart = GetEyePositionZ(pLocal);
	Vector vecSum;
	Vector vecEnd, Final, qView;

	Vector viewang = cmd->viewangles;


	ALX.PSpreadz->AngleVectors(viewang, &vDir);
	ALX.PSpreadz->VectorNormalize_Custom(vDir);

	vecEnd = vDir * 8192 + vecStart;

	CTraceFilter filter;
	trace_t tr;
	Ray_t ray;
	filter.pSkip = pLocal;

	ray.Init(vecStart, vecEnd);
	ALX.pEngineTrace->TraceRay(ray, 0x4600400B, &filter, &tr);////0x4600400B 0x46004003

	//COLLISION_GROUP_BREAKABLE_GLASS |  00000000000000110  0000000000000006 ????? ????????? ????? ?????? MASK_NPCWORLDSTATIC | CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_HITBOX
	if (tr.allsolid)//|| tr.startsolid)
		return false;
	if (tr.DidHitWorld())
		return false;



	//if (!(tr.hitgroup <= 10 && tr.hitgroup > 0))//its check for if we hit head or
	//return false;

	if (!tr.m_pEnt)
		return false;



	if (tr.m_pEnt->GetTeamNum() == pLocal->GetTeamNum())//check for team
		return false;

	if (!tr.m_pEnt->GetHealth() > 0)//check for static shit,  we need only enemies
		return false;
	//	if(tr.m_pEnt->IsProtected())//for spawn protection, works fine
	//return false;

	if (tr.m_pEnt->GetTeamNum() != pLocal->GetTeamNum() && tr.hitgroup == 1)
		return true;


}

void CTrigger::intro(CBaseEntity*   pLocal, CUserCmd* pCmd, C_BaseCombatWeapon *pWeapon)
{

	for (int i = 1; i <= ALX.pEntList->GetHighestEntityIndex(); i++)
	{
		CBaseEntity* pEntity = ALX.pEntList->GetClientEntity(i);

		if (pEntity == NULL)
			continue;


		if (ALX.pEngine->GetPlayerInfo(i, &pInfo) == false)
			continue;

		if (!ALX.pDrawManager->GetBonePosition(pEntity, vHead, BONE_HEAD))
			continue;


		if (ALX.pPlayerESP->IsVisible(GetEyePositionZ(pLocal), GetEyePositionZ(pEntity), pEntity))
		{


			if (Triggerbot(pLocal, pCmd))
			{

				if (ALX.pCvar->autopistol)
				{

					if (pCmd->buttons & IN_ATTACK)
					{
						static bool bAttack = false;
						if (bAttack)    pCmd->buttons |= IN_ATTACK;
						else
							pCmd->buttons &= ~IN_ATTACK;
						bAttack = !bAttack;
					}
				}
				else
				{
					pCmd->buttons |= IN_ATTACK;
				}
			}

		}

	}

}

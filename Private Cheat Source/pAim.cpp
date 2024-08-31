#include "SDK.h"
#include "pAim.h"
#include "Control Variables.h"
#include "CDrawManager.h"
#include "Player ESP.h"

Vector GetOrigin1(CBaseEntity* pEntity)
{
	return *reinterpret_cast< Vector* >(reinterpret_cast< int >(pEntity)+0x134);
}


Vector PRotator::Randomize(Vector vAngles)
{

	if (abs(curX - destX) < .05f)
	{
		destX = rand() % (int)(ALX.pCvar->aim_human_scale * 10) + 1;
		destX /= 500;
		int positive = rand() % 2 + 1;
		if (positive == 2)
			destX = -destX;
	}

	if (abs(curY - destY) < .05f)
	{
		destY = rand() % (int)(ALX.pCvar->aim_human_scale * 10) + 1;
		destY /= 500;
		int positive = rand() % 2 + 1;
		if (positive == 2)
			destY = -destY;
	}

	int speed = 20 - int(ALX.pCvar->aim_human_speed);
	curX += (destX - curX) / ((15 * speed) + 10);

	curY += (destY - curY) / ((15 * speed) + 10);

	vAngles.x += curX;
	vAngles.y += curY;

	lastX = curX;
	lastY = curY;



	return vAngles;

}

bool IsAlive1(CBaseEntity* pEntity)
{
	char szLifeState = *(char*)((DWORD)pEntity + 0x25B);
	return (szLifeState == 0);
}

Vector GetEyePosition1(CBaseEntity* pEntity)
{
	Vector vecViewOffset = *reinterpret_cast< Vector* >(reinterpret_cast< int >(pEntity)+0x104);

	return GetOrigin1(pEntity) + vecViewOffset;
}

bool PRotator::EdgeAntiAim(CBaseEntity* pLocal, CUserCmd *cmd, float angle)
{
	bool ret = false;
	static CTraceFilter filter;

	if (cmd->buttons & IN_ATTACK)
		return false;

	Vector localPosition = GetEyePosition1(pLocal);

	for (int y = 0; y < 360; y++)
	{
		Vector tmp(10.f, cmd->viewangles.y, 0.f);
		tmp.y += y;
		ALX.pPlayerESP->NormalizeAngle(tmp);

		Vector forward;
		ALX.PSpreadz->AngleVectors(tmp, &forward);

		float length = ((16 + 3) + ((16 + 3) * sin(DEG2RAD(10.f)))) + 5;

		forward *= length;

		Ray_t ray;
		trace_t traceData;

		ray.Init(localPosition, (localPosition + forward));
		ALX.pEngineTrace->TraceRay(ray, 0x200400B, (CTraceFilter*)&filter, &traceData);

		if (traceData.fraction != 1.f)
		{
			Vector angles;
			Vector Negate = traceData.plane.normal;
			Negate *= -1;
			ALX.PSpreadz->VectorAngles(&Negate, &angles);

			tmp.y = angles.y;

			ALX.pPlayerESP->NormalizeAngle(tmp);

			trace_t leftTrace, rightTrace;

			Vector left, right;
			ALX.PSpreadz->AngleVectors(tmp + Vector(0.f, 30.f, 0.f), &left);
			ALX.PSpreadz->AngleVectors(tmp - Vector(0.f, 30.f, 0.f), &right);

			left *= (length + (length * sin(DEG2RAD(30.f))));
			right *= (length + (length * sin(DEG2RAD(30.f))));


			ray.Init(localPosition, (localPosition + left));
			ALX.pEngineTrace->TraceRay(ray, 0x200400B, (CTraceFilter*)&filter, &leftTrace);

			ray.Init(localPosition, (localPosition + right));
			ALX.pEngineTrace->TraceRay(ray, 0x200400B, (CTraceFilter*)&filter, &rightTrace);


			if ((leftTrace.fraction == 1.f)
				&& (rightTrace.fraction != 1.f))
			{
				//tmp.y += 90.f-(45.f/2.f);
				//tmp.y -= 45.f;
				tmp.y -= 90.f;
				// LEFT
			}
			else if ((leftTrace.fraction != 1.f)
				&& (rightTrace.fraction == 1.f))
			{
				//tmp.y -= 90.f-(45.f/2.f);
				//tmp.y += 45.f;
				tmp.y += 90.f;
				// RIGHT
			}

			cmd->viewangles.y = tmp.y;
			cmd->viewangles.y -= angle;
			ret = true;
		}
	}

	return ret;
}

bool PRotator::EdgeAntiAimZ(CBaseEntity *localPlayer, CUserCmd *cmd, float angle)
{
	bool ret = false;

	Vector localPosition = GetEyePosition1(localPlayer);

	for (int y = 0; y < 360; y++)
	{
		Vector tmp(10.f, cmd->viewangles.y, 0.f);
		tmp.y += y;

		ALX.pPlayerESP->NormalizeAngle(tmp);

		Vector forward;
		ALX.PSpreadz->AngleVectors(tmp, &forward);

		float length = ((16 + 3) + ((16 + 3) * sin(DEG2RAD(10.f)))) + 5;

		forward *= length;

		Ray_t ray;
		trace_t traceData;

		ray.Init(localPosition, (localPosition + forward));
		ALX.pEngineTrace->TraceRay(ray, 0x200400B, NULL, &traceData);

		if (traceData.fraction != 1.f)
		{
			Vector angles;
			Vector Negate = traceData.plane.normal;
			Negate *= -1;
			ALX.PSpreadz->VectorAngles(&Negate, &angles);

			tmp.y = angles.y;

			ALX.pPlayerESP->NormalizeAngle(tmp);

			trace_t leftTrace, rightTrace;

			Vector left, right;
			ALX.PSpreadz->AngleVectors(tmp + Vector(0.f, 30.f, 0.f), &left);
			ALX.PSpreadz->AngleVectors(tmp - Vector(0.f, 30.f, 0.f), &right);

			left *= (length + (length * sin(DEG2RAD(30.f))));
			right *= (length + (length * sin(DEG2RAD(30.f))));


			ray.Init(localPosition, (localPosition + left));
			ALX.pEngineTrace->TraceRay(ray, 0x200400B, NULL, &leftTrace);


			ray.Init(localPosition, (localPosition + right));
			ALX.pEngineTrace->TraceRay(ray, 0x200400B, NULL, &rightTrace);


			if ((leftTrace.fraction == 1.f)
				&& (rightTrace.fraction != 1.f))
			{
				//tmp.y += 90.f-(45.f/2.f);
				//tmp.y -= 45.f;
				tmp.y -= 90.f;
				// LEFT
			}
			else if ((leftTrace.fraction != 1.f)
				&& (rightTrace.fraction == 1.f))
			{
				//tmp.y -= 90.f-(45.f/2.f);
				//tmp.y += 45.f;
				tmp.y += 90.f;
				// RIGHT
			}

			ALX.pPlayerESP->NormalizeAngle(tmp);
			ALX.pPlayerESP->ClampAngles(tmp);
		

			cmd->viewangles.y = tmp.y;
			cmd->viewangles.y -= angle;

			
			ret = true;
		}
	}

	return ret;
}

float PRotator::GetAntiAimAngles(CBaseEntity* pLocal)
{

	if (!pLocal) return -1;

	int     best = 0;
	float	besttemp = 9999;
	Vector  vAntiAim = Vector(0, -90, 0);

	for (int Index = 1; Index <= ALX.pEntList->GetHighestEntityIndex(); Index++)
	{

		CBaseEntity* pEntity = ALX.pEntList->GetClientEntity(Index);

		if (pEntity == NULL)
			continue;
		if (pEntity->GetIndex() == pLocal->GetIndex())
			continue;
		if (!IsAlive1(pEntity))
			continue;
		if (!IsAlive1(pLocal))
			continue;

		Vector vMyPos = pLocal->GetOrigin();
		Vector vTarget = pEntity->GetOrigin();

		float temp = vMyPos.DistTo(vTarget);

		if (temp < besttemp)
		{
			best = Index;
			besttemp = temp;
			ALX.PAim->CalcAngleZ(vMyPos, vTarget, vAntiAim);
			ALX.pPlayerESP->NormalizeAngle(vAntiAim);
			ALX.pPlayerESP->ClampAngles(vAntiAim);
		}
	}
	return vAntiAim.y - 180;
}

BYTE PRotator::m_MoveType(CBaseEntity* pLocal)
{
	return *(BYTE*)((DWORD)pLocal + ALX.pPlayerVariables->m_movetype); //9F0  ASCII "DT_BaseToggle" ASCII "m_movementType" 0x174

}

float PRotator::GetAntiAimAngles2(CBaseEntity* pLocal)
{

	if (!pLocal) return -1;

	int     best = 0;
	float	besttemp = 9999;
	Vector  vAntiAim = Vector(0, -90, 0);


	for (int Index = 1; Index <= ALX.pEntList->GetHighestEntityIndex(); Index++)
	{

		CBaseEntity* pEntity = ALX.pEntList->GetClientEntity(Index);

		if (pEntity == NULL)
			continue;
		if (pEntity->GetIndex() == pLocal->GetIndex())
			continue;
		if (!IsAlive1(pEntity))
			continue;
		if (!IsAlive1(pLocal))
			continue;

		Vector vMyPos = pLocal->GetOrigin();
		Vector vTarget = pEntity->GetOrigin();

		float temp = vMyPos.DistTo(vTarget);

		if (temp < besttemp)
		{
			best = Index;
			besttemp = temp;

			ALX.PAim->CalcAngleZ(vMyPos, vTarget, vAntiAim);
			ALX.pPlayerESP->NormalizeAngle(vAntiAim);
			//ALX.PSpreadz->ClampAngles(vAntiAim);
		}
	}
	return vAntiAim.y;
}


float GetCrossDistance(Vector& to)
{

	int screenwidth, screenheight;

	ALX.pEngine->GetScreenSize(screenwidth, screenheight);

	float xMid = (float)(screenwidth / 2);
	float yMid = (float)(screenheight / 2);

	Vector vPos;
	ALX.pDrawManager->WorldToScreen(to, vPos);

	return sqrt(pow(vPos.x - xMid, 2) + pow(vPos.y - yMid, 2));
}


PRotator::PRotator(void){
	flBestDist = 99999.9f;
	m_nTarget = -1;
}
void PRotator::DrapTrgtZ(void){
	flBestDist = 99999.9f;
	m_nTarget = -1;
}
int	PRotator::GetTrgtZ(void)
{
	return m_nTarget;
}
float PRotator::Get3DDistanceZ(Vector from, Vector to)
{
	Vector angle;
	angle.x = to.x - from.x;	angle.y = to.y - from.y;	angle.z = to.z - from.z;

	return sqrt(angle.x*angle.x + angle.y*angle.y + angle.z*angle.z);
}

void PRotator::MakeVectorZ(Vector& pfIn, Vector& pfOut)
{
	float pitch;
	float yaw;
	float tmp;

	pitch = (float)(pfIn.x * M_PI / 180);
	yaw = (float)(pfIn.y * M_PI / 180);
	tmp = (float)cos(pitch);

	pfOut.x = (float)(-tmp * -cos(yaw));
	pfOut.y = (float)(sin(yaw)*tmp);
	pfOut.z = (float)-sin(pitch);
}

void PRotator::CalcAngleZ(Vector& src, Vector& dst, Vector &angles)
{

	Vector delta((src.x - dst.x), (src.y - dst.y), (src.z - dst.z));
	double hyp = sqrt(delta.x*delta.x + delta.y*delta.y);

	angles.x = (float)(atanf((delta.z) / hyp) * M_RADPI);// (delta.z + 64.06f)/hyp)if u aim to origin  //  + 77.06f + 10.06f
	angles.y = (float)(atanf(delta.y / delta.x) * M_RADPI);
	angles.z = 0.0f;

	if (delta.x >= 0.0)
		angles.y += 180.0f;



}



float PRotator::GetFOVZ(Vector& vMyView, Vector& vMyPos, Vector& vHitbox)//for vector
{
	float flFov;

	float fDistance;
	Vector vAng, vAim;
	CalcAngleZ(vMyPos, vHitbox, vAng);

	MakeVectorZ(vMyView, vAim);
	MakeVectorZ(vAng, vAng);
	float mag_s = sqrt((vAim.x * vAim.x) + (vAim.y * vAim.y) + (vAim.z * vAim.z));
	float mag_d = mag_s;
	float u_dot_v = ((vAim.x * vAng.x) + (vAim.y * vAng.y) + (vAim.z * vAng.z));
	flFov = acos(u_dot_v / (mag_s*mag_d)) * (180.0 / M_PI);
	return flFov;
}

void PRotator::Smooth(Vector& flLocalAngles, float iSmooth)
{
	Vector src;
	ALX.pEngine->GetViewAngles(src);//grab current ang for smooth

	Vector qDelta = src - flLocalAngles;
	if (qDelta[0]>180)  qDelta[0] -= 360;
	if (qDelta[1]>180)  qDelta[1] -= 360;
	if (qDelta[0]<-180) qDelta[0] += 360;
	if (qDelta[1]<-180) qDelta[1] += 360;
	flLocalAngles = src - qDelta / iSmooth;
	if (flLocalAngles[0] >  180) flLocalAngles[0] -= 360;
	if (flLocalAngles[1] >  180) flLocalAngles[1] -= 360;
	if (flLocalAngles[0] < -180) flLocalAngles[0] += 360;
	if (flLocalAngles[1] < -180) flLocalAngles[1] += 360;


}



Vector PRotator::GetPredictedVelocity(CBaseEntity* pEnt)
{

	return GetEyePosition1(pEnt) + GetVelocity(pEnt) * ALX.pGlobals->interval_per_tick;

}



Vector PRotator::GetVelocity(CBaseEntity* pEnt)
{
	return *(Vector*)((DWORD)pEnt + 0x110);
}

void PRotator::ApplyPrediction(Vector &vAim, Vector &vMe, Vector &vOut, CBaseEntity* pEnt, CBaseEntity* pLocal)
{
	Vector vDelta(0, 0, 0);


	float flLatency = ALX.pEngine->GetNetChannelInfo()->GetLatency(FLOW_OUTGOING);

	float fDelay = flLatency / 1000;
	Vector vDeltaZ = (GetVelocity(pEnt) - GetVelocity(pLocal));


	//vDelta.x *= flLatency * 1000;
	//vDelta.y *= flLatency * 1000;
	//vDelta.z *= flLatency * 1000;

	vOut = vAim + vDeltaZ * fDelay;

}

void PRotator::ApplySpeedPrediction(Vector &vAim, Vector &vOut, Vector &EntitySpeed, CBaseEntity* pLocal)
{


	Vector MySpeed = GetVelocity(pLocal);
	Vector DeltaToAdd;
	Vector vSpeedDelta = EntitySpeed - MySpeed;


	float addtime;
	if (ALX.pCvar->smooth != 0) { addtime = (0.65 / 100) + (1 / ALX.pCvar->smooth); }
	else addtime = 0;



	DeltaToAdd = addtime *  vSpeedDelta;
	vOut = vAim + DeltaToAdd;



}



bool PRotator::HitScans(CBaseEntity* pLocal, CBaseEntity* pTarget, Vector &toAIM)
{
	static unsigned int bonearrays[16] = { 0, 1, 5, 7, 8, 9, 10, 13, 14, 15, 23, 24, 25, 26, 27, 28 };


	for (int i = 0; i < 16; i++)
	{
		ALX.pDrawManager->GetBonePosition(pTarget, toAIM, bonearrays[i]);
		
			return true;
		
	}
	return false;
}





bool PRotator::AutoWall(Vector vPos, CBaseEntity* pLocal, CBaseEntity* pEntity) //hehe
{
	trace_t tr;
	Ray_t ray;
	Vector vStart, vEnd, vEndPos[3];
	vStart = GetEyePosition1(pLocal);
	vEnd = vPos;
	CTraceFilter filter;

	if (ALX.pPlayerESP->IsVisible(vStart,vEnd,pEntity))
		return true;


	filter.pSkip = pLocal;
	ray.Init(vStart, vEnd);

	ALX.pEngineTrace->TraceRay(ray, MASK_NPCWORLDSTATIC | CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_HITBOX | CONTENTS_GRATE, &filter, &tr);

	vEndPos[0] = tr.endpos;

	ray.Init(vEnd, vStart);
	filter.pSkip = pEntity;
	ALX.pEngineTrace->TraceRay(ray, MASK_NPCWORLDSTATIC | CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_HITBOX | CONTENTS_GRATE, &filter, &tr);

	vEndPos[1] = tr.endpos;

	VectorSubtract(vEndPos[0], vEndPos[1], vEndPos[2]);

	float flLength = VectorLength(vEndPos[2]);

	if (tr.fraction != 0)
	if (flLength < 14)
		return true;

	return false;
}

void PRotator::StealthRotation(CBaseEntity* pLocal, CUserCmd* cmd)
{
	int iBone;
	if (ALX.pCvar->aim_head)
	{
		iBone = 10;
	}
	if (ALX.pCvar->aim_chest)
	{
		iBone = 3;
	}
	if (ALX.pCvar->aim_neck)
	{
		iBone = 9;
	}
	if (ALX.pCvar->aim_stomach)
	{
		iBone = 5;
	}

	int m_target = -1;
	DrapTrgtZ();


	Vector PredOrg;
	Vector EnemySpeed;
	float distance = 99999.9f;


	for (int i = 1; i <= ALX.pEntList->GetHighestEntityIndex(); i++)//start iteration shit  or use ALX.pGlobals->maxclients...
	{

		CBaseEntity* pEntity = ALX.pEntList->GetClientEntity(i);

		if (pEntity == NULL)
			continue;
		if (pEntity->GetIndex() == pLocal->GetIndex())
			continue;

		//if ( pEntity->IsDormant( ) )
		//continue;
		if (!IsAlive1(pEntity))
			continue;
		if (!IsAlive1(pLocal))
			continue;

		//if(pEntity->IsProtected()) //spawnprotection
		//continue;
		//if(!pEntity->GotchaHealth())
		//continue;
		int  Health = pEntity->GetHealth();
		if (Health <= 0)
			continue;

		if (!ALX.pCvar->aimteam)
		{
			if (pEntity->GetTeamNum() == pLocal->GetTeamNum())
				continue;
		}

		if (ALX.pEngine->GetPlayerInfo(i, &pInfo) == false)
			continue;


		FOV = cmd->viewangles;


		if (!ALX.pDrawManager->GetBonePosition(pEntity, vHead, iBone))//boneselector()
			continue;


		vEyePs = GetEyePosition1(pLocal);
		Hitbox = vHead;


		float flCurrentDistance = Get3DDistanceZ(vEyePs, Hitbox); // Get distance between you and the target

		if (flCurrentDistance > flBestDist) // Just ignore players that are further than your current target
			continue;
//
		if (!ALX.pPlayerESP->IsVisible(GetOrigin1(pLocal), GetEyePosition1(pEntity), pEntity) && !ALX.pCvar->autowall || ALX.pCvar->hitscan)
		{
			//if (!HitScans(pLocal, pEntity, vHead))
				continue;				
		}

		if (ALX.pCvar->autowall)
		{
			if (!AutoWall(Hitbox, pLocal, pEntity))
			{
				continue;
			}
		}
		

		if (ALX.pCvar->hitscan)
		{
			if (!HitScans(pLocal, pEntity, vHead))
				continue;
		}


		if (GetFOVZ(FOV, vEyePs, vHead) >= ALX.pCvar->fov || distance < GetFOVZ(FOV, vEyePs, vHead))  //check FOV
			continue;


		distance = GetFOVZ(FOV, vEyePs, vHead);

		flBestDist = flCurrentDistance;
		m_target = i;


		EnemySpeed = GetVelocity(pEntity);
		PredOrg = vHead;


	}


	if (m_target == -1)
		return;

	Vector ReturnViewAA;
	//ALX.pEngine->GetViewAngles(ReturnViewAA); 
	ReturnViewAA = cmd->viewangles;
	float oldSidemove = cmd->sidemove;
	float oldForwardmove = cmd->forwardmove;



	if (ALX.pCvar->prediction){
		//ApplyPrediction( PredOrg, vEyePs, vPredicted, pEntity2 , pLocal );//changed to 78 or? dont work for me...
		ApplySpeedPrediction(PredOrg, vPredicted, EnemySpeed, pLocal);

	}
	else vPredicted = PredOrg;



	CalcAngleZ(vEyePs, vPredicted, vAim); //calculate ang 

	if (!ALX.pCvar->silent)
	{
		if (ALX.pCvar->smooth != 0)
		{
			float smoothdiff[2];
			Vector src = vAim;
			Vector flLocalAngles = cmd->viewangles;
			Vector back = flLocalAngles;
			src.x -= flLocalAngles.x;
			src.y -= flLocalAngles.y;
			if (src.x > 180) src.x -= 360;
			if (src.y > 180) src.y -= 360;
			if (src.x < -180) src.x += 360;
			if (src.x < -180) src.y += 360;
			smoothdiff[0] = src.x / (ALX.pCvar->smooth * 3);
			smoothdiff[1] = src.y / (ALX.pCvar->smooth * 3);
			back.x = flLocalAngles.x + smoothdiff[0];
			back.y = flLocalAngles.y + smoothdiff[1];
			back.z = flLocalAngles.z;
			if (back.x > 180)  back.x -= 360;
			if (back.y > 180)  back.y -= 360;
			if (back.x < -180) back.x += 360;
			if (back.y < -180) back.y += 360;
			vAim = back;
		}
	}

	Vector Punch = pLocal->GetPunchAngle();

	

	if (ALX.pCvar->aim_human_scale != 0)
	{
		vAim = Randomize(vAim);
	}

	ALX.pPlayerESP->NormalizeAngle(vAim);
	ALX.pPlayerESP->ClampAngles(vAim);


	Vector vMove(cmd->forwardmove, cmd->sidemove, cmd->upmove);


	float flSpeed = sqrt(vMove.x * vMove.x + vMove.y * vMove.y), flYaw;
	Vector qMove, qRealView(cmd->viewangles);
	ALX.PSpreadz->VectorAngles(&vMove, &qMove);

	if (ALX.pCvar->silent)//make silent
	{
		flYaw = DEG2RAD(cmd->viewangles.y - qRealView.y + qMove.y);
		cmd->forwardmove = cos(flYaw) * flSpeed;
		cmd->sidemove = sin(flYaw) * flSpeed;

		if (ALX.pCvar->stop_crouch)
		{

			cmd->forwardmove = 0.0f;
			cmd->sidemove = 0.0f;
			cmd->buttons |= IN_DUCK;
		}

		if (ALX.pCvar->rcs)
		{
			vAim -= Punch * 2;
		}


		cmd->viewangles = vAim;//silent aim

	
		ALX.pPlayerESP->NormalizeAngle(cmd->viewangles);
		ALX.pPlayerESP->ClampAngles(cmd->viewangles);

		if (ALX.pCvar->autoshoot)
		{
			if (ALX.pCvar->autopistol)
			{
				cmd->buttons |= IN_ATTACK;
				if (cmd->buttons & IN_ATTACK)
				{
				
					static bool bAttack = false;
					if (bAttack)    cmd->buttons |= IN_ATTACK;
					else
						cmd->buttons &= ~IN_ATTACK;
					bAttack = !bAttack;
				}
			}
			else
			{
				cmd->buttons |= IN_ATTACK;
			}

		}

	}
	else
	{


		if (ALX.pCvar->stop_crouch)
		{

			cmd->forwardmove = 0.0f;
			cmd->sidemove = 0.0f;
			cmd->buttons |= IN_DUCK;
		}

		if (ALX.pCvar->rcs)
		{
			vAim -= Punch * 2;
		}


		cmd->viewangles = vAim;
		ALX.pEngine->SetViewAngles(vAim);
		ALX.pPlayerESP->NormalizeAngle(cmd->viewangles);
		ALX.pPlayerESP->ClampAngles(cmd->viewangles);
		if (ALX.pCvar->autoshoot)
		{
			cmd->buttons |= IN_ATTACK;
			if (cmd->buttons & IN_ATTACK && ALX.pCvar->autopistol)
			{
				static bool bAttack = false;
				if (bAttack)    cmd->buttons |= IN_ATTACK;
				else
					cmd->buttons &= ~IN_ATTACK;
				bAttack = !bAttack;
			}
		}
	}

	DrapTrgtZ();

}
#include "CreateMove.h"
CCreateMove gCreateMove;

void C_RandomA::SetSeed(int iSeed)
{
	m_idum = ((iSeed < 0) ? iSeed : -iSeed);
	m_iy = 0;
}

int C_RandomA::GenerateRandomNumber()
{
	int j;
	int k;

	if (m_idum <= 0 || !m_iy){
		if (-(m_idum) < 1) m_idum = 1;
		else m_idum = -(m_idum);

		for (j = NTAB + 7; j >= 0; j--){
			k = (m_idum) / IQ;
			m_idum = IA * (m_idum - k * IQ) - IR * k;
			if (m_idum < 0) m_idum += IM;
			if (j < NTAB) m_iv[j] = m_idum;
		}
		m_iy = m_iv[0];
	}
	k = (m_idum) / IQ;
	m_idum = IA * (m_idum - k * IQ) - IR * k;
	if (m_idum < 0) m_idum += IM;
	j = m_iy / NDIV;
	m_iy = m_iv[j];
	m_iv[j] = m_idum;

	return m_iy;
}

float C_RandomA::RandomFloat(float flLow, float flHigh)
{
	float fl = AM * (float)this->GenerateRandomNumber();
	if (fl > RNMX) fl = RNMX;
	return (fl * (flHigh - flLow)) + flLow;
}
void ChikenGlow()
{
	/*
	Everything Chiken
	
	vecOrigin 0x0134
	|__m_bShouldGlow___________________________________ -> 0x0d8c
	|__m_clrGlow_______________________________________ -> 0x0d8
	*/
	for (int i = 0; i < ClientEntList->GetMaxEntities(); i++)
	{
		CBaseEntityNew* ent = (CBaseEntityNew*)ClientEntList->GetClientEntity(i);
		if (!ent)
			continue;
		if (ent->GetClientClass()->m_ClassID == 30)
		{
			bool* shouldGlow = (bool*)((DWORD)ent + 0xD8C); // m_bShouldGlow
			*shouldGlow = gCvars.chiken_glow;

			Color* colorGlow = (Color*)((DWORD)ent + 0xD8D); //m_clrGlow
			srand(Engine->Time());
			colorGlow->SetColor(rand() % 255, rand() % 255, rand() % 255, 255);
		}

	}
}
void AngleToVectors(const Vector &angles, Vector *forward, Vector *right, Vector *up)
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
void VectorAngles(Vector *forward, Vector *angles)
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
void VectorAnglesZ(Vector forward, Vector angles)
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
void Normalize(Vector angles)
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
void AngleVectorsZ(const Vector &angles, Vector *forward)
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
void __stdcall CL_FixMove(CUserCmd* cmd, Vector viewangles)
{
	Vector move, movenorm, dir, set;
	Vector movenormang, adjusted;

	float len;

	move.Init(cmd->forwardmove, cmd->sidemove, cmd->upmove);

	movenorm = move;

	VectorNormalize(movenorm);

	len = move.Length();

	VectorAngles(&movenorm, &movenormang);

	if ((cmd->viewangles.x >= 89.0f) || (cmd->viewangles.x <= -89.0f))
	{
		if (viewangles.x >= 0.0f && viewangles.x <= 89.0f)
		{
			viewangles.x = cmd->viewangles.x + 180.0f;
		}
		if (viewangles.x <= 0.0f && viewangles.x >= -89.0f)
		{
			viewangles.x = cmd->viewangles.x - 180.0f;
		}
	}

	adjusted = movenormang + (cmd->viewangles - viewangles);

	AngleVectors((QAngle&)adjusted, &dir);

	set = dir * len;

	if ((cmd->viewangles.x > 89.0f) || (cmd->viewangles.x < -89.0f))
		cmd->forwardmove = set.x;
	else if ((cmd->viewangles.x == 89.0f || cmd->viewangles.x == -89.0f))
		cmd->forwardmove = -set.x;
	else
		cmd->forwardmove = set.x;

	if ((cmd->viewangles.x >= 89.0f) || (cmd->viewangles.x <= -89.0f))
		cmd->sidemove = -set.y;
	else
		cmd->sidemove = set.y;
}
void ClampAngles(Vector &angles)
{
	if (angles.x > 89.f)
		angles.x -= 360.f;
	else if (angles.x < -89.f)
		angles.x += 360.f;
	if (angles.y > 180.f)
		angles.y -= 360.f;
	else if (angles.y < -180.f)
		angles.y += 360.f;

	angles.z = 0;
}
C_RandomA *randoma = new C_RandomA();
void CCreateMove::X_SpreadFix(CUserCmd* pCmd)
{
	Vector vecForward, vecRight, vecUp, vecAntiDir;
	float flSpread, flInaccuracy, flSpreadX, flSpreadY;

	Vector qAntiSpread;
	Normalize(pCmd->viewangles);

	// My player
		CBaseEntityNew* me = (CBaseEntityNew*)ClientEntList->GetClientEntity(Engine->GetLocalPlayer());
		if (!me || !me->isAlive())
			return;
	CBaseCombatWeaponNew* pWeapon = (CBaseCombatWeaponNew*)me->GetWeapon();
	if (!pWeapon)
		return;
	// Get the up to date weapon information
	pWeapon->UpdateAccuracyPenalty();
	flSpread = pWeapon->GetSpread();
	flInaccuracy = pWeapon->GetInaccuracy();

	// Set the Seed up for the spread
//	pCmd->random_seed = MD5_PseudoRandom(pCmd->command_number) & 0x7FFFFFFF;
	randoma->SetSeed((pCmd->random_seed & 0xFF) + 1);

	// Generate the "random" spread values
	float flRandPi_1 = randoma->RandomFloat(0.0f, 2.0f * M_PI);
	float flRandInaccuracy = randoma->RandomFloat(0.0f, flInaccuracy);
	float flRandPi_2 = randoma->RandomFloat(0.0f, 2.0f * M_PI);
	float flRandSpread = randoma->RandomFloat(0, flSpread);

	// Calculate the spread X, Y Values
	flSpreadX = cos(flRandPi_1) * flRandInaccuracy + cos(flRandPi_2) * flRandSpread;
	flSpreadY = sin(flRandPi_1) * flRandInaccuracy + sin(flRandPi_2) * flRandSpread;

	// Convert them to the new view angles
	AngleVectors((QAngle&)pCmd->viewangles, &vecForward, &vecRight, &vecUp);
	vecAntiDir = vecForward + (vecRight * -flSpreadX) + (vecUp * -flSpreadY);
	vecAntiDir.NormalizeInPlace();
	VectorAngles(&vecAntiDir, &qAntiSpread);
	// Set the view Angles
	pCmd->viewangles = qAntiSpread;
	Normalize(pCmd->viewangles);
}
void SmoothSpinbot(CUserCmd* _pCommand)
{


	if (_pCommand->buttons & IN_ATTACK)
		return;
	float fTime = Engine->Time();
	_pCommand->viewangles.y = (vec_t)(fmod(fTime / 0.4f * 360.0f, 360.0f));
	ClampAngles(_pCommand->viewangles);
}
void Triggerbot(CUserCmd* cmd, CBaseEntityNew* me)
{
	Ray_t ray;
	trace_t trace;
	Vector mpos, mang;
	Engine->GetViewAngles(mang);
	mpos = me->GetEyePosition();
	Vector forward;
	AngleVectorsZ((const Vector&)cmd->viewangles, &forward);
	forward = forward * 8192.f + mpos;
	ray.Init(mpos, forward);
	CTraceFilter filter;
	filter.pSkip1 = me;
	Trace->TraceRay(ray, MASK_SHOT, &filter, &trace);
	if (!trace.m_pEnt)
		return;
	CBaseEntityNew* target = (CBaseEntityNew*)trace.m_pEnt;
	if (!target)
		return;
	if (!target->isAlive())
		return;
	if (target->IsDormant())
		return;
	
	player_info_t info;
	if (!Engine->GetPlayerInfo(target->GetIndex(), &info))
		return;
	if (target->GetTeamNum() == me->GetTeamNum())
		return;
	cmd->buttons |= IN_ATTACK;

}
void CCreateMove::Invoke(CUserCmd* cmd , BYTE &bSendPacket)
{
	//static void* glowp;
	//if (glowp == NULL)
	//	find_glowp((void*)GetModuleHandle("client.dll"),0x4C56000);
	ChikenGlow();
	if (gCvars.fakelag)
		gAimbot.FakeLag(bSendPacket);
	CBaseEntityNew* me = (CBaseEntityNew*)ClientEntList->GetClientEntity(Engine->GetLocalPlayer());
	if (!me)
		return;
	//m_hActiveWeapon_______________________________ -> 0x12c0
	//__m_iName_____________________________________ -> 0x0150
	//int name = *reinterpret_cast<int*>(me + 0x12c0 + 0x150);
	//cout << name << endl;
	if (gCvars.radar)
	{
		for (int i = 0; i < 32; i++)
		{
			CBaseEntityNew* target = (CBaseEntityNew*)ClientEntList->GetClientEntity(i);
			if (!target)
				continue;
			if (target->isAlive() && !target->IsDormant() && target->GetTeamNum() != me->GetTeamNum())
			{
				int* spotted = (int*)((DWORD)target + 0x935);
				if (*spotted != 1)
					*spotted = 1;
			}
		}
	}
	Vector organg = cmd->viewangles;
	int flags = me->GetFlags();
	if (gCvars.aimassist)
		gAimbot.DoAimbot(cmd, me, bSendPacket);
	if (gCvars.triggerbot)
		Triggerbot(cmd, me);
	if (gCvars.bhop)
	{
		if (gCvars.bhop_strafe)
		{
			if (!(flags & FL_ONGROUND))
			{
				if (cmd->mousedx < 0)
					cmd->sidemove = -450.f;
				if (cmd->mousedx > 0)
					cmd->sidemove = 450.f;
			}
		}
		static bool bLastJumped = false;
		static bool bShouldFake = false;

		if (!bLastJumped && bShouldFake)
		{
			bShouldFake = false;
			cmd->buttons |= IN_JUMP;
		}
		else if (cmd->buttons & IN_JUMP)
		{
			if (flags & FL_ONGROUND)
			{
				bLastJumped = true;
				bShouldFake = true;
			}
			else
			{
				cmd->buttons &= ~IN_JUMP;
				bLastJumped = false;
			}
		}
		else
		{
			bLastJumped = false;
			bShouldFake = false;
		}
	}
	if (cmd->buttons & IN_ATTACK)
	{
		static bool bAttack = false;
		if (bAttack)
			cmd->buttons |= IN_ATTACK;
		else
			cmd->buttons &= ~IN_ATTACK;
		bAttack = !bAttack;
	}

	if (gCvars.rcs)
		cmd->viewangles -= (me->GetPunch() * 2.f);

	if (gCvars.nospread && cmd->buttons & IN_ATTACK)
		X_SpreadFix(cmd);

	ClampAngles(cmd->viewangles);
	if (!(cmd->buttons & IN_ATTACK))
	{
		/*AA HERE*/
		if (gCvars.spinbot)
			SmoothSpinbot(cmd);
		if (gCvars.fakeangle)
			cmd->viewangles.x = -181;
		static bool switcheroni = false;
		if (gCvars.fakeside)
		{
			Vector view;
			Engine->GetViewAngles(view);
			if (switcheroni)
			{
				bSendPacket = 0;
				cmd->viewangles.x = -181;
				cmd->viewangles.y = view.y + 90.f;
				//cmd->buttons |= IN_DUCK;
			}
			else
			{
				bSendPacket = 1;
				cmd->viewangles.x = 181;
				cmd->viewangles.y = view.y - 90.f;
				//cmd->buttons &= ~IN_DUCK;
			}
			switcheroni = !switcheroni;
		}
	}
	CL_FixMove(cmd, organg);
}
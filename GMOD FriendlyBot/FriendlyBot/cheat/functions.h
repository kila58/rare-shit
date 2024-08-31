bool IsAlive(CBaseEntity* Player)
{
	int Health = *(int*)((DWORD)Player + 0x90);
	return Health > 0;
}

int GetPlayerTeam(CBaseEntity* Player)
{
	return *(int*)((DWORD)Player + 0x9C);
}

inline QAngle AngleNormalize(QAngle Angle)
{

	Angle.x = fmodf(Angle.x, 360.0f);
	if (Angle.x > 180)
		Angle.x -= 360;
	if (Angle.x < -180)
		Angle.x += 360;

	Angle.y = fmodf(Angle.y, 360.0f);
	if (Angle.y > 180)
		Angle.y -= 360;
	if (Angle.y < -180)
		Angle.y += 360;

	Angle.z = fmodf(Angle.z, 360.0f);
	if (Angle.z > 180)
		Angle.z -= 360;
	if (Angle.z < -180)
		Angle.z += 360;

	return Angle;
}

inline bool GetHitboxPosition(int HitBox, Vector& Origin, int Index, QAngle& Angles)
{
	if (HitBox < 0 || HitBox >= 20)
		return false;
	matrix3x4_t pmatrix[128];

	IClientEntity* Entity = InterfaceManager.ClientEntList->GetClientEntity(Index);
	if (!Entity)
		return false;
	if (Entity->IsDormant())
		return false;
	const model_t* Model = Entity->GetModel();
	if (!Model)
		return false;
	studiohdr_t *pStudioHdr = InterfaceManager.ModelInfo->GetStudiomodel(Model);
	if (!pStudioHdr)
		return false;
	if (!Entity->SetupBones(pmatrix, 128, BONE_USED_BY_HITBOX, 0))
		return false;
	mstudiohitboxset_t *set = pStudioHdr->pHitboxSet(0);
	if (!set)
		return false;
	mstudiobbox_t* pBox = NULL;
	pBox = pStudioHdr->pHitbox(HitBox, NULL);
	Vector min, max;
	MatrixAngles(pmatrix[pBox->bone], Angles, Origin);
	VectorTransform(pBox->bbmin, pmatrix[pBox->bone], min);
	VectorTransform(pBox->bbmax, pmatrix[pBox->bone], max);
	Origin = (min + max) * 0.5f;

	return true;
}


inline Vector GetEyePos(CBaseEntity* Player)
{
	Vector vecViewOffset;

	QAngle ang;
	if (!GetHitboxPosition(0, vecViewOffset, Player->index, ang))
		return Player->GetAbsOrigin() + Vector(0, 0, 32);

	return vecViewOffset;

}

inline Vector GetShootPos()
{
	CBaseEntity* LocalPlayer = (CBaseEntity*)InterfaceManager.ClientEntList->GetClientEntity(InterfaceManager.Engine->GetLocalPlayer());
	Vector ShootPos = LocalPlayer->GetAbsOrigin() + Vector(0, 0, 64);

	return ShootPos;
}

inline bool IsVisible(CBaseEntity* Target)
{

	trace_t tr;
	Ray_t ray;

	CBaseEntity* LocalPlayer = (CBaseEntity*)InterfaceManager.ClientEntList->GetClientEntity(InterfaceManager.Engine->GetLocalPlayer());

	Vector selfPos = GetShootPos();

	Vector vE = GetEyePos(Target);

	ray.Init(selfPos, vE);
	InterfaceManager.EngineTrace->TraceRay(ray, MASK_SHOT, 0, &tr);

	if (tr.fraction > 1.0)
		return true;

	player_info_s pinfo;

	if (tr.m_pEnt && Target)
	{
		if (tr.m_pEnt->index == 0 || tr.allsolid)
			return false;

		if ((InterfaceManager.Engine->GetPlayerInfo(tr.m_pEnt->index, &pinfo)
			|| Target->index == tr.m_pEnt->index) && tr.fraction != 1.0)
			return true;
	}
	return false;

}
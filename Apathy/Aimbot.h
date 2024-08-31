#include "client.h"

bool Insight(Entity* ply, vec3 pos)
{
	RayData ray;
	ray.base = cl.shootpos;
	ray.delta = pos - cl.shootpos;
	ray.isray = true;
	ray.hasdelta = true;
	TraceFilter filter;
	filter.local = cl.me;
	filter.ignore = ply;
	TraceResult tr;
	cl.trace->TraceRay(&tr, ray, &filter);
	return tr.fraction == 1;
}

HitBBox* GetHitbox(Entity* ply)
{
	void* mdl = ply->GetModel();
	if (!mdl)
		return 0; // you never know in gay's mod
	StudioHDR* hdr = cl.mdl->GetStudioModel(mdl);
	if (!hdr)
		return 0;
	const char* name = cl.mdl->GetModelName(mdl);
	int index = name[14] == 'c' ? 1 : 0;
	return hdr->GetHitbox(index);
}

bool GetPosition(Entity* ply, vec3& pos)
{
	matrix3x4 matrix[128];
	if (!ply->SetupBones(matrix))
		return false;
	HitBBox* box = GetHitbox(ply);
	vec3 min = box->min;
	vec3 max = box->max;
	matrix3x4& mtx = matrix[box->bone];
	vec3 a = vec3(mtx[0][0], mtx[0][1], mtx[0][2]);
	vec3 b = vec3(mtx[1][0], mtx[1][1], mtx[1][2]);
	vec3 c = vec3(mtx[2][0], mtx[2][1], mtx[2][2]);
	min = vec3(min.Dot(a) + mtx[0][3], min.Dot(b) + mtx[1][3], min.Dot(c) + mtx[2][3]);
	max = vec3(max.Dot(a) + mtx[0][3], max.Dot(b) + mtx[1][3], max.Dot(c) + mtx[2][3]);
	pos = (min + max) * 0.5;
	return Insight(ply, pos);
}

bool ValidTarget(Entity* ply)
{
	//if (ply->Team() == cl.team)
	//eturn false;
	if (!ply->Alive())
		return false;
	//if (ply->IsDormant())
	//return false;
	return true;
}

void DoMain(UserCmd* cmd)
{
	if (!cl.wep || !(cmd->buttons & 16384))
		return;
	Entity* ply;
	vec3 ang = cmd->ang;
	vec3 pos, dt;
	int max = cl.engine->GetMaxClients();
	vec3 valid[16];
	int index = 0;
	float fov = 0;
	for (int i = 1; i <= max; i++)
	{
		if (index == 15)
			break;
		if (i == cl.local)
			continue;
		ply = cl.ents->GetEntity(i);
		if (!ply)
			continue;
		if (!ValidTarget(ply))
			continue;
		if (!GetPosition(ply, pos))
			continue;
		dt = (pos - cl.shootpos).Angle();
		dt.Clamp();
		dt = ang - dt;
		fov = sqrtf(dt.x*dt.x + dt.y*dt.y);
		//if (fov > nigger)
		//continue;
		valid[++index] = pos;
	}
	if (!index)
		return;
	cmd->ang = (valid[max(cl.wep->Ammo() % index, 1)] - cl.shootpos).Angle();
	cmd->move = (cmd->move.Normal().Angle() + (vec3(0, cmd->ang.y) - ang)).Forward() * cmd->move.Length();
	cmd->buttons |= 1;
}
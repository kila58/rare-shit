#include "hooks.h"
#include "Aimbot.h"
#include "speed.h"
#include "Bhop.h"

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
	if (!variables::Aimbot::TargetTeammates && ply->m_iTeamNum() == cl.me->m_iTeamNum())
		return false;
	if (!ply->Alive())
		return false;
	if (ply->IsDormant())
		return false;
	return true;
}

void DoMain(UserCmd* cmd)
{
	if (!cl.wep || !variables::Aimbot::Active || !GetAsyncKeyState('F'))
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
		valid[++index] = pos;
	}

	if (!index)
		return;

	cmd->ang = (valid[max(cl.wep->Ammo() % index, 1)] - cl.shootpos).Angle();
	cmd->move = (cmd->move.Normal().Angle() + (vec3(0, cmd->ang.y) - ang)).Forward() * cmd->move.Length();

	cmd->buttons |= 1;

	if (!variables::Aimbot::Silent)
		cl.engine->SetViewAngles(cmd->ang);
}

GetContentsFn GetContents;
PaintTraverseFn PaintTraverse;

#include "md5.h"

float spread[64];

void Niger(UserCmd* cmd)
{
	if (!cl.wep || !variables::Removals::Seed)
		return;

	RandomSeed(MD5_PseudoRandom(cmd->index) & 255);

	float x = RandomFloat(-0.5, 0.5) + RandomFloat(-0.5, 0.5);
	float y = RandomFloat(-0.5, 0.5) + RandomFloat(-0.5, 0.5);

	x *= spread[cl.wep->GetIndex() % 64];
	y *= spread[cl.wep->GetIndex() % 64];

	cmd->ang += vec3(1, x, -y).Angle();
}

bool HookedCreateMove(float frametime, UserCmd* cmd)
{
	cl.local = cl.engine->GetLocalPlayer();
	cl.me = cl.ents->GetEntity(cl.local);
	cl.wep = cl.ents->GetEntity(cl.me->Weapon(), true);
	void* baseptr;
	_asm MOV baseptr, EBP;
	baseptr = ***(void****)baseptr;
	CL_Speed(baseptr);
	cl.shootpos = cl.me->LocalOrigin() + cl.me->ViewOffset();
	DoMain(cmd);
	Bhop(cmd);
	Niger(cmd);
	cmd->ang.Clamp();
	return false;
}

int HookedGetContents(vec3& pos, void* ent)
{
	void** baseptr;
	_asm mov baseptr, ebp;

	if (cl.wep && (dword)baseptr[1] == cl.clientbase + 0x100B6B)
	{
		//Msg("%X\n", (dword)baseptr[1] - cl.clientbase);

		//if (false)
		{
			float spr = *(float*)(*(dword*)baseptr - 0x7C);
			int index = cl.wep->GetIndex() % 64;

			if (spread[index] != spr)
				spread[index] = spr;
		}
	}

	return GetContents(cl.trace, pos, ent);
}
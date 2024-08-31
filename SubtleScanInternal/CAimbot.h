#pragma once
#include "Main.h"
#include "gametrace.h"
class CAimbot
{
public:
	/*struct FireBulletData
	{
		FireBulletData(const Vector &eye_pos)
		: src(eye_pos)
		{
		}

		Vector           src;
		trace_t          enter_trace;
		Vector           direction;
		CTraceFilter    filter;
		float           trace_length;
		float           trace_length_remaining;
		float           current_damage;
		int             penetrate_count;
	};
	void ScaleDamage(int hitgroup, CBaseEntityNew* enemy, float weapon_armor_ratio, float &current_damage)
	{
		current_damage *= GetHitgroupDamageMult(hitgroup);

		if (enemy->m_ArmorValue() > 0)
		{
			if (hitgroup == HITGROUP_HEAD)
			{
				if (enemy->m_bHasHelmet())
					current_damage *= (weapon_armor_ratio * .5f);
			}
			else
			{
				current_damage *= (weapon_armor_ratio * .5f);
			}
		}
	}

	bool SimulateFireBullet(CBaseEntityNew *local, CBaseCombatWeapon *weapon, FireBulletData &data)
	{
		data.penetrate_count = 4;
		data.trace_length = 0.0f;
		FileWeaponInfo_t wpn_data = weapon->GetWpnData();

		data.current_damage = (float)wpn_data.damage();

		while ((data.penetrate_count > 0) && (data.current_damage >= 1.0f))
		{
			data.trace_length_remaining = 8192.f - data.trace_length;

			Vector end = data.src + data.direction * data.trace_length_remaining;
			Ray_t ray;
			ray.Init(data.src, end);
			Trace->TraceRay(ray, 0x4600400B, NULL, &data.enter_trace);
			UTIL_ClipTraceToPlayers(data.src, end + data.direction * 40.f, 0x4600400B, &data.filter, &data.enter_trace);

			if (data.enter_trace.fraction == 1.0f)
				break;

			if ((data.enter_trace.hitgroup <= 7)
				&& (data.enter_trace.hitgroup > 0)
				&& (local->GetTeamNum() != data.enter_trace.m_pEnt->m_iTeamNum)
				&& (DoesRayTouchHitbox(end, &data)))
			{
				data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
				data.current_damage *= pow(wpn_data.range_modifier(), data.trace_length * 0.002);
				ScaleDamage(data.enter_trace.hitgroup, (CBaseEntityNew*)data.enter_trace.m_pEnt, wpn_data.armor_ratio(), data.current_damage);

				return true;
			}


			if (!HandleBulletPenetration(wpn_data, data))
				break;
		}

		return false;
	}

	bool TraceToExit(Vector &end, trace_t *enter_trace, Vector start, Vector dir, trace_t *exit_trace)
	{
		float distance = 0.0f;

		while (distance <= 90.0f)
		{
			distance += 4.0f;
			end = start + dir * distance;

			auto point_contents = Trace->GetPointContents(end, (IHandleEntity**)exit_trace->m_pEnt);

			if (point_contents & MASK_SHOT_HULL && (!(point_contents & CONTENTS_HITBOX)))
				continue;

			auto new_end = end - (dir * 4.0f);
			Ray_t ray;
			ray.Init(end, new_end);
			Trace->TraceRay(ray, 0x4600400B, 0, exit_trace);

			// bool allsolid; @ TR + 54 
			// bool startsolid; @ TR + 55 

			if (exit_trace->startsolid && exit_trace->surface.flags & SURF_HITBOX)
			{
				Ray_t ray2;
				ray2.Init(end, start);
				CTraceFilter filter;
				filter.pSkip1 = exit_trace->m_pEnt;
				Trace->TraceRay(ray2, 0x600400B, &filter, exit_trace);

				if ((exit_trace->fraction < 1.0f || exit_trace->allsolid) && !exit_trace->startsolid)
				{
					end = exit_trace->endpos;
					return true;
				}
				continue;
			}

			if (!(exit_trace->fraction < 1.0 || exit_trace->allsolid || exit_trace->startsolid) || exit_trace->startsolid)
			{
				if (exit_trace->m_pEnt)
				{
					if (enter_trace->DidHitNonWorldEntity() && IsBreakableEntity(enter_trace->m_pEnt))
						return true;
				}
				continue;
			}

			// checking for SURF_NODRAW perhaps 
			if (((exit_trace->surface.flags >> 7) & 1) && !((enter_trace->surface.flags >> 7) & 1))
				continue;

			if (exit_trace->plane.normal.Dot(dir) <= 1.0f)
			{
				auto fraction = exit_trace->fraction * 4.0f;
				end = end - (dir * fraction);
				return true;
			}
		}
		return false;
	}

	bool HandleBulletPenetration(FileWeaponInfo_t wpn_data, FireBulletData &data)
	{

		surfacedata_t *enter_surface_data = physprops->GetSurfaceData(data.enter_trace.surface.surfaceProps);
		int enter_material = enter_surface_data->game.material;
		float enter_surf_penetration_mod = enter_surface_data->game.penetration_modifier;

		data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
		data.current_damage *= pow(wpn_data.range_modifier(), (data.trace_length * 0.002));

		if ((data.trace_length > 3000.f) || (enter_surf_penetration_mod < 0.1f))
			data.penetrate_count = 0;

		if (data.penetrate_count <= 0)
			return false;

		Vector dummy;
		trace_t trace_exit;
		if (!TraceToExit(dummy, &data.enter_trace, data.enter_trace.endpos, data.direction, &trace_exit))
			return false;

		surfacedata_t *exit_surface_data = physprops->GetSurfaceData(trace_exit.surface.surfaceProps);
		int exit_material = exit_surface_data->game.material;

		float exit_surf_penetration_mod = exit_surface_data->game.penetration_modifier;
		float final_damage_modifier = 0.16f;
		float combined_penetration_modifier = 0.0f;

		if (((data.enter_trace.contents & CONTENTS_GRATE) != 0) || (enter_material == 89) || (enter_material == 71))
		{
			combined_penetration_modifier = 3.0f;
			final_damage_modifier = 0.05f;
		}
		else
		{
			combined_penetration_modifier = (enter_surf_penetration_mod + exit_surf_penetration_mod) * 0.5f;
		}

		if (enter_material == exit_material)
		{
			if (exit_material == 87 || exit_material == 85)
				combined_penetration_modifier = 3.0f;
			else if (exit_material == 76)
				combined_penetration_modifier = 2.0f;
		}

		float v34 = fmaxf(0.f, 1.0f / combined_penetration_modifier);
		float v35 = (data.current_damage * final_damage_modifier) + v34 * 3.0f * fmaxf(0.0f, (3.0f / wpn_data.penetration()) * 1.25f);
		float thickness = VectorLength(trace_exit.endpos - data.enter_trace.endpos);

		thickness *= thickness;
		thickness *= v34;
		thickness /= 24.0f;

		float lost_damage = fmaxf(0.0f, v35 + thickness);

		if (lost_damage > data.current_damage)
			return false;

		if (lost_damage >= 0.0f)
			data.current_damage -= lost_damage;

		if (data.current_damage < 1.0f)
			return false;

		data.src = trace_exit.endpos;
		data.penetrate_count--;

		return true;
	}


	/*
	*    CanHit() - example of how to use the code
	*     @in  point: target hitbox vector
	*     @out damage_given: amount of damage the shot would do
	*
	bool CanHit(Vector &point, float *damage_given)
	{
		CBaseEntityNew *local = (CBaseEntityNew*)ClientEntList->GetClientEntity(Engine->GetLocalPlayer());
		auto data = FireBulletData(local->GetEyePosition());
		CTraceFilter filter;
		filter.pSkip1 = local;
		data.filter = filter;


		Vector angles;
		CalcAngle(data.src, point, angles);
		AngleVectors((QAngle&)angles, &data.direction);
		VectorNormalize(data.direction);

		if (SimulateFireBullet(local, local->GetWeapon(), data))
		{
			*damage_given = data.current_damage;

			return true;
		}

		return false;
	}*/
	inline bool GetHitboxPosition(int HitBox, Vector& Origin, int Index);
	void ClampAngles(Vector &angles)
	{
		if (angles.x > 180.f)
			angles.x -= 360.f;
		else if (angles.x < -180.f)
			angles.x += 360.f;
		if (angles.y > 180.f)
			angles.y -= 360.f;
		else if (angles.y < -180.f)
			angles.y += 360.f;

		angles.z = 0;
	}
	void FakeLag(byte& sendPacket)
	{
		static int choked = 0;
		if (choked >= 0)
		{
			choked++;
			if (choked < 2)
				sendPacket = 1;
			else
				sendPacket = 0;

		}

		if (choked >= 15)
			choked = 0;
	}
	void CalcAngle(Vector &src, Vector &dst, Vector &angles)
	{
		double delta[3] = { (src[0] - dst[0]), (src[1] - dst[1]), (src[2] - dst[2]) };
		double hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);

		angles[0] = (float)(atan(delta[2] / hyp) * M_RADPI);
		angles[1] = (float)(atan(delta[1] / delta[0]) * M_RADPI);
		angles[2] = 0.0f;

		if (delta[0] >= 0.0) { angles[1] += 180.0f; }
		/*RCS*/
		CBaseEntityNew *me = (CBaseEntityNew*)ClientEntList->GetClientEntity(Engine->GetLocalPlayer());
		Vector punch = me->GetPunch();
		if (gCvars.aimbot_rcs)
			angles -= punch * 2.f;
		angles.z = 0.f;

	}
	bool GetBonePosition(CBaseEntityNew* pPlayer, Vector& Hitbox, int Bone)
	{
		matrix3x4_t MatrixArray[128];

		if (!pPlayer->SetupBones(MatrixArray, 128, BONE_USED_BY_HITBOX, 0))
			return false;

		Hitbox = Vector(MatrixArray[Bone][0][3], MatrixArray[Bone][1][3], MatrixArray[Bone][2][3]);

		return true;
		/*if (Bone < 0 || Bone >= 20)
			return false;
		matrix3x4_t matrix[128];
		if (!pPlayer)
			return false;
		IClientEntity* player = (IClientEntity*)pPlayer;
		if (!player)
			return false;
		const model_t* model = pPlayer->GetModel();
		if (!model)
			return false;
		studiohdr_t *hdr = ModelInfo->GetStudiomodel(model);
		if (!hdr)
			return false;
		if (!pPlayer->SetupBones(matrix, 128, 0x100, 0))
			return false;
		mstudiohitboxset_t *set = hdr->pHitboxSet(0);
		if (!set)
			return false;
		mstudiobbox_t* box = NULL;
		box = hdr->pHitbox(Bone, 0);
		if (!box)
			return false;
		Vector min, max;
		Vector angles;
		MatrixAngles(matrix[128], (QAngle&)angles, Hitbox);
		VectorTransform(box->bbmin, matrix[box->bone], min);
		VectorTransform(box->bbmax, matrix[box->bone], max);
		Hitbox = (min + max) * .5f;

		return true;*/

	}
	void SmoothAngleSet(Vector &dest, Vector &orig, CUserCmd* cmd)
	{
		Vector SmoothAngles;
		SmoothAngles.x = dest.x - orig.x;
		SmoothAngles.y = dest.y - orig.y;
		SmoothAngles.z = 0.f;
		ClampAngles(SmoothAngles);
		SmoothAngles.x = orig.x + SmoothAngles.x / 100.f * gCvars.smoothamount;
		SmoothAngles.y = orig.y + SmoothAngles.y / 100.f * gCvars.smoothamount;
		SmoothAngles.z = 0.f;
		ClampAngles(SmoothAngles);
		cmd->viewangles = SmoothAngles;
		Engine->SetViewAngles(cmd->viewangles);
	}
	void VelocityComp(Vector &pos, CBaseEntityNew* me, CBaseEntityNew* target)
	{
		Vector evel;
		Vector mvel;
		mvel = me->GetVelocity();
		evel = target->GetVelocity();
		pos = pos + (evel / 100.f) * (40.f / gCvars.smoothamount);
		pos = pos - (mvel / 100.f) * (40.f / gCvars.smoothamount);
	}
	bool ScreenPosition2(Vector& screen, Vector& origin)
	{
		typedef bool(__thiscall* oScreenPosition)(void*, Vector&, Vector&);
		return getvfunc<oScreenPosition>(DebugOverlay, 12)(DebugOverlay, screen, origin);
	}
	bool WorldToScreen(Vector &vOrigin, Vector &vScreen)
	{
		return(ScreenPosition2(vOrigin, vScreen) != 1);
	}
	void MakeVector(Vector &angle, Vector &vector)
	{
		float pitch = float(angle[0] * M_PI / 180);
		float yaw = float(angle[1] * M_PI / 180);
		float tmp = float(cos(pitch));
		vector[0] = float(-tmp * -cos(yaw));
		vector[1] = float(sin(yaw)*tmp);
		vector[2] = float(-sin(pitch));
	}
	float FieldOfView(Vector &angles, Vector &source, Vector &dst)
	{
		//Stole this from the internet.
		Vector ang, aim;
		float fov;
		CalcAngle(source, dst, ang);
		MakeVector(angles, aim);
		MakeVector(ang, ang);
		float mag_s = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
		float mag_d = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
		float u_dot_v = aim[0] * ang[0] + aim[1] * ang[1] + aim[2] * ang[2];
		fov = acos(u_dot_v / (mag_s*mag_d)) * M_RADPI;
		return fov;
	}
	bool IsVisible(Vector aimpos, CBaseEntityNew* me)
	{
		Vector eyepos = me->GetEyePosition();
		trace_t trace;
		Ray_t ray;
		CTraceFilter filter;
		filter.pSkip1 = me;
		player_info_t info;
		ray.Init(eyepos, aimpos);
		Trace->TraceRay(ray, MASK_SHOT, &filter, &trace);
		CBaseEntityNew* hit = (CBaseEntityNew*)trace.m_pEnt;
		if (!hit)
			return false;
		if (hit)
		{
			if (trace.allsolid)
				return false;
			if (Engine->GetPlayerInfo(hit->GetIndex(), &info) && me->GetTeamNum() != hit->GetTeamNum())
			{
				return true;
			}
		}
		return false;
	}
	bool IsVisibleAW(Vector aimpos, CBaseEntityNew* me)
	{
		trace_t tr;
		Ray_t ray;
		Vector vStart, vEnd, vEndPos[3];
		vStart = me->GetEyePosition();
		vEnd = aimpos;
		CTraceFilter filter;

		if (this->IsVisible(vEnd,me))
			return true;


		filter.pSkip1 = me;
		ray.Init(vStart, vEnd);

		Trace->TraceRay(ray, MASK_NPCWORLDSTATIC | CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_HITBOX | CONTENTS_GRATE, &filter, &tr);

		vEndPos[0] = tr.endpos;

		ray.Init(vEnd, vStart);
		filter.pSkip1 = me;
		Trace->TraceRay(ray, MASK_NPCWORLDSTATIC | CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_HITBOX | CONTENTS_GRATE, &filter, &tr);

		vEndPos[1] = tr.endpos;

		VectorSubtract(vEndPos[0], vEndPos[1], vEndPos[2]);

		float flLength = VectorLength(vEndPos[2]);

		if (tr.fraction != 0)
		if (flLength < 14)
			return true;

		return false;
	}
	void DoAimbot(CUserCmd* cmd, CBaseEntityNew* me, byte &bSendPacket);

};
extern CAimbot gAimbot;
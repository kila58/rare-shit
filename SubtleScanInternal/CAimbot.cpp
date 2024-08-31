#include "CAimbot.h"
CAimbot gAimbot;
struct TargetList_t
{
	float distance;
	Vector angle;
	TargetList_t()
	{

	}
	TargetList_t(Vector vangle, Vector mpos, Vector epos)
	{
		distance = flGetDistance(mpos, epos);
		angle = vangle;
	}
	float flGetDistance(Vector from, Vector to)
	{
		Vector angle;
		angle.x = to.x - from.x;	angle.y = to.y - from.y;	angle.z = to.z - from.z;

		return sqrt(angle.x*angle.x + angle.y*angle.y + angle.z*angle.z);
	}

};
struct CompareArray
{
	bool operator() (TargetList_t &t1, TargetList_t& t2)
	{
		return t1.distance < t2.distance;
	}
};
//Broken
Vector GetLagCompOffset(CBaseEntityNew* target, CBaseEntityNew* me)
{
	float wishspeed = target->GetMaxSpeed();
	Vector playerspeed = target->GetVelocity();
	Vector wishDir;
	float curspeed = playerspeed.Length();
	float addspeed = wishspeed - curspeed;
	if (addspeed <= 1)
		return Vector(0, 0, 0);
	//ConVar *sv_accelerate = Cvar->FindVar("sv_accelerate");
	INetChannelInfo *netInfo = Engine->GetNetChannelInfo();
	float accelspeed = 5.5f * (netInfo->GetLatency(FLOW_OUTGOING) + netInfo->GetLatency(FLOW_INCOMING)) * wishspeed * *reinterpret_cast<float*>((DWORD)me + 0x140);
	if (accelspeed > addspeed)
		accelspeed = addspeed;
	return wishDir * accelspeed;
}
void CAimbot::DoAimbot(CUserCmd* cmd, CBaseEntityNew* me, BYTE &bSendPacket)
{
	Vector oldView = cmd->viewangles;
	float oldSidemove = cmd->sidemove;
	float oldForwardmove = cmd->forwardmove;
	//nextattack 0x159c
	//activeweapon 0x12c0
	//tickbase 0x17cc
	DWORD weaponh = *reinterpret_cast<DWORD*>((DWORD)me + 0x12c0);
	int index = weaponh & 0xFFF;
	C_BaseCombatWeapon *weapon = (C_BaseCombatWeapon*)ClientEntList->GetClientEntity(index);
	if (!weapon)
		return;
	float flNextAttack = *reinterpret_cast<float*>((DWORD)weapon + 0x159c);
	float flServerTime = (float)*(int*)((DWORD)me + 0x17cc) * Globals->interval_per_tick;
	bool locked = false;
	//For maxentities
	for (int i = 0; i < 32; i++)
	{
		if (locked)
			break;
		//Make it a player
		CBaseEntityNew* target = (CBaseEntityNew*)ClientEntList->GetClientEntity(i);
		if (!target)
			continue;
		if (target->GetIndex() == me->GetIndex())
			continue;
		//Its not null or me so continue
		player_info_t info;
		if (Engine->GetPlayerInfo(i, &info))
		{
			//Its a player
			if (target->isAlive() && !target->IsDormant() && target->GetTeamNum() != me->GetTeamNum())
			{
				Vector mpos, epos, aimangle, mang;
				Engine->GetViewAngles(mang);
				mpos = me->GetEyePosition();
				if (!GetBonePosition(target, epos, 10))
				{
					cout << "Couldn't get bone!\n";
					continue;
				}
				if (FieldOfView(mang, mpos, epos) < gCvars.fov && IsVisibleAW(epos, me))
				{					
					locked = true;
					if (gCvars.smoothamount == 50) //Reversed smooth amount. If not smoothed at all, ragemode.
					{
						//epos += GetLagCompOffset(target, me);
						CalcAngle(mpos, epos, aimangle);
						ClampAngles(aimangle);
						cmd->viewangles = aimangle;
						if (!gCvars.aimbot_silent)
							Engine->SetViewAngles(cmd->viewangles);

						if (gCvars.aimbot_autoshoot && flServerTime > flNextAttack)
							cmd->buttons |= IN_ATTACK;
					}
					else
					{
						VelocityComp(epos, me, target);
						CalcAngle(mpos, epos, aimangle);
						ClampAngles(aimangle);
						SmoothAngleSet(aimangle, cmd->viewangles, cmd);
					}
					bool bBulletTime = true;
					if (flNextAttack > flServerTime)
						bBulletTime = false;

					if (cmd->buttons & IN_ATTACK && bBulletTime) {
						bSendPacket = false;
					}
					else {
						bSendPacket = true;
						cmd->viewangles = oldView;
						cmd->sidemove = oldSidemove;
						cmd->forwardmove = oldForwardmove;
					}
				}

			}
		}
	}

}
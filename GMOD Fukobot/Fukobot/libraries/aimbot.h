class CAimbot{
public:
	void Aimbot(CUserCmd*);
	QAngle FakeView = QAngle(0, 0, 0);
	bool* bSendPacket = NULL;
}; CAimbot Aimbot;

inline void MoveFix(CUserCmd* cmd)
{
	float forward = cmd->forwardmove;
	float side = cmd->sidemove;

	Vector vec = Vector(forward, side, 0);
	float vecLength = vec.Length();
	VectorNormalizeFast(vec);

	QAngle vecAng;
	VectorAngles(vec, vecAng);

	QAngle dirAng = (vecAng)+(cmd->viewangles - Aimbot.FakeView);

	Vector angVec;
	AngleVectors(dirAng, &angVec);

	Vector dir = (angVec)* (vecLength);

	cmd->forwardmove = dir.x;

	if (*Vars->HVH_AA == 1 && cmd->viewangles.x == -181)
		cmd->sidemove = -dir.y;
	else
		cmd->sidemove = dir.y;
}

inline void FakeViewMovement(CUserCmd* cmd)
{

	int MouseX = cmd->mousedx;
	int MouseY = cmd->mousedy;

	Aimbot.FakeView.x = Aimbot.FakeView.x + MouseY*0.01;
	Aimbot.FakeView.y = Aimbot.FakeView.y + (-MouseX)*0.01;

}


/*
void FixAA(CBaseEntity* Target)
{
	float* Pitch = (float*)((DWORD)Target + 0x2BCC);

	if (*Pitch == 90)
		*Pitch = 270;
	else if (*Pitch == -90)
		*Pitch = 90;

}
*/

bool Attacking = false;
inline void Attack(CUserCmd* cmd)
{

	if (Attacking)
		cmd->buttons |= IN_ATTACK;
	
	Attacking = !Attacking;

}

bool noob = false;
int CurrentTarget = 0;
QAngle OrgAngle = QAngle(0,0,0);
bool ShouldRevert = false;
inline void CAimbot::Aimbot(CUserCmd* cmd)
{

	FakeViewMovement(cmd);

	//if (bSendPacket != NULL)
		//*bSendPacket = !*bSendPacket;

	//CBaseEntity* Target = (CBaseEntity*)ClientEntList->GetClientEntity(Engine->GetLocalPlayer());
	//float pitch = *(float*)((DWORD)Target + );
	//Msg("Pitch: %f \n", pitch);

	if (ShouldRevert)
	{
		*bSendPacket = true;
		ShouldRevert = false;
		cmd->viewangles = OrgAngle;
		return;
	}

	OrgAngle = cmd->viewangles;

	if (!ShouldTarget(CurrentTarget))
	{

		for (int i = 0; i < ClientEntList->GetHighestEntityIndex(); i++)
		{

			if (i == Engine->GetLocalPlayer())
				continue;

			if (!ShouldTarget(i))
				continue;

			CurrentTarget = i;

		}
	}

	if (*Vars->AIM_Enabled == 1 && (GetAsyncKeyState(MK_LBUTTON) || *Vars->AIM_AutoFire == 1) && ShouldTarget(CurrentTarget))
	{

		CBaseEntity* Player = (CBaseEntity*)ClientEntList->GetClientEntity(CurrentTarget);
		Vector HeadPos = GetEyePos(Player) - GetShootPos();

		//FixAA(Player);

		QAngle AimAngle;
		VectorAngles(HeadPos, AimAngle);

		if (*Vars->AIM_SilentAim)
		{
			*bSendPacket = false;
			ShouldRevert = true;
		}

		cmd->viewangles = AngleNormalize(AimAngle);

		if (*Vars->AIM_AutoFire)
			Attack(cmd);

	}
	else
	{

		if (*Vars->HVH_AA == 1)
		{
			cmd->viewangles.x = -181;
			cmd->viewangles.y = cmd->viewangles.y + 10;
		}

		else
			cmd->viewangles = FakeView;

			
	}

	MoveFix(cmd);

}
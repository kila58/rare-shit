#include "PaintTraverse.h"
CPaintTraverse gPaintTraverse;
#define DM gDrawManager
//const char *GetClassName(VPANEL vguiPanel)
#define GAMEUNITS_TO_METERS   0.01905
const char *GetClassName(VPANEL vguiPanel)
{
	typedef const char*(__thiscall *OriginalFn)(void*, VPANEL);
	return getvfunc<OriginalFn>(VPanel, 36)(VPanel, vguiPanel);
}
bool Menuv = true;
void checkMenu()
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		gCvars.MenuSwitch = !gCvars.MenuSwitch;
		Engine->ExecuteClientCmd("cl_mouseenable 1");
		Menuv = !Menuv;
	}
	if (!Menuv)
	{
		Engine->ExecuteClientCmd("cl_mouseenable 0");
	}
	if (gCvars.MenuSwitch)
	{
		pMenu.Render(pOptions.Menu_X, pOptions.Menu_Y, 800, 500);
	}
}
Color GetTeamColor(CBaseEntityNew* player)
{
	int teamnum = player->GetTeamNum();
	switch (teamnum){
	case 2: // T
		return Color(247, 143, 63, 255);
		break;
	case 3: // CT
		if (player->IsDefusing())
			return Color(255, 255, 255, 255);
		else
		return Color(81, 140, 202, 255);
		break;
	}
	return Color(255, 255, 255, 255);
}
float flGetDistance(Vector from, Vector to)
{
	Vector angle;
	angle.x = to.x - from.x;	angle.y = to.y - from.y;	angle.z = to.z - from.z;

	return sqrt(angle.x*angle.x + angle.y*angle.y + angle.z*angle.z);
}
static const char *Ranks[] =
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
void DrawESP(int i)
{
	CBaseEntityNew* target = (CBaseEntityNew*)ClientEntList->GetClientEntity(i);
	CBaseEntityNew* me = (CBaseEntityNew*)ClientEntList->GetClientEntity(Engine->GetLocalPlayer());
	if (!me)
		return;
	if (!target)
		return;
	if (me->GetIndex() == target->GetIndex())
		return;
	player_info_t info;
	Vector top, bot;
	if (target->GetTeamNum() == me->GetTeamNum() && !gCvars.esp_team)
		return;
	if (!Engine->GetPlayerInfo(i, &info))
		return;
	if (!target->isAlive() || target->IsDormant())
		return;
	int w, h;
	Vector bone;
	DM.GetBonePosition(target, bone, 10);
	if (gAimbot.IsVisible(bone, me)) // team check in visible check
	{
		Vector pos = target->GetAbsOrigin();
		Vector mins = target->OBBMins();
		Vector maxs = target->OBBMaxs();
		DM.Draw3DBox(pos + mins, pos + maxs, Color(0, 255, 0, 255));
	}
	else
		//DM.DrawPlayerBox(target, GetTeamColor(target), top, bot, w, h);
	{
		Vector pos = target->GetAbsOrigin();
		Vector mins = target->OBBMins();
		Vector maxs = target->OBBMaxs();
		DM.Draw3DBox(pos + mins, pos + maxs, GetTeamColor(target));
	}
	Vector vMon, vNom;

	vNom = target->GetAbsOrigin();

	vMon = vNom + Vector(0, 0, 70.f);
	if (target->GetFlags() & IN_DUCK)
		vMon = vNom + Vector(0, 0, 60.f);
	if (DM.WorldToScreen(vNom, bot) && DM.WorldToScreen(vMon, top))
	{
		h = (bot.y - top.y);
		w = h / 4.f;
		if (target->GetFlags() & IN_DUCK)
			w = h / 3.f;
	}

	if (gCvars.esp_name)
	{
		if (!target->HasDefuser())
			DM.DrawString(false, false, bot.x - w, top.y, GetTeamColor(target), info.name);
		else
		{
			DM.DrawString(false, false, bot.x - w, top.y, GetTeamColor(target), "%s [D]",info.name);
		}

	}
	if (gCvars.esp_healthbar)
		DM.DrawHealthBar(top.x, bot.y, w * 2, 5, target->GetHP());
	int y = bot.y;
	if (gCvars.esp_healthbar)
		y += 6;
	float red = 255 - (target->GetHP()*2.55);
	float green = target->GetHP()*2.55;
	Vector thing,thing2;
	DM.GetBonePosition(target, thing, 10);
	if (DM.WorldToScreen(thing, thing2))
		DM.DrawString(false, false, thing2.x, thing2.y, Color(255, 255, 255, 255), "x HEAD");
	if (gCvars.esp_health)
	{
		DM.DrawString(false, false, bot.x - w, y, Color(red, green, 0, 255), "HP: %i", target->GetHP());
		y += 18;/*HUD_HEIGHT*/
	}
	if (gCvars.esp_distance)
	{
		DM.DrawString(false, false, bot.x - w, y, GetTeamColor(target), "%fm",floor(flGetDistance(me->GetAbsOrigin(),target->GetAbsOrigin())) + 0.5);
		y += 18;
	}
	//DM.DrawString(false, false, bot.x - w, y, Color(255,255,255,255), "%s | %i",Ranks[target->GetRank()],target->GetWins()); //Broken - draws - | 0
	y += 18;

	static BYTE iBoneLegL[] = { 1, 26, 27, 28, 40 };
	static BYTE iBoneLegR[] = { 1, 23, 24, 25, 39 };

	static BYTE iBoneBody[] = { 1, 3, 4, 5, 10 };

	static BYTE iBoneArmL[] = { 5, 7, 8, 9, 20 };
	static BYTE iBoneArmR[] = { 5, 13, 14, 15, 29 };
	if (gCvars.esp_bone)
	{

		for (int i = 0; i < 4; i++)
		{
			DM.DrawBone(iBoneBody[i], iBoneBody[i + 1], target, Color(255, 255, 255, 255));
		}

		for (int i = 0; i < 3; i++)
		{
			DM.DrawBone(iBoneLegL[i], iBoneLegL[i + 1], target, Color(255, 255, 255, 255));
			DM.DrawBone(iBoneLegR[i], iBoneLegR[i + 1], target, Color(255, 255, 255, 255));

			DM.DrawBone(iBoneArmL[i], iBoneArmL[i + 1], target, Color(255, 255, 255, 255));
			DM.DrawBone(iBoneArmR[i], iBoneArmR[i + 1], target, Color(255, 255, 255, 255));
		}
	}
}
void CPaintTraverse::Invoke(unsigned int panel)
{
	static unsigned int mSTP;
	if (mSTP == NULL)
	{
		const char* pszPanel = GetClassName(panel);
		if (pszPanel[0] == 'M' && pszPanel[9] == 'T')
		{
			cout << "FOUND PANEL!\n";
			mSTP = panel;
		}
	}
	if (panel == mSTP)
	{
		DM.DrawString(false, true, 2, 2, Color(255, 0, 200, 200), "pHook V1.2");
		checkMenu(); // Xenshi menu
		//g_pCVarConsole->HandleInput();
		//g_pCVarConsole->Render();
		if (gCvars.esp_fov)
		{
			DM.DrawCircle(DM.gScreenWidth / 2, DM.gScreenHeight / 2, (gCvars.fov / 2) * (gCvars.fov / 2), colYellow);
		}
		if (gCvars.esp)
		{
			for (int i = 0; i < 32; i++)
			{
				DrawESP(i);
			}

		}

	}
}
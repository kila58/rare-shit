#include "dll.h"

/*
	tec9 = 7
	glock = 9
	elite = 7
	five = 9
	p250 = 9
	p2000 = 10
	sil = 10
	deag = 14
	awp = 93
	scout = 79
	*/

bool CreateMove(float time,UserCmd* cmd)
{
	if (!cmd->index)
		return true;

	if (cmd->buttons & 32768)
		game->Speedhack();

	local = client->GetEntity(engine->GetLocalPlayer());

	if (!local)
		return true;

	weapon = client->GetEntity(local->GetActiveWeapon(),true);

	game->cmd = cmd;
	game->viewangles = cmd->ang;

	game->Autohop();

	game->SimulatePrediction();

	aimbot->Think(cmd);

	//prediction->Think(cmd);

	game->SimulateFireBullets();

	game->Think();

	client->CreateMove(time,cmd);

	return false;
}

bool InPrediction()
{
	void** baseptr;
	_asm mov baseptr,ebp;

	static long lastadr = 0;

	if (cvars->misc_noeffects && local && ((long)baseptr[1] - lastadr) == 0xDF)
	{
		Vector& angles = **(Vector**)(*(long*)baseptr + 12);

		Vector punch = local->GetAimPunch();
		punch *= 0.9;

		angles -= punch;
		angles -= local->GetViewPunch();
		angles.z = 0;

		return true;
	}

	lastadr = (long)baseptr[1];

	return *(bool*)((long)client->prediction + 8);
}

void RunCommand(Entity* player,UserCmd* cmd,void* helper)
{
	client->movehelper = (long*)helper;

	client->RunCommand(player,cmd,helper);
}

bool KeyEvent(void* evt)
{
	int type = *(int*)((long)evt);
	int key = *(int*)((long)evt + 8);

	if (type == 0 || type == 2)
	{
		if (gui->InputThink(key))
			return true;
	}

	return vgui->KeyEvent(evt);
}

void PaintTraverse(int index,bool repaint,bool force)
{
	vgui->PaintTraverse(index,repaint,force);

	char* name = vgui->GetPanelName(index);

	if (name[0] != 'F' || name[5] != 'O')
		return;

	static int call = 0;

	++call;

	if (call % 2)
		return;

	static int menufont = 0,espfont = 0;

	if (!menufont)
		menufont = vgui->CreateFont("System",11,800,0x200);

	if (!espfont)
		espfont = vgui->CreateFont("Verdana",12,800,0x200);

	engine->GetScreenSize(game->scrw,game->scrh);

	vgui->SetFont(5);

	vgui->SetTextColor(255,255,255);

	gui->DrawMenu();

	vgui->SetFont(espfont);

	esp->EntThink();
	
	esp->Think();
}

void DrawModel(void* context,void* state,RenderInfo* info,void* mtx)
{
	engine->context = context;

	engine->DrawModel(context,state,info,mtx);
}

void SceneEnd()
{
	engine->SceneEnd();

	glow->Think();
}
#include "hooks.h"
#include "Sigscan.h"
#include "Menu.h"

bool __cdecl worldToScreen(vec3 vecInput, vec3& vecOutput)
{
	vecOutput = vec3();

	matrix3x4& mtx = cl.engine->GetScreenMatrix();
	float w = mtx[3][0] * vecInput.x + mtx[3][1] * vecInput.y + mtx[3][2] * vecInput.z + mtx[3][3];
	if (w <= 0.001)
		return false;

	vecOutput.x = (cl.sw * 0.5);
	vecOutput.x += (0.5 * ((mtx[0][0] * vecInput.x + mtx[0][1] * vecInput.y + mtx[0][2] * vecInput.z + mtx[0][3]) * (1 / w)) * cl.sw + 0.5);
	vecOutput.y = (cl.sh * 0.5);
	vecOutput.y -= (0.5 * ((mtx[1][0] * vecInput.x + mtx[1][1] * vecInput.y + mtx[1][2] * vecInput.z + mtx[1][3]) * (1 / w)) * cl.sh + 0.5);

	return true;
}

void __cdecl getBoxCoords(Entity *ent, int &minx, int &miny, int &maxx, int &maxy)
{
	vec3 min, max;
	min = ent->Maxs() + ent->GetOrigin();
	max = ent->Mins() + ent->GetOrigin();
	vec3 corners[8] =
	{
		vec3(min.x, min.y, min.z),
		vec3(min.x, min.y, max.z),
		vec3(min.x, max.y, min.z),
		vec3(min.x, max.y, max.z),
		vec3(max.x, min.y, min.z),
		vec3(max.x, min.y, max.z),
		vec3(max.x, max.y, min.z),
		vec3(max.x, max.y, max.z)
	};

	//int minx, miny, maxx, maxy;
	minx = cl.sw * 2;
	miny = cl.sh * 2;
	maxx = 0;
	maxy = 0;

	for (unsigned int i = 1; i < 8; i++)
	{
		vec3 corner = corners[i];
		vec3 screen;
		if (worldToScreen(corner, screen))
		{
			minx = min(minx, screen.x);
			miny = min(miny, screen.y);
			maxx = max(maxx, screen.x);
			maxy = max(maxy, screen.y);
		}
	}
}




const char *(__thiscall* GetGModClassname)(void*);
void HookedPaintTraverse(int panel, bool repaint, bool force)
{
	static bool bDoOnce = false;
	if (!bDoOnce) {
		GetGModClassname = (const char*(__thiscall*)(void*))sigscan::FindPattern("client.dll", "\x57\x8B\xF9\x8B\x87????\x85\xC0\x74\x0D\x50\xE8");
		bDoOnce = true;
	}
	if (panel == cl.vgui->GetPanel(4)) // what the fuck again ok
	{
		cl.engine->GetScreenSize(cl.sw, cl.sh);
		cl.surface->SetFont(5); // keep this
		cl.surface->SetDrawColor(255, 150, 50);
		cl.local = cl.engine->GetLocalPlayer();
		GetCursorPos(&mousepos); ScreenToClient(GetActiveWindow(), &mousepos);
		if (GetKeyState(VK_INSERT) & 1)
			GUI::shitMenu();



		Entity* ply;

		int max = cl.engine->GetMaxClients();
		for (int i = 0; i <= max; i++)
		{
			if (i == cl.local)
				continue;

			ply = cl.ents->GetEntity(i);
			if (!ply)
				continue;

			PlayerInfo playerInfo;
			cl.engine->GetPlayerInfo(i, playerInfo);
			if (variables::Visuals::Active);
			if (!ply->Alive())
				continue;

			int m_iHealth = ply->Health();
			if (m_iHealth <= 0)
				continue;
			int x, y, w, h;
			getBoxCoords(ply, x, y, w, h);
			w = w - x; h = h - y;

			cl.surface->SetDrawColor(0, 0, 0);
			cl.surface->DrawOutlined(x - 1, y - 1, w + 2, h + 2);
			cl.surface->DrawOutlined(x + 1, y + 1, w - 2, h - 2);
			cl.surface->SetDrawColor(255, 150, 50);
			cl.surface->DrawOutlined(x, y, w, h);

			cl.surface->SetTextColor(240, 240, 240);
			cl.surface->SetTextPos(x + w + 2, y);
			cl.surface->DrawText(playerInfo.name);


			// find math clamp later
			float flBarlenght = (m_iHealth * (w - 2)) / 100; // assuming 100 is max health so we divide by 100
			cl.surface->SetDrawColor(0, 0, 0);
			cl.surface->DrawOutlined(x - 1, y - 1 - 7, w + 2, 3 + 2);
			cl.surface->DrawOutlined(x + 1, y + 1 - 7, w - 2, 3 - 2);
			cl.surface->SetDrawColor(255 - 2.55 * (m_iHealth), 2.55 * (m_iHealth), 0);
			cl.surface->DrawRect(x, y - 7, flBarlenght, 3);





			//Entity* pWeapon = cl.ents->GetEntity(ply->Weapon());
			//if (pWeapon) {
			cl.surface->SetTextPos(x + w + 2, y + 10); // weapon esp later
			cl.surface->DrawText(GetGModClassname(ply));
			//}
		}
	}

	PaintTraverse(cl.panel, panel, repaint, force);
}
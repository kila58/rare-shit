#pragma once

#include "cEsp.h"
#include "cCvar.h"

CEsp gEsp;

float flGetDistance(Vector vOrigin, Vector vLocalOrigin)
{
	Vector vDelta = vOrigin - vLocalOrigin;

	float m_fDistance = FastSqrt(vDelta.Length());

	if (m_fDistance < 1.0f)
		return 1.0f;

	return m_fDistance;
}

void DrawPlayerBox(CBaseEntity *pEnt, DWORD dwColor)
{
	if (pEnt == NULL)
		return;

	Vector min, max;


	max = pEnt->GetAbsOrigin();

	min = max + Vector(0, 0, 70.f);

	Vector bot, top;

	if (gDrawing.WorldToScreen(max, bot) && gDrawing.WorldToScreen(min, top))
	{

		float h = (bot.y - top.y);
		float w = h / 2.6f;

		gDrawing.DrawBoxBlackBackground(top.x - (w / 2), top.y, w, h, dwColor);

	}

}

void ReallyDrawHealthBar(CBaseEntity *pEnt, DWORD dwColor, float health)
{

	if (pEnt == NULL)
		return;

	Vector min, max;

	max = pEnt->GetAbsOrigin();

	min = max + Vector(0, 0, 70.f);

	Vector bot, top;

	if (gDrawing.WorldToScreen(max, bot) && gDrawing.WorldToScreen(min, top))
	{

		float h = (bot.y - top.y);
		float w = h / 2.6f;

		int Red = 255 - (health*2.55);
		int Green = health*2.55;

		//Note to self: x is left and right, y is up and down
		gDrawing.DrawHealthBar(top.x - (w / 2) - 5, top.y - (h / -2), health, 5, h + 3, COLORCODE(Red, Green, 0, 255));
	}
}

inline float GetDistance(Vector vOrigin, Vector vLocalOrigin)
{
	Vector vDelta = vOrigin - vLocalOrigin;

	float m_fDistance = sqrt(vDelta.Length());

	if (m_fDistance < 1.0f)
		return 1.0f;

	return m_fDistance;
}

void CEsp::DrawPlayerESP(int iIndex)
{

	player_info_s pInfo;

	CBaseEntity* pPlayer = (C_BaseEntity*)entitylist->GetClientEntity(g_pEngine->GetLocalPlayer());

	if (!pPlayer)
		return;

	CBaseEntity* pBaseEntity = (C_BaseEntity*)entitylist->GetClientEntity(iIndex);

	if (!pBaseEntity)
		return;

	if (pBaseEntity == pPlayer)
		return;

	Vector vScreen;
	Vector vWorldPosition;
	Vector vPlayerHead;

	Vector vHead;
	Vector vPlayerLeg;

	int health = *(int*)((DWORD)pBaseEntity + (DWORD)0x90);

	float Height = abs(vPlayerLeg.y - vPlayerHead.y);
	float Width = Height / 2.0f;

	float Distance = GetDistance(pBaseEntity->GetAbsOrigin(), pPlayer->GetAbsOrigin());

	if (g_pEngine->GetPlayerInfo(iIndex, &pInfo))
	{
		if (gDrawing.WorldToScreen(pBaseEntity->GetAbsOrigin(), vPlayerHead))
		{
			gDrawing.DrawString(vPlayerHead.x, vPlayerHead.y - (vHead.y / 2), COLORCODE(255, 0, 0, 255), "%s", pInfo.name);
			vPlayerHead.y += 12;

			gDrawing.DrawString(vPlayerHead.x, vPlayerHead.y, COLORCODE(255, 0, 0, 255), "Dist: %.0fm", Distance);
			vPlayerHead.y += 12;

			DrawPlayerBox(pBaseEntity, COLORCODE(255, 255, 255, 255));
			ReallyDrawHealthBar(pBaseEntity, COLORCODE(255, 255, 255, 255), health);

			Vector min, max;
			pBaseEntity->GetRenderBounds(min, max);
			//g_pDebugOverlay->AddBoxOverlay(pBaseEntity->GetAbsOrigin(), min, max, pBaseEntity->GetAbsAngles(), 255, 0, 0, 25, 0.05f);
		}
	}
}

void CEsp::DrawEntityESP(int iIndex)
{

	CBaseEntity* pPlayer = (C_BaseEntity*)entitylist->GetClientEntity(g_pEngine->GetLocalPlayer());

	CBaseEntity* pBaseEntity = (C_BaseEntity*)entitylist->GetClientEntity(iIndex);

	if (pBaseEntity == NULL)
		return;

	if (pBaseEntity->IsDormant() == false)
	{
		Vector vScreen;

		if (gDrawing.WorldToScreen(pBaseEntity->GetAbsOrigin(), vScreen) == false)
			return;

		const char* modelName = g_pModelInfo->GetModelName(pBaseEntity->GetModel());
		if (!modelName) return;

		if (strstr(modelName, "c_")) return;
		//if (strstr(modelName, "w_")) return;
		if (strstr(modelName, "v_")) return;

		/*if (!(entitylist->GetClientEntityFromHandle(pBaseEntity->m_hOwnerEntity)))
		{
			if (strstr(pBaseEntity->GetClientClass()->GetName(), "CWeapon"))
			{
				//gDrawing.DrawString(vScreen.x, vScreen.y, COLORCODE(255, 0, 0, 255), modelName);

				Vector min, max;
				pBaseEntity->GetRenderBounds(min, max);
				g_pDebugOverlay->AddBoxOverlay(pBaseEntity->GetAbsOrigin(), min, max, pBaseEntity->GetAbsAngles(), rand() % 255, rand() % 255, rand() % 255, 25, 0.05f);
			}
			if (strstr(pBaseEntity->GetClientClass()->GetName(), "SENT"))
			{
				//gDrawing.DrawString(vScreen.x, vScreen.y, COLORCODE(255, 0, 0, 255), modelName);

				Vector min, max;
				pBaseEntity->GetRenderBounds(min, max);
				g_pDebugOverlay->AddBoxOverlay(pBaseEntity->GetAbsOrigin(), min, max, pBaseEntity->GetAbsAngles(), rand() % 255, rand() % 255, rand() % 255, 25, 0.05f);
			}
		}*/
	}
}

void CEsp::DrawCrosshair()
{
	if (gCvar.esp_active && gCvar.esp_crosshair)
	{
		int x = 0;
		int y = 0;

		g_pEngine->GetScreenSize(x, y);

		x /= 2;
		y /= 2;

		int gap = 5;
		int length = gap + 15;

		gDrawing.DrawLine(x - length, y, x - gap, y, COLORCODE(255, 150, 0, 255));
		gDrawing.DrawLine(x + length, y, x + gap, y, COLORCODE(255, 150, 0, 255));
		gDrawing.DrawLine(x, y - length, x, y - gap, COLORCODE(255, 150, 0, 255));
		gDrawing.DrawLine(x, y + length, x, y + gap, COLORCODE(255, 150, 0, 255));
	}
}

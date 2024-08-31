#pragma once
#include "CDrawManager.h"
//===================================================================================

CDrawManager gDrawManager;
//CInterfacez interfaceManager;

#define ESP_HEIGHT 16
#define HUD_HEIGHT 20
unsigned long m_Font;
HFont gameFont;
//===================================================================================
void CDrawManager::Initialize()
{
	if (Surface == NULL)
		return;
	Engine->GetScreenSize(gScreenWidth, gScreenHeight);
	m_Font = Surface->CreateFont();
	//04b09
	Surface->SetFontGlyphSet(m_Font, "U.S. 101", ESP_HEIGHT, 400, 0, 0, 16);
	gameFont = Surface->CreateFont();
	Surface->SetFontGlyphSet(gameFont, "Tahoma", HUD_HEIGHT, 500, 0, 0, 16);
}
//===================================================================================
void CDrawManager::DrawString(bool centred, bool esp, int x, int y, Color dwColor, const wchar_t *pszText)
{
	if (pszText == NULL)
		return;
	
	else
		Surface->DrawSetTextPos(x, y);
	Surface->DrawSetTextFont(esp ? m_Font : gameFont);
	Surface->DrawSetTextColor(dwColor);

	Surface->DrawPrintText(pszText, wcslen(pszText));
}
//===================================================================================
void CDrawManager::DrawString(bool centred, bool esp, int x, int y, Color dwColor, const char *pszText, ...)
{
	if (pszText == NULL)
		return;

	va_list va_alist;
	char szBuffer[1024] = { '\0' };
	wchar_t szString[1024] = { '\0' };

	va_start(va_alist, pszText);
	vsprintf_s(szBuffer, pszText, va_alist);
	va_end(va_alist);

	wsprintfW(szString, L"%S", szBuffer);

	
	
	Surface->DrawSetTextPos(x, y);
	Surface->DrawSetTextFont(esp ? m_Font : gameFont);
	Surface->DrawSetTextColor(dwColor);
	Surface->DrawPrintText(szString, wcslen(szString));
}
//===================================================================================
byte CDrawManager::GetESPHeight()
{
	return ESP_HEIGHT;
}
//===================================================================================
void CDrawManager::DrawRect(int x, int y, int w, int h, Color dwColor)
{
	Surface->DrawSetColor(dwColor);
	Surface->DrawFilledRect(x, y, x + w, y + h);
}
//===================================================================================
void CDrawManager::OutlineRect(int x, int y, int w, int h, Color dwColor)
{
	Surface->DrawSetColor(dwColor);
	Surface->DrawOutlinedRect(x, y, x + w, y + h);
}
//===================================================================================
void CDrawManager::DrawBox(Vector vOrigin, int r, int g, int b, int alpha, int box_width, int radius)
{
	Vector vScreen;

	if (!WorldToScreen(vOrigin, vScreen))
		return;

	int radius2 = radius << 1;

	OutlineRect(vScreen.x - radius + box_width, vScreen.y - radius + box_width, radius2 - box_width, radius2 - box_width, Color(0, 0, 0, 255));
	OutlineRect(vScreen.x - radius - 1, vScreen.y - radius - 1, radius2 + (box_width + 2), radius2 + (box_width + 2), Color(0, 0, 0, 255));
	DrawRect(vScreen.x - radius + box_width, vScreen.y - radius, radius2 - box_width, box_width, Color(r, g, b, alpha));
	DrawRect(vScreen.x - radius, vScreen.y + radius, radius2, box_width, Color(r, g, b, alpha));
	DrawRect(vScreen.x - radius, vScreen.y - radius, box_width, radius2, Color(r, g, b, alpha));
	DrawRect(vScreen.x + radius, vScreen.y - radius, box_width, radius2 + box_width, Color(r, g, b, alpha));
}
//===================================================================================
bool CDrawManager::WorldToScreen(Vector &vOrigin, Vector &vScreen)
{
	return gAimbot.WorldToScreen(vOrigin, vScreen);
}


void CDrawManager::DrawPlayerBox(CBaseEntityNew *pEnt, Color dwColor,Vector &vTop,Vector &vBot,int &iW, int &iH)
{
	if (pEnt == NULL)
		return;
	Vector vMon, vNom;

	vNom = pEnt->GetAbsOrigin();

	vMon = vNom + Vector(0, 0, 70.f);
	if (pEnt->GetFlags() & IN_DUCK)
		vMon = vNom + Vector(0, 0, 60.f);
	if (WorldToScreen(vNom, vBot) && WorldToScreen(vMon, vTop))
	{
		iH = (vBot.y - vTop.y);
		iW = iH / 4.f;
		if (pEnt->GetFlags() & IN_DUCK)
			iW = iH / 3.f;
		OutlineRect(vTop.x - iW, vTop.y, iW * 2, iH, dwColor);
	}
}

float CDrawManager::flGetDistance(Vector from, Vector to)
{
	Vector angle;
	angle.x = to.x - from.x;	angle.y = to.y - from.y;	angle.z = to.z - from.z;

	return sqrt(angle.x*angle.x + angle.y*angle.y + angle.z*angle.z);
}
void CDrawManager::DrawCrosshair(int iValue)

{
	int m_iScreenWidth;
	int	m_iScreenHeight;
	Engine->GetScreenSize(m_iScreenWidth, m_iScreenHeight);
	Color dwRed = Color(255, 50, 0, 255);
	Color dwWhite = Color(255, 255, 255, 255);

	switch (iValue)
	{
	case 1:
		DrawRect((m_iScreenWidth / 2) - 25, m_iScreenHeight / 2, 50, 1, dwWhite);
		DrawRect(m_iScreenWidth / 2, (m_iScreenHeight / 2) - 25, 1, 50, dwWhite);
		DrawRect((m_iScreenWidth / 2) - 7, m_iScreenHeight / 2, 14, 1, dwRed);
		DrawRect(m_iScreenWidth / 2, (m_iScreenHeight / 2) - 7, 1, 14, dwRed);
		break;
	case 2:
		DrawRect(m_iScreenWidth / 2 - 14, (m_iScreenHeight / 2), 9, 1, dwWhite);
		DrawRect(m_iScreenWidth / 2 + 5, (m_iScreenHeight / 2), 9, 1, dwWhite);
		DrawRect(m_iScreenWidth / 2, (m_iScreenHeight / 2) - 14, 1, 9, dwWhite);
		DrawRect(m_iScreenWidth / 2, (m_iScreenHeight / 2) + 5, 1, 9, dwWhite);
		DrawRect(m_iScreenWidth / 2, (m_iScreenHeight / 2), 1, 1, dwWhite);

		break;
	case 3:
		DrawRect(m_iScreenWidth / 2 - 14, (m_iScreenHeight / 2), 9, 2, dwWhite);
		DrawRect(m_iScreenWidth / 2 + 6, (m_iScreenHeight / 2), 9, 2, dwWhite);
		DrawRect(m_iScreenWidth / 2, (m_iScreenHeight / 2) - 14, 2, 9, dwWhite);
		DrawRect(m_iScreenWidth / 2, (m_iScreenHeight / 2) + 7, 2, 9, dwWhite);
		DrawRect(m_iScreenWidth / 2, (m_iScreenHeight / 2), 2, 2, dwWhite);
		break;
	case 4:
		DrawRect((m_iScreenWidth / 2) - 2, (m_iScreenHeight / 2) - 2, 4, 4, dwWhite);
		break;
	}
}
#include "CDrawManager.h"
#include "CGlobalVars.h"
#include "Player Manager.h"
#include "Extra Functions.h"
#include "SDK.h"
#include "Math.h"
#include "Player ESP.h" // Base Header
#include "Color Manager.h" // gDrawManager
#include "Control Variables.h"
#include <stdint.h>




void CDrawManager::DrawGradient(int x, int y, int w, int h,GradientType gType, Color from, Color to)
{
	if (gType == GRADIENT_HORIZONAL_FILL)
	{
		float r = (to.r() - from.r()) / w;
		float g = (to.g() - from.g()) / w;
		float b = (to.b() - from.b()) / w;
		float a = (to.a() - from.a()) / w;

		for (int i = 0; i < h; i++) {
			int R = from.r() + r * i;
			int G = from.g() + g * i;
			int B = from.b() + b * i;
			int A = from.a() + a * i;

			ALX.pDrawManager->FillRGBA(x + i, y, 1, h, Color(R, G, B, A));
		}
	}
	else if (gType == GRADIENT_VERTICAL_FILL)
	{

		float r = (to.r() - from.r()) / h;
		float g = (to.g() - from.g()) / h;
		float b = (to.b() - from.b()) / h;
		float a = (to.a() - from.a()) / h;

		for (int i = 0; i < h; i++)
		{
			int R = from.r() + r * i;
			int G = from.g() + g * i;
			int B = from.b() + b * i;
			int A = from.a() + a * i;

			ALX.pDrawManager->FillRGBA(x, y + i, w, 1, Color(R, G, B, A));
		}
	}
}



//===================================================================================

void CDrawManager::Initialize( )
{
	if ( ALX.pSurface == NULL )
		return;

	ALX.pEngine->GetScreenSize( gScreenSize.iScreenWidth, gScreenSize.iScreenHeight );

	m_ESPFont = ALX.pSurface->CreateFont( );
	ALX.pSurface->SetFontGlyphSet( m_ESPFont, "Verdana", 12, 800, 0, 0, FONTFLAG_DROPSHADOW);

	m_HUDFont = ALX.pSurface->CreateFont( );
	ALX.pSurface->SetFontGlyphSet( m_HUDFont, "Tahoma", 18, 500, 0, 0, FONTFLAG_OUTLINE );

	//verdana, size 12, weight 800

}
//===================================================================================

void CDrawManager::DrawCrosshair(int x, int y,Color color)
{
	ALX.pSurface->DrawSetColor(color);

	ALX.pSurface->DrawLine(x - 5, y, x + 5, y);
	ALX.pSurface->DrawLine(x, y - 5, x, y + 5);

	ALX.pSurface->DrawLine(x - 2.5, y, x + 2.5, y);
	ALX.pSurface->DrawLine(x, y - 2.5, x, y + 2.5);
}

void CDrawManager::GradientFunc(int x, int y, int w, int h, Color dwColor)
{
	int Cr, Cg, Cb;
	for (int i = 1; i < h; i++)
	{
		Cr = (int)((float)i / h*dwColor.r());
		Cg = (int)((float)i / h*dwColor.g());
		Cb = (int)((float)i / h*dwColor.b());
		this->FillRGBA(x, y + i, w, 1, Color(dwColor.r() - Cr, dwColor.g() - Cg, dwColor.b() - Cb, 255));
	}
}

void CDrawManager::DrawString( bool HUDFont, int x, int y, DWORD dwColor, const wchar_t *pszText)
{
	if( pszText == NULL )
		return;

	ALX.pSurface->DrawSetTextPos( x, y );
	ALX.pSurface->DrawSetTextFont( HUDFont ? m_HUDFont: m_ESPFont );
	ALX.pSurface->DrawSetTextColor( RED(dwColor), GREEN(dwColor), BLUE(dwColor), ALPHA(dwColor) );
	ALX.pSurface->DrawPrintText( pszText, wcslen( pszText ) );
}

void CDrawManager::DrawStringZ(bool HUDFont, int x, int y, Color dwColor, const wchar_t *pszText)
{
	if (pszText == NULL) return;

	ALX.pSurface->DrawSetTextPos(x, y);
	ALX.pSurface->DrawSetTextFont(HUDFont ? m_HUDFont : m_ESPFont);
	ALX.pSurface->DrawSetTextColor1(dwColor);
	ALX.pSurface->DrawPrintText(pszText, wcslen(pszText));
}

void CDrawManager::DrawStringZ(bool HUDFont, int x, int y, Color dwColor, const char *pszText, ...)
{
	if (pszText == NULL) return;

	va_list va_alist;
	char szBuffer[1024] = { '\0' };
	wchar_t szString[1024] = { '\0' };

	va_start(va_alist, pszText);
	vsprintf_s(szBuffer, pszText, va_alist);
	va_end(va_alist);

	wsprintfW(szString, L"%S", szBuffer);

	ALX.pSurface->DrawSetTextPos(x, y);
	ALX.pSurface->DrawSetTextFont(HUDFont ? m_HUDFont : m_ESPFont);
	ALX.pSurface->DrawSetTextColor1(dwColor);
	ALX.pSurface->DrawPrintText(szString, wcslen(szString));
}
void CDrawManager::DrawLine2D(Vector a, Vector b, Color dat)
{
	this->DrawLine1(a.x, a.y, b.x, b.y, dat);

}

void CDrawManager::DrawString( bool HUDFont, int x, int y, DWORD dwColor, const char *pszText, ... )
{
	if( pszText == NULL )
		return;

	va_list va_alist;
	char szBuffer[1024] = { '\0' };
	wchar_t szString[1024] = { '\0' };

	va_start( va_alist, pszText );
	vsprintf_s( szBuffer, pszText, va_alist );
	va_end( va_alist );

	wsprintfW( szString, L"%S", szBuffer );

	ALX.pSurface->DrawSetTextPos( x, y );
	ALX.pSurface->DrawSetTextFont( HUDFont ? m_HUDFont: m_ESPFont  );
	ALX.pSurface->DrawSetTextColor( dwColor );
	ALX.pSurface->DrawPrintText( szString, wcslen( szString ) );
}

void CDrawManager::DrawCorneredBox(int x, int y, int w, int h, Color colour)
{
	Vector TO_Pos(x, y, 0);
	int bWidth = w;
	int bHeight = h;

	// Box: Upper Left Corner    V
	DrawLine1(TO_Pos.x, TO_Pos.y, TO_Pos.x, TO_Pos.y + (bHeight / 5), colour); // Top To Bottom
	DrawLine1(TO_Pos.x, TO_Pos.y, TO_Pos.x + (bWidth / 5), TO_Pos.y, colour); // Left To Right
	// Box: Upper Right Corner   V
	DrawLine1(TO_Pos.x + bWidth, TO_Pos.y, TO_Pos.x + bWidth - (bWidth / 5), TO_Pos.y, colour); // Right To Left
	DrawLine1(TO_Pos.x + bWidth, TO_Pos.y, TO_Pos.x + bWidth, TO_Pos.y + (bHeight / 5), colour); // Top To Bottom
	// Box: Bottom Left Corner   V
	DrawLine1(TO_Pos.x, TO_Pos.y + bHeight, TO_Pos.x + (bWidth / 5), TO_Pos.y + bHeight, colour); // Right To Left
	DrawLine1(TO_Pos.x, TO_Pos.y + bHeight, TO_Pos.x, TO_Pos.y + bHeight - (bHeight / 5), colour); // Bottom To Top
	// Box: Bottom Right Corner  V
	DrawLine1(TO_Pos.x + bWidth, TO_Pos.y + bHeight, TO_Pos.x + bWidth - (bWidth / 5), TO_Pos.y + bHeight, colour); // Right To Left
	DrawLine1(TO_Pos.x + bWidth, TO_Pos.y + bHeight, TO_Pos.x + bWidth, TO_Pos.y + bHeight - (bHeight / 5), colour); // Bottom To Top
}
void CDrawManager::DrawOC(int x, int y, int w, int h, Color colour)
{
	DrawCorneredBox(x - 1, y - 1, w + 2, h + 2, Color(0, 0, 0, 255));
	DrawCorneredBox(x, y, w, h, colour);
}

void CDrawManager::FillRGBA2(int x, int y, int w, int h, Color colour, Color color)
{
	FillRGBA(x, y, w, h, colour);
	OutlineRect1(x, y, w, h, color);
}

void CDrawManager::DrawString1(bool HUDFont, int x, int y, Color dwColor, const char *pszText, ...)
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

	ALX.pSurface->DrawSetTextPos(x, y);
	ALX.pSurface->DrawSetTextFont(HUDFont ? m_HUDFont : m_ESPFont);
	ALX.pSurface->DrawSetTextColor1(dwColor);
	ALX.pSurface->DrawPrintText(szString, wcslen(szString));
}

void CDrawManager::DrawRect( int x, int y, int w, int h, DWORD dwColor )
{
	ALX.pSurface->DrawSetColor( dwColor );
	ALX.pSurface->DrawFilledRect( x, y, x + w, y + h );
}
void CDrawManager::DrawRect1(int x, int y, int w, int h, Color dwColor)
{
	ALX.pSurface->DrawSetColor(dwColor);
	ALX.pSurface->DrawFilledRect(x, y, x + w, y + h);
}
//===================================================================================
void CDrawManager::OutlineRect( int x, int y, int w, int h, DWORD dwColor )
{
	ALX.pSurface->DrawSetColor( dwColor );
	ALX.pSurface->DrawOutlinedRect( x, y, x + w, y + h );
}

void CDrawManager::OutlineRect1(int x, int y, int w, int h, Color dwColor)
{
	ALX.pSurface->DrawSetColor(dwColor);
	ALX.pSurface->DrawOutlinedRect(x, y, x + w, y + h);
}
void CDrawManager::DrawLine(int x, int y, int x2, int y2, DWORD dwColor)
{
	ALX.pSurface->DrawSetColor(dwColor);
	ALX.pSurface->DrawLine(x, y, x2, y2);

}

#define DM gDrawManager
void CDrawManager::DrawRhombus(int x, int y, int w, int h, Color dwColor)
{
	int W = w / 2;

	ALX.pDrawManager->DrawLine1(x + W, y, x + W + w, y, dwColor); //top
	ALX.pDrawManager->DrawLine1(x + W - h, y + h, x + W, y, dwColor); //left
	ALX.pDrawManager->DrawLine1(x + W + w - h, y + h, x + W + w, y, dwColor); //right
	ALX.pDrawManager->DrawLine1(x + W - h, y + h, x + W + w - h, y + h, dwColor); //bottom
}



void CDrawManager::DrawRhombusFill(int x, int y, int w, int h, Color dwColor)
{
	int W = w / 2;
	ALX.pSurface->DrawSetColor(dwColor);
	for (int i = 0; i < h; i++)
	{
	  ALX.pSurface->DrawLine(x + W - i, y + i, x + W + w - i, y + i);
	}
}

void CDrawManager::DrawLine1(int x, int y, int x2, int y2, Color dwColor)
{
	ALX.pSurface->DrawSetColor(dwColor);
	ALX.pSurface->DrawLine(x, y, x2, y2);

}

void CDrawManager::TextW(bool cent, int font, int x, int y, Color color, wchar_t *pszString)
{
	if (cent)
	{
		int wide, tall;
		ALX.pSurface->GetTextSize(font, pszString, wide, tall);
		x -= wide / 2;
		y -= tall / 2;
	}
	ALX.pSurface->DrawSetTextColor1(color);
	ALX.pSurface->DrawSetTextFont(font);
	ALX.pSurface->DrawSetTextPos(x, y);
	ALX.pSurface->DrawPrintText1(pszString, (int)wcslen(pszString), FONT_DRAW_DEFAULT);
}

void CDrawManager::DrawStringM(int FONT, bool bCenter, int x, int y, Color c, const char *fmt, ...)
{
	wchar_t *pszStringWide = reinterpret_cast< wchar_t* >(malloc((strlen(fmt) + 1) * sizeof(wchar_t)));

	mbstowcs(pszStringWide, fmt, (strlen(fmt) + 1) * sizeof(wchar_t));

	TextW(bCenter, FONT, x, y, c, pszStringWide);

	free(pszStringWide);
}

void CDrawManager::DrawStringM1(int FONT, bool bCenter, float x, float y, Color c, const char *fmt, ...)
{
	wchar_t *pszStringWide = reinterpret_cast< wchar_t* >(malloc((strlen(fmt) + 1) * sizeof(wchar_t)));

	mbstowcs(pszStringWide, fmt, (strlen(fmt) + 1) * sizeof(wchar_t));

	TextW(bCenter, FONT, x, y, c, pszStringWide);

	free(pszStringWide);
}

void CDrawManager::BorderBoxOutlined(int x, int y, int w, int h, Color dwColor, Color Outline)
{
	this->OutlineRect1(x, y, w, h, dwColor);
	ALX.pSurface->DrawSetColor(Outline);
	ALX.pSurface->DrawOutlinedRect(x + 1, y + 1, x + w - 1, y + h - 1);
	ALX.pSurface->DrawOutlinedRect(x - 1, y - 1, x + w + 1, y + h + 1);
}

void CDrawManager::BorderCornerBoxOutlined(int x, int y, int w, int h, Color dwColor, Color Outline)
{
	this->DrawCorneredBox(x, y, w, h, dwColor);
	this->DrawCorneredBox(x + 1, y + 1,  w - 1,  h - 1,Outline);
	this->DrawCorneredBox(x - 1, y - 1,  w + 1, h + 1,Outline);
}

bool CDrawManager::WorldToScreen( Vector &vOrigin, Vector &vScreen )
{
	const matrix3x4& worldToScreen = ALX.pEngine->WorldToScreenMatrix(); //Grab the world to screen matrix from CEngineClient::WorldToScreenMatrix

	float w = worldToScreen[3][0] * vOrigin[0] + worldToScreen[3][1] * vOrigin[1] + worldToScreen[3][2] * vOrigin[2] + worldToScreen[3][3]; //Calculate the angle in compareson to the player's camera.
	vScreen.z = 0; //Screen doesn't have a 3rd dimension.

	if( w > 0.001 ) //If the object is within view.
	{
		float fl1DBw = 1 / w; //Divide 1 by the angle.
		vScreen.x = (gScreenSize.iScreenWidth / 2) + ( 0.5 * ((worldToScreen[0][0] * vOrigin[0] + worldToScreen[0][1] * vOrigin[1] + worldToScreen[0][2] * vOrigin[2] + worldToScreen[0][3]) * fl1DBw) * gScreenSize.iScreenWidth + 0.5); //Get the X dimension and push it in to the Vector.
		vScreen.y = (gScreenSize.iScreenHeight / 2) - ( 0.5 * ((worldToScreen[1][0] * vOrigin[0] + worldToScreen[1][1] * vOrigin[1] + worldToScreen[1][2] * vOrigin[2] + worldToScreen[1][3]) * fl1DBw) * gScreenSize.iScreenHeight + 0.5); //Get the Y dimension and push it in to the Vector.
		return true;
	}

	return false;
}
//===================================================================================
bool CDrawManager::ScreenTransform( const Vector &point, Vector &screen )
{
	float w;
	const matrix3x4 &worldToScreen = ALX.pEngine->WorldToScreenMatrix( );
	screen.x = worldToScreen[0][0] * point[0] + worldToScreen[0][1] * point[1] + worldToScreen[0][2] * point[2] + worldToScreen[0][3];
	screen.y = worldToScreen[1][0] * point[0] + worldToScreen[1][1] * point[1] + worldToScreen[1][2] * point[2] + worldToScreen[1][3];
	w		 = worldToScreen[3][0] * point[0] + worldToScreen[3][1] * point[1] + worldToScreen[3][2] * point[2] + worldToScreen[3][3];
	screen.z = 0.0f;

	bool behind = false;

	if( w < 0.001f )
	{
		behind = true;
		screen.x *= 100000;
		screen.y *= 100000;
	}
	else
	{
		behind = false;
		float invw = 1.0f / w;
		screen.x *= invw;
		screen.y *= invw;
	}
	return behind;
}
//===================================================================================
void CDrawManager::DrawBox(Vector vOrigin, int r, int g, int b, int alpha, int box_width, int radius)
{
	Vector vScreen;

	if (!WorldToScreen(vOrigin, vScreen))
		return;

	int radius2 = radius << 1;

	OutlineRect(vScreen.x - radius + box_width, vScreen.y - radius + box_width, radius2 - box_width, radius2 - box_width, 0x000000FF);
	OutlineRect(vScreen.x - radius - 1, vScreen.y - radius - 1, radius2 + (box_width + 2), radius2 + (box_width + 2), 0x000000FF);
	DrawRect(vScreen.x - radius + box_width, vScreen.y - radius, radius2 - box_width, box_width, COLORCODE(r, g, b, alpha));
	DrawRect(vScreen.x - radius, vScreen.y + radius, radius2, box_width, COLORCODE(r, g, b, alpha));
	DrawRect(vScreen.x - radius, vScreen.y - radius, box_width, radius2, COLORCODE(r, g, b, alpha));
	DrawRect(vScreen.x + radius, vScreen.y - radius, box_width, radius2 + box_width, COLORCODE(r, g, b, alpha));
}
 
void CDrawManager::DrawPlayerBox1(CBaseEntity *pEnt,int w, int h, Color dwColor, int iIndex)
{

	player_info_t pInfo;
	CSetupPlayer __pBaseEntity = gPlayers[iIndex];
	DWORD dwTeamColor = ALX.pColorManager->dwGetColor(*MakePtr(int*, pEnt, ALX.pPlayerVariables->m_iTeamNum));

	if (pEnt == NULL)
		return;

	Vector mon, nom;

	nom = pEnt->GetAbsOrigin();

	Vector bot, top;

	

		OutlineRect1(top.x -2 - w +1, top.y -1, w * 2 +2, (bot.y +1 - top.y +1), dwColor);
		OutlineRect1(top.x +2 - w -1, top.y +1, w * 2 -2, (bot.y -1 - top.y -1), dwColor);

	

}
void CDrawManager::DrawChickenBox(CBaseEntity *pEnt, Color dwColor)
{
	if (pEnt == NULL)
		return;

	Vector mon, nom;

	nom = pEnt->GetAbsOrigin();

	mon = nom + Vector(0, 0, 20.f);


	Vector bot, top;

	if (WorldToScreen(nom, bot) && WorldToScreen(mon, top))
	{
		float h = (bot.y - top.y);

		float w = h / 2.f;

		OutlineRect1(top.x - w, top.y, w * 2, (bot.y - top.y), dwColor);

	}

}
void CDrawManager::DrawChickenBox1(CBaseEntity *pEnt, Color dwColor, int iIndex)
{
	CSetupPlayer __pBaseEntity = gPlayers[iIndex];

	if (pEnt == NULL)
		return;

	Vector mon, nom;

	nom = pEnt->GetAbsOrigin();
	mon = nom + Vector(0, 0, 20.f);
	

	Vector bot, top;

	if (WorldToScreen(nom, bot) && WorldToScreen(mon, top))
	{
		float h = (bot.y - top.y);

		float w = h / 2.f;

		OutlineRect1(top.x - 2 - w + 1, top.y - 1, w * 2 + 2, (bot.y + 1 - top.y + 1), dwColor);
		OutlineRect1(top.x + 2 - w - 1, top.y + 1, w * 2 - 2, (bot.y - 1 - top.y - 1), dwColor);

	}

}
//================================================================================
bool CDrawManager::GetBonePosition(CBaseEntity* pPlayer, Vector& Hitbox, int Bone)
{
	matrix3x4 MatrixArray[128];

	if(!pPlayer->SetupBones( MatrixArray, 128, 0x00000100, ALX.pEngine->Time() ) )
		return false;

	Hitbox = Vector(MatrixArray[Bone][0][3], MatrixArray[Bone][1][3], MatrixArray[Bone][2][3]);

	return true;
}


void CDrawManager::FillRGBA(int x, int y, int w, int h, Color colour)
{
	ALX.pSurface->DrawSetColor(colour);
	ALX.pSurface->DrawFilledRect(x, y, x + w, y + h);
}
void CDrawManager::FillRGBA1(int x, int y, int w, int h, DWORD dwColor)
{
	ALX.pSurface->DrawSetColor(dwColor);
	ALX.pSurface->DrawFilledRect(x, y, x + w, y + h);
}
void CDrawManager::DrawHealthBar(int x, int y, float health, int w, int h, Color Draw)
{
	x -= w / 2;
	y -= h / 2;
	FillRGBA(x, y, w, h + 1, Color(0, 0, 0, 255));
	UINT hw = (UINT)(((w - 2) * health) / 100);
	FillRGBA(x + 1, y + 1, hw, h - 1, Draw);
}
void CDrawManager::drawGrid(int x, int y, int w, int h, Color colour)
{
	int newX = x, newY = y;
	while (newX < x + w){
		FillRGBA(newX, y, 1, h, colour);
		newX += 2;
	}
	while (newY < y + h){
		FillRGBA(x, newY, w, 1, colour);
		newY += 2;
	}
}

void CDrawManager::DrawOutlinedCircle(int x, int y, int radius, Color dwColor)
{
	ALX.pSurface->DrawSetColor(dwColor);
	ALX.pSurface->DrawOutlinedCircle(x, y, radius, radius * 10);
	ALX.pSurface->DrawSetColor(Color(0,0,0,255));
	ALX.pSurface->DrawOutlinedCircle(x, y, radius + 1, radius * 10);
	ALX.pSurface->DrawOutlinedCircle(x, y, radius - 1, radius * 10);
}
void CDrawManager::outline(int x, int y, int w, int h, DWORD color)
{
	ALX.pSurface->DrawSetColor(color);
	ALX.pSurface->DrawOutlinedRect(x, y, (x + w) + 1, (y + h) + 1);
}
/*void CDrawManager::UpdateEntityGlow(CBaseEntity* pEntity, float r, float g, float b, float a)
{
	typedef uintptr_t(__cdecl* fnGetGlowObjectManager)();
	fnGetGlowObjectManager pGetObjMngr = (fnGetGlowObjectManager)((int)GetModuleHandleA("client.dll") + 0x2B57F0 /*"C_CSPlayer::m_iv_angEyeAngles"*///);
	/*static uintptr_t pGlowObjMngr = pGetObjMngr();

	uint32_t glowIndex = *(uint32_t*)(pEntity + (ALX.pPlayerVariables->m_flFlashDuration + 0x18*/ /*0x1DB8));
	GlowObjectDefinition_t* pGlowObject = (GlowObjectDefinition_t*)(sizeof(GlowObjectDefinition_t)* glowIndex + *(uintptr_t*)pGlowObjMngr);

	pGlowObject->r = r;
	pGlowObject->g = g;
	pGlowObject->b = b;
	pGlowObject->a = a;
	pGlowObject->m_bRenderWhenOccluded = true;
	pGlowObject->m_bRenderWhenUnoccluded = true;
	//pGlowObject->m_bShouldGlow = true;
}*/

void CDrawManager::UpdateEntityGlow(CBaseEntity* pEntity, float r, float g, float b, float a)
{
	typedef uintptr_t(__cdecl* fnGetGlowObjectManager)();
	fnGetGlowObjectManager pGetObjMngr = (fnGetGlowObjectManager)((int)GetModuleHandleA("client.dll") + 0x2B57F0);
	static uintptr_t pGlowObjMngr = pGetObjMngr();

	uint32_t glowIndex = *(uint32_t*)(pEntity + 0x1DB8);
	GlowObjectDefinition_t* pGlowObject = (GlowObjectDefinition_t*)(sizeof(GlowObjectDefinition_t) * glowIndex + *(uintptr_t*)pGlowObjMngr);

	pGlowObject->r = r;
	pGlowObject->g = g;
	pGlowObject->b = b;
	pGlowObject->a = a;
	pGlowObject->m_bRenderWhenOccluded = true;
	pGlowObject->m_bRenderWhenUnoccluded = false;
}

void CDrawManager::DrawESPBox(int x, int y, int w, int h, Color colo)
{
	this->OutlineRect1(x - 1, y - 1, w + 1, h + 1, colo);
	this->OutlineRect1(x + 1, y + 1, w - 2, h - 2, colo);
}



#define colBlue Color(70,130,180,255)

void CDrawManager::DrawArmorBar(float x, float y, float w, float h, int r, int g, int b)
{
	Color colour = colBlue;
	FillRGBA(x, y, w, h, colour);
}

void CDrawManager::DrawHealthBarOutline(float x, float y, float w, float h)
{
	FillRGBA(x, y, w, h, Color(0, 0, 0, 255));
}


VOID CDrawManager::DrawHeader(INT x, INT y, INT w, INT r, INT g, INT b, INT HealthBarWidth)
{
	INT i = 0;
	INT xCoord = x;
	INT yCoord = y;

	// Male Male :)
	for (i = 0; i < 5; i++)
	{
		this->FillRGBA(x - i, y + i, w, 1, Color(0, 0, 0, 255));
		this->FillRGBA(x - i, y + i, HealthBarWidth + 2, 1, Color(r, g, b, 255));

		this->FillRGBA(x - 3, y + 3, HealthBarWidth + 2, 1, Color((INT)(r / 1.5f),
			(INT)(g / 1.5f), (INT)(b / 1.5f), 255));

		this->FillRGBA(x - 4, y + 4, HealthBarWidth + 2, 1, Color((INT)(r / 1.5f),
			(INT)(g / 1.5f), (INT)(b / 1.5f), 255));
	}

	// Oben
	this->FillRGBA(x, y, w, 1,Color(255, 255, 255, 255));

	// Unten
	this->FillRGBA((x + 1) - 5, y + 5, w, 1, Color(255, 255, 255, 255));

	for (i = 0; i < 5; i++)
	{
		// Schräg links
		this->FillRGBA(x, y, 1, 1, Color(255, 255, 255, 255));
		x--;
		y++;
	}

	x = xCoord;
	y = yCoord;

	for (i = 0; i < 5; i++)
	{
		// Schräg rechts
		if (i != 0)
			this->FillRGBA(x + w, y, 1, 1, Color(255, 255, 255, 255));

		x--;
		y++;
	}

}

void CDrawManager::DrawHealthBox(int x, int y, int r, int g, int b, int a, int CurHealth, int MaxHealth,int W)
{
	if (CurHealth == 0 || MaxHealth == 0)
		return;

	if (CurHealth > 100)
		CurHealth = 100;

	float mx = MaxHealth / 2;
	float wx = CurHealth / 2;

	if (mx == 0) return;

	int hpwidth = (CurHealth / MaxHealth);

	//x -= (mx / 2);

	this->DrawHeader(x, y, hpwidth + 2, r, g, b,W);
}

#include "DLLMain.h"
void CDrawManager::DrawPlayerBox(CBaseEntity *pEnt, Color dwColor, player_info_t pInfo,int iIndex)
{
	if (pEnt == NULL)
		return;

	CSetupPlayer __pBaseEntity = gPlayers[iIndex];

	CBaseEntity* pBaseEntity = __pBaseEntity.BaseEnt();

	if (pBaseEntity == NULL)
		return;

	Vector mon, nom;

	nom = pEnt->GetAbsOrigin();

	if (gPlayers[pEnt->GetIndex()].GetFlags() & FL_DUCKING)
	{
		mon = nom + Vector(0, 0, 50.f);
	}
	else
	{
		mon = nom + Vector(0, 0, 70.f);
	}

	Vector bot, top;

	if (WorldToScreen(nom, bot) && WorldToScreen(mon, top))
	{
		float h = (bot.y - top.y);

		float w = h / 4.f;

		if (ALX.pCvar->boxesp)
		{
			//OutlineRect1(top.x - w - 1, top.y - 1, w * 2 + 2, (bot.y - top.y + 2), Color(0,0,0,255));
			//OutlineRect1(top.x - w, top.y, w * 2, (bot.y - top.y), dwColor);
			BorderBoxOutlined(top.x - w, top.y, w * 2, (bot.y - top.y), dwColor, Color(0, 0, 0, 255));
		}

		float Width = w * 2;
		if (ALX.pCvar->hbarL)
		{
			FillRGBA(top.x - w, top.y - 25, Width, 10, Color(0, 0, 0, 100));
			FillRGBA(top.x - w, top.y - 25, Width * pBaseEntity->GetHealth(), 10, Color(50, 220, 50, 255));
		}
		
		if (ALX.pCvar->CornerBox)
		{
			this->BorderCornerBoxOutlined(top.x - w, top.y, w * 2, (bot.y - top.y), dwColor, Color(0, 0, 0, 255));
		}

		if (ALX.pCvar->Name && !ALX.pCvar->bbox)
		{
			//DrawString1(false, top.x - w, top.y - 15, Color(255, 255, 255, 255), "%s", pInfo.name);
			DrawStringM(AFont, true, top.x, top.y - 12, Color(255,255,255,255), pInfo.name);
		}

		if (ALX.pCvar->Weapons && !ALX.pCvar->bbox)
		{

			if (strstr(__pBaseEntity.GetActiveWeapon()->GetClientClass()->GetName(), "CWeapon"))
				ALX.pDrawManager->DrawStringM(AFont,false, top.x + (w) + 5, top.y + (h / 2) , Color(255,255,255,255), string(__pBaseEntity.GetActiveWeapon()->GetClientClass()->GetName()).substr(7).c_str());
			else if (streql(__pBaseEntity.GetActiveWeapon()->GetClientClass()->GetName(), "CAK47"))
				ALX.pDrawManager->DrawStringM(AFont,false, top.x + (w) + 5, top.y + (h / 2), Color(255,255,255,255), "AK47");
			else if (streql(__pBaseEntity.GetActiveWeapon()->GetClientClass()->GetName(), "CDEagle"))
				ALX.pDrawManager->DrawStringM(AFont,false, top.x + (w) + 5, top.y + (h / 2) , Color(255,255,255,255), "Deagle");
			else if (streql(__pBaseEntity.GetActiveWeapon()->GetClientClass()->GetName(), "CKnife"))
				ALX.pDrawManager->DrawStringM(AFont,false, top.x + (w) + 5, top.y + (h / 2), Color(255,255,255,255), "Knife");
			else if (streql(__pBaseEntity.GetActiveWeapon()->GetClientClass()->GetName(), "CC4"))
				ALX.pDrawManager->DrawStringM(AFont,false, top.x + (w) + 5, top.y + (h / 2), Color(255,255,255,255), "C4");
		}
	
	
	}

}

void CDrawManager::DrawPlayerHealthBox(CBaseEntity *pEnt, Color dwColor, int health, int maxHealth){

	if (pEnt == NULL)
		return;

	Vector mon, nom;

	nom = pEnt->GetAbsOrigin();

	if (gPlayers[pEnt->GetIndex()].GetFlags() & FL_DUCKING)
	{
		mon = nom + Vector(0, 0, 50.f);
	}
	else
	{
		mon = nom + Vector(0, 0, 70.f);
	}

	Vector bot, top;

	if (WorldToScreen(nom, bot) && WorldToScreen(mon, top))
	{
		float h = floor(bot.y - top.y);

		float w = h / 4.f;

		Color dwHealth;



		dwHealth = Color(255, 255, 255, 255); //white


		if (maxHealth*.5<health){
			dwHealth = Color(255 - (health / maxHealth * 255 * 2), 255, 25, 255);
		}
		else{
			dwHealth = Color(255, 0 + (health / maxHealth * 255 * 2), 25, 255);
		}



		top.x -= floor(w + 6);
		DrawRect1(floor(top.x), floor(top.y), 4, h,Color(0, 0, 0, 255)); // Border
		if (maxHealth<health){
			dwHealth = Color(0, 0, 255, 255);
			health = maxHealth;
		}
		int hw = floor((((h)* health) / maxHealth)); // Percentage I think?
		DrawRect1(floor(top.x) + 1, floor(top.y + (h - hw)) + 1, 2, hw - 2, dwHealth);



	}

}


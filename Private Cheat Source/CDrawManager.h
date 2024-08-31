#pragma once
//===================================================================================
#include "Panels.h"
#include "Player Manager.h"

#define RED(COLORCODE)	((int) ( COLORCODE >> 24) )
#define BLUE(COLORCODE)	((int) ( COLORCODE >> 8 ) & 0xFF )
#define GREEN(COLORCODE)	((int) ( COLORCODE >> 16 ) & 0xFF )
#define ALPHA(COLORCODE)	((int) COLORCODE & 0xFF )
#define COLORCODE(r,g,b,a)((DWORD)((((r)&0xff)<<24)|(((g)&0xff)<<16)|(((b)&0xff)<<8)|((a)&0xff)))

enum GradientType
{
	GRADIENT_HORIZONAL_FILL,
	GRADIENT_VERTICAL_FILL,
};
//===================================================================================
class CDrawManager
{
public:
	void Initialize( );
	void DrawString( bool HUDFont, int x, int y, DWORD dwColor, const wchar_t *pszText);
	void DrawString( bool HUDFont, int x, int y, DWORD dwColor, const char *pszText, ... );
	byte GetESPHeight( );
	byte GetHUDHeight( );
	int GetPixelTextSize ( const char *pszText );
	VOID DrawHeader(INT x, INT y, INT w, INT r, INT g, INT b, INT HealthBarWidth);
	void DrawCorneredBox(int x, int y, int w, int h, Color colour);
	void DrawOC(int x, int y, int w, int h, Color colour);
	void BorderCornerBoxOutlined(int x, int y, int w, int h, Color dwColor, Color Outline);
	void DrawStringM1(int FONT, bool bCenter, float x, float y, Color c, const char *fmt, ...);
	void FillRGBA2(int x, int y, int w, int h, Color colour, Color color);
	void DrawHealthBox(int x, int y, int r, int g, int b, int a, int CurHealth, int MaxHealth,int W);
	int GetPixelTextSize ( wchar_t *pszText );
	void DrawPlayerHealthBox(CBaseEntity *pEnt, Color dwColor, int health, int maxHealth);
	void DrawRect1(int x, int y, int w, int h, Color dwColor);
	void DrawBox( Vector vOrigin, int r, int g, int b, int alpha, int box_width, int radius );
	void DrawRect( int x, int y, int w, int h, DWORD dwColor );
	void OutlineRect( int x, int y, int w, int h, DWORD dwColor );
	void DrawBox3D(Vector head, Vector bottom, Vector angles, Color color);
	void DrawLine2D(Vector a, Vector b, Color dat);
	void DrawStringZ(bool HUDFont, int x, int y, Color dwColor, const char *pszText, ...);
	void DrawStringZ(bool HUDFont, int x, int y, Color dwColor, const wchar_t *pszText);
	void TextW(bool cent, int font, int x, int y, Color color, wchar_t *pszString);
	void DrawStringM(int FONT, bool bCenter, int x, int y, Color c, const char *fmt, ...);
	void OutlineRect1(int x, int y, int w, int h, Color dwColor);
	void GradientFunc(int x, int y, int w, int h, Color dwColor);
	void DrawLine(int x, int y, int x2, int y2, DWORD dwColor);
	void DrawRhombus(int x, int y, int w, int h, Color dwColor);
	void DrawDiamond(int x, int y, int w, int h, Color dwColor);
	bool WorldToScreen( Vector &vOrigin, Vector &vScreen );
	bool ScreenTransform( const Vector &point, Vector &screen );
	void DrawString1(bool HUDFont, int x, int y, Color dwColor, const char *pszText, ...);
	void DrawLine1(int x, int y, int x2, int y2, Color dwColor);
	void DrawOutlinedCircle(int x, int y, int radius, Color dwColor);
	void DrawPlayerBox( CBaseEntity *pEnt, Color dwColor,player_info_t pInfo,int iIndex);
	void DrawPlayerBox1(CBaseEntity *pEnt, int w, int h, Color dwColor, int iIndex);
	void DrawChickenBox(CBaseEntity *pEnt, Color dwColor);
	void BorderBoxOutlined(int x, int y, int w, int h, Color dwColor, Color Outline);
	void DrawChickenBox1(CBaseEntity *pEnt, Color dwColor, int iIndex);
	bool GetBonePosition(CBaseEntity* pPlayer, Vector& Hitbox, int Bone);
	Vector GetBonePosition2(CBaseEntity* target, int iBone);
	Vector GetEyePosition(CBaseEntity* pEntity);
	void DrawRhombusFill(int x, int y, int w, int h, Color dwColor);
	void DrawHealthBar(int x, int y, float health, int w, int h, Color Draw);
	void FillRGBA(int x, int y, int w, int h, Color colour);
	void FillRGBA1(int x, int y, int w, int h, DWORD dwColor);
	void drawGrid(int x, int y, int w, int h, Color colour);
	void outlinedCircle(int x, int y, int radius, DWORD dwColor);
	void DrawCrosshair(int x, int y, Color color);
	void HBAR(int x, int y, int w, int h, float hp,Color color);
	void DrawGradient(int x, int y, int w, int h, GradientType gType, Color from, Color to);
	void outline(int x, int y, int w, int h, DWORD color);
	void UpdateEntityGlow(CBaseEntity* pEntity, float r, float g, float b, float a);
	void blackBorder(int x, int y, int w, int h);
	void DrawHealthBar2(float x, float y, float w, float h, Color color);
	void DrawArmorBar(float x, float y, float w, float h, int r, int g, int b);
	void DrawESPBox(int x, int y, int w, int h, Color colo);
	void DrawHealthBarOutline(float x, float y, float w, float h);
	void MagicCross();


private:
	unsigned long m_ESPFont;
	unsigned long m_HUDFont;
};

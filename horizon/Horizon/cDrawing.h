#pragma once

#include "sdk.h"
#include "Panels.h"

#include "public\\mathlib\\vector.h" // For some fucking reason it wont include it from sdk.h, pissed me off.

#define RED(COLORCODE)			((int) ( COLORCODE >> 24) )
#define BLUE(COLORCODE)			((int) ( COLORCODE >> 8 ) & 0xFF )
#define GREEN(COLORCODE)		((int) ( COLORCODE >> 16 ) & 0xFF )
#define ALPHA(COLORCODE)		((int) COLORCODE & 0xFF )
#define COLORCODE(r,g,b,a)		((DWORD)((((r)&0xff)<<24)|(((g)&0xff)<<16)|(((b)&0xff)<<8)|((a)&0xff)))
#define RGBA(colorcode)			RED(colorcode), GREEN(colorcode), BLUE(colorcode), ALPHA(colorcode)

class CDrawing
{
public:
	void Init();
	void SetFont(const char* facename, int tall, int weight, int falgs);
	void DrawString(int x, int y, DWORD col, const char* pszText, ...);
	void DrawString_w(int x, int y, DWORD col, const wchar_t* pszText);
	void DrawLine(int x0, int y0, int x1, int y1, DWORD Color);
	void FillRGBA(int x, int y, int w, int h, DWORD dwColor);
	bool WorldToScreen(CONST Vector &origin, OUT Vector &screen);
	bool ScreenTransform(CONST Vector& point, OUT Vector& screen);
	void DrawBox(int x, int y, int x2, int y2, DWORD Color);
	void DrawHealthBar(int x, int y, float health, int w, int h, DWORD Draw);
	//void DrawPlayerBox(CBaseEntity *pEnt, DWORD dwColor);
	void DrawBoxBlackBackground(int x, int y, int width, int height, DWORD dwColor);

private:
	unsigned long m_pFont;
};

extern CDrawing gDrawing;

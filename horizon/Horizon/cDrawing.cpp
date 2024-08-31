#include "cDrawing.h"

CDrawing gDrawing;

void CDrawing::Init()
{
	g_pEngine->GetScreenSize(gScreenSize.m_iWidth, gScreenSize.m_iHeight);

	m_pFont = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(m_pFont, "Arial", 14, 150, 0, 0, 0x200);
}

void CDrawing::SetFont(const char* facename, int tall, int weight, int flags)
{
	g_pSurface->SetFontGlyphSet(m_pFont, facename, tall, weight, 0, 0, flags);
}

void CDrawing::DrawString(int x, int y, DWORD col, const char* pszText, ...)
{
	if (pszText == NULL)
		return;

	va_list va_alist;
	char buf[1024];
	va_start(va_alist, pszText);
	_vsnprintf(buf, sizeof(buf), pszText, va_alist);
	va_end(va_alist);
	wchar_t wbuf[1024];
	MultiByteToWideChar(CP_UTF8, 0, buf, 256, wbuf, 256);
	g_pSurface->DrawSetTextFont(m_pFont);
	g_pSurface->DrawSetTextColor(RED(col), GREEN(col), BLUE(col), ALPHA(col));
	g_pSurface->DrawSetTextPos(x, y);
	g_pSurface->DrawPrintText(wbuf, wcslen(wbuf));
}

void CDrawing::DrawString_w(int x, int y, DWORD col, const wchar_t* pszText)
{
	if (pszText == NULL)
		return;

	g_pSurface->DrawSetTextPos(x, y);
	g_pSurface->DrawSetTextFont(m_pFont);
	g_pSurface->DrawSetTextColor(RED(col), GREEN(col), BLUE(col), ALPHA(col));
	g_pSurface->DrawPrintText(pszText, wcslen(pszText));
}

void CDrawing::DrawLine(int x0, int y0, int x1, int y1, DWORD Color)
{
	g_pSurface->DrawSetColor(RED(Color), BLUE(Color), GREEN(Color), ALPHA(Color));
	g_pSurface->DrawLine(x0, y0, x1, y1);
}

void CDrawing::FillRGBA(int x, int y, int w, int h, DWORD dwColor)
{
	g_pSurface->DrawSetColor(RED(dwColor), GREEN(dwColor), BLUE(dwColor), ALPHA(dwColor));
	g_pSurface->DrawFilledRect(x, y, x + w, y + h);
}

bool CDrawing::ScreenTransform(CONST Vector& point, OUT Vector& screen)
{
	const VMatrix& worldToScreen = g_pEngine->WorldToScreenMatrix();
	screen.x = worldToScreen.m[0][0] * point.x + worldToScreen.m[0][1] * point.y + worldToScreen.m[0][2] * point.z + worldToScreen.m[0][3];
	screen.y = worldToScreen.m[1][0] * point.x + worldToScreen.m[1][1] * point.y + worldToScreen.m[1][2] * point.z + worldToScreen.m[1][3];

	FLOAT w;
	w = worldToScreen.m[3][0] * point.x + worldToScreen.m[3][1] * point.y + worldToScreen.m[3][2] * point.z + worldToScreen.m[3][3];
	screen.z = 0.0f;

	BOOL behind = FALSE;
	if (w < 0.001f)
	{
		behind = TRUE;
		screen.x *= 100000;
		screen.y *= 100000;
	}
	else
	{
		FLOAT invw = 1.0f / w;
		screen.x *= invw;
		screen.y *= invw;
	}

	return behind;
}

bool CDrawing::WorldToScreen(CONST Vector &origin, OUT Vector &screen)
{
	BOOL bRet = FALSE;

	if (!ScreenTransform(origin, screen))
	{
		INT width, height;
		g_pEngine->GetScreenSize(width, height);

		float fScreenX = width / 2;
		float fScreenY = height / 2;

		fScreenX += 0.5f * screen.x * width + 0.5f;
		fScreenY -= 0.5f * screen.y * height + 0.5f;

		screen.x = fScreenX;
		screen.y = fScreenY;

		bRet = TRUE;
	}

	return bRet;
}

void CDrawing::DrawBox(int x, int y, int x2, int y2, DWORD Color)
{
	gDrawing.FillRGBA(x - 1, y - 1, x2 + 2, 1, Color);
	gDrawing.FillRGBA(x - 1, y, 1, y2 - 1, Color);
	gDrawing.FillRGBA(x + x2, y, 1, y2 - 1, Color);
	gDrawing.FillRGBA(x - 1, y + y2 - 1, x2 + 2, 1, Color);
}

void CDrawing::DrawBoxBlackBackground(int x, int y, int width, int height, DWORD dwColor)
{
	gDrawing.FillRGBA(x, y + height - 1, width + 1, 1 + 2, COLORCODE(0, 0, 0, 255));
	gDrawing.FillRGBA(x - 1 - 1, y - 1, 1 + 2, height + 2, COLORCODE(0, 0, 0, 255));
	gDrawing.FillRGBA(x, y - 1 - 1, width + 1, 1 + 2, COLORCODE(0, 0, 0, 255));
	gDrawing.FillRGBA(x + width + 1 - 1, y - 1, 1 + 2, height + 2, COLORCODE(0, 0, 0, 255));

	gDrawing.FillRGBA(x, y + height, width + 1, 1, dwColor);
	gDrawing.FillRGBA(x - 1, y - 1, 1, height + 2, dwColor);
	gDrawing.FillRGBA(x, y - 1, width + 1, 1, dwColor);
	gDrawing.FillRGBA(x + width + 1, y - 1, 1, height + 2, dwColor);
}

void CDrawing::DrawHealthBar(int x, int y, float health, int w, int h, DWORD color)
{
	x -= w / 2;
	y -= h / 2;
	gDrawing.FillRGBA(x, y, w, h, COLORCODE(0, 0, 0, 255));
	UINT hw = (UINT)(((h - 2) * health) / 100);
	gDrawing.FillRGBA(x + 1, y + 1, w - 1, hw, color);
}
class CVisuals
{
public:
	void DrawString(HFont font, int x, int y, Color color, const char* msg, ...);
	void DrawStringA(HFont font, int x, int y, Color color, const char* msg, ...);
	void DrawBox(int x, int y, int w, int h, Color Col);
	void DrawBoxOutline(int x, int y, int w, int h, Color Col);
	void DrawLine(int x, int y, int x2, int y2, Color Col);
	void DrawLineOutline(int x, int y, int x2, int y2, Color Col);

}; CVisuals Visuals;

void CVisuals::DrawString(HFont font, int x, int y, Color color, const char* msg, ...)
{

	va_list va_alist;
	char buf[1024];
	va_start(va_alist, msg);
	_vsnprintf(buf, sizeof(buf), msg, va_alist);
	va_end(va_alist);
	wchar_t wbuf[1024];
	MultiByteToWideChar(CP_UTF8, 0, buf, 256, wbuf, 256);

	int r = 255, g = 255, b = 255, a = 255;
	color.GetColor(r, g, b, a);

	InterfaceManager.Surface->SDKSurface()->DrawSetTextFont(font);
	InterfaceManager.Surface->SDKSurface()->DrawSetTextColor(r, g, b, a);
	InterfaceManager.Surface->SDKSurface()->DrawSetTextPos(x, y);
	InterfaceManager.Surface->SDKSurface()->DrawPrintText(wbuf, wcslen(wbuf));

}

void CVisuals::DrawStringA(HFont font, int x, int y, Color color, const char* msg, ...)
{

	va_list va_alist;
	char buf[1024];
	va_start(va_alist, msg);
	_vsnprintf(buf, sizeof(buf), msg, va_alist);
	va_end(va_alist);
	wchar_t wbuf[1024];
	MultiByteToWideChar(CP_UTF8, 0, buf, 256, wbuf, 256);

	int r = 255, g = 255, b = 255, a = 255;
	color.GetColor(r, g, b, a);

	int Wid, Hit;
	InterfaceManager.Surface->GetTextSize(font, wbuf, Wid, Hit);

	InterfaceManager.Surface->SDKSurface()->DrawSetTextFont(font);
	InterfaceManager.Surface->SDKSurface()->DrawSetTextColor(r, g, b, a);
	InterfaceManager.Surface->SDKSurface()->DrawSetTextPos(x - Wid*.5, y - Hit*.5);
	InterfaceManager.Surface->SDKSurface()->DrawPrintText(wbuf, wcslen(wbuf));

}

void CVisuals::DrawBox(int x, int y, int w, int h, Color Col)
{

	int r, g, b, a;
	Col.GetColor(r, g, b, a);

	InterfaceManager.Surface->SDKSurface()->DrawSetColor(r, g, b, a);
	InterfaceManager.Surface->SDKSurface()->DrawFilledRect(x, y, x + w, y + h);

}

void CVisuals::DrawBoxOutline(int x, int y, int w, int h, Color Col)
{

	int r, g, b, a;
	Col.GetColor(r, g, b, a);

	InterfaceManager.Surface->SDKSurface()->DrawSetColor(r, g, b, a);
	InterfaceManager.Surface->SDKSurface()->DrawOutlinedRect(x, y, x + w, y + h);

}

void CVisuals::DrawLine(int x, int y, int x2, int y2, Color Col)
{

	int r, g, b, a;
	Col.GetColor(r, g, b, a);

	InterfaceManager.Surface->SDKSurface()->DrawSetColor(r, g, b, a);
	InterfaceManager.Surface->SDKSurface()->DrawLine(x, y, x2, y2);

}

void CVisuals::DrawLineOutline(int x, int y, int x2, int y2, Color Col)
{

	int r, g, b, a;
	Col.GetColor(r, g, b, a);

	InterfaceManager.Surface->SDKSurface()->DrawSetColor(Col);

	InterfaceManager.Surface->SDKSurface()->DrawLine(x, y + 1, x2, y2 + 1);
	InterfaceManager.Surface->SDKSurface()->DrawLine(x, y - 1, x2, y2 - 1);

}

bool ScreenTransform(const Vector &point, Vector &screen)
{
	float w;
	const VMatrix &worldToScreen = InterfaceManager.Engine->WorldToScreenMatrix();

	screen.x = worldToScreen[0][0] * point[0] + worldToScreen[0][1] * point[1] + worldToScreen[0][2] * point[2] + worldToScreen[0][3];
	screen.y = worldToScreen[1][0] * point[0] + worldToScreen[1][1] * point[1] + worldToScreen[1][2] * point[2] + worldToScreen[1][3];
	w = worldToScreen[3][0] * point[0] + worldToScreen[3][1] * point[1] + worldToScreen[3][2] * point[2] + worldToScreen[3][3];
	screen.z = 0.0f;

	bool behind = false;

	if (w < 0.001f)
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

void GetWorldSpaceCenter(CBaseEntity* pBaseEntity, Vector& WorldSpaceCenter)
{
	Vector Min, Max;
	pBaseEntity->GetRenderBounds(Min, Max);
	WorldSpaceCenter = pBaseEntity->GetAbsOrigin();
	WorldSpaceCenter.z += (Min.z + Max.z) / 2.0f;
}

bool WorldToScreen(const Vector &origin, Vector &screen)
{
	if (!ScreenTransform(origin, screen))
	{
		int ScreenWidth, ScreenHeight;
		InterfaceManager.Engine->GetScreenSize(ScreenWidth, ScreenHeight);
		float x = ScreenWidth / 2;
		float y = ScreenHeight / 2;
		x += 0.5 * screen.x * ScreenWidth + 0.5;
		y -= 0.5 * screen.y * ScreenHeight + 0.5;
		screen.x = x;
		screen.y = y;
		return true;
	}

	return false;
}
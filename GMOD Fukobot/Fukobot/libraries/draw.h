class draw{
public:
	void DrawString(HFont, int, int, Color, const char*, ...);
	void DrawStringA(HFont, int, int, Color, const char*, ...);
	void CreateFonts();

	void DrawBox(int, int, int, int, Color);
	void DrawBoxOutline(int, int, int, int, Color);
	void DrawLine(int, int, int, int, Color);
	void DrawLineOutline(int, int, int, int, Color);
}; draw *Draw = new draw;

void draw::DrawString(HFont font, int x, int y, Color color, const char* msg, ...){

	// Multibyte to wide char conversion taken from Horizon until I learn how to do it myself
	va_list va_alist;
	char buf[1024];
	va_start(va_alist, msg);
	_vsnprintf(buf, sizeof(buf), msg, va_alist);
	va_end(va_alist);
	wchar_t wbuf[1024];
	MultiByteToWideChar(CP_UTF8, 0, buf, 256, wbuf, 256);

	int r = 255, g = 255, b = 255, a = 255;
	color.GetColor(r, g, b, a);

	Surface->DrawSetTextFont(font);
	Surface->DrawSetTextColor(r, g, b, a);
	Surface->DrawSetTextPos(x, y);
	Surface->DrawPrintText(wbuf, wcslen(wbuf));

}

void draw::DrawStringA(HFont font, int x, int y, Color color, const char* msg, ...){

	// Multibyte to wide char conversion taken from Horizon until I learn how to do it myself
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
	GetTextSize(font, wbuf, Wid, Hit);

	Surface->DrawSetTextFont(font);
	Surface->DrawSetTextColor(r, g, b, a);
	Surface->DrawSetTextPos(x - Wid*.5, y - Hit*.5);
	Surface->DrawPrintText(wbuf, wcslen(wbuf));

}


bool FontsValid = false;
void draw::CreateFonts()
{

	if (FontsValid)
		return;

	FukoFont = CreateFont();
	SetFontGlyphSet(FukoFont, "FixedSys", 12, 150, 0, 0, 0x200);

	FukoFontMenu = CreateFont();
	SetFontGlyphSet(FukoFontMenu, "Arial", 16, 550, 0, 0, 0x010);

	FukoFontMenuTitle = CreateFont();
	SetFontGlyphSet(FukoFontMenuTitle, "Arial", 20, 400, 0, 0, 0x010);

	FontsValid = true;
}

void draw::DrawBox(int x, int y, int w, int h, Color Col)
{

	int r, g, b, a;
	Col.GetColor(r, g, b, a);

	Surface->DrawSetColor(r, g, b, a);
	Surface->DrawFilledRect(x, y, x + w, y + h);

}

void draw::DrawBoxOutline(int x, int y, int w, int h, Color Col)
{

	int r, g, b, a;
	Col.GetColor(r, g, b, a);

	Surface->DrawSetColor(r, g, b, a);
	Surface->DrawOutlinedRect(x, y, x + w, y + h);

}

void draw::DrawLine(int x, int y, int x2, int y2, Color Col)
{

	int r, g, b, a;
	Col.GetColor(r, g, b, a);

	Surface->DrawSetColor(r, g, b, a);
	Surface->DrawLine(x, y, x2, y2);

}

void draw::DrawLineOutline(int x, int y, int x2, int y2, Color Col)
{

	int r, g, b, a;
	Col.GetColor(r, g, b, a);

	Surface->DrawSetColor(Col);

	Surface->DrawLine(x, y + 1, x2, y2 + 1);
	Surface->DrawLine(x, y - 1, x2, y2 - 1);

	// TODO: Fix this retarded shit
	//Surface->DrawLine(x - 1, y - 1, x - 1, y2 + 1);
	//Surface->DrawLine(x2 - 1, y - 1, x2 - 1, y2 + 1);

}

bool ScreenTransform(const Vector &point, Vector &screen)
{
	float w;
	const VMatrix &worldToScreen = Engine->WorldToScreenMatrix();

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
		Engine->GetScreenSize(ScreenWidth, ScreenHeight);
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
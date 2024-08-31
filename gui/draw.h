#pragma once

#include "../sdk.h"

namespace draw
{
	void SetColor(const Color& color)
	{
		surface->SetDrawColor(color);
	}
	void FilledRect(int x, int y, int w, int h)
	{
		surface->DrawFilledRect(x, y, w, h);
	}
	void OutlinedRect(int x, int y, int w, int h)
	{
		surface->DrawOutlinedRect(x, y, w, h);
	}
	void SetTextColor(const Color& color)
	{
		surface->SetTextColor(color);
	}
	// trash function below
	void Text(unsigned long font, Color &color, bool centerx, bool centery, bool shadow, int x, int y, const char* text, ...)
	{
		wchar_t wstring[128];
		char cstring[256];

		va_list	list;
		va_start(list, text);
		vsprintf_s(cstring, text, list);
		va_end(list);

		MultiByteToWideChar(CP_UTF8, 0, cstring, -1, wstring, 128);

		int wide, tall;
		surface->GetTextSize(font, wstring, wide, tall);

		if (centerx)
			x -= wide / 2;

		if (centery)
			y -= tall / 2;

		surface->SetFont(font);

		if (shadow)
		{
			surface->SetTextColor(Color(0, 0, 0, 64));
			surface->SetTextPos(x - 1, y + 1);
			surface->DrawText(wstring, wcslen(wstring));
		}

		surface->SetTextColor(color);
		surface->SetTextPos(x, y);
		surface->DrawText(wstring, wcslen(wstring));
	}
}
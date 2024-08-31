#pragma once

#include "gui.h"

namespace render
{
	extern HWND handle;
}

namespace util
{
	inline bool IsWindowInFocus()
	{
		return (render::handle == GetFocus());
	}
	void GetMousePosition(int& x, int& y)
	{
		POINT pos;
		GetCursorPos(&pos);
		ScreenToClient(render::handle, &pos);

		x = pos.x;
		y = pos.y;
	}
	bool IsMouseWithin(int x, int y, int w, int h)
	{
		int mx, my;
		GetMousePosition(mx, my);

		return (mx >= x && mx <= x + w && my >= y && my <= y + h);
	}
}
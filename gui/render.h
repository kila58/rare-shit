#pragma once

#include "gui.h"

namespace render
{
	HWND handle = NULL;
	WNDPROC oldproc = NULL;

	long __stdcall WindowProc(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		if (msg == WM_KEYDOWN && wparam == VK_INSERT)
		{
			menu.open = !menu.open;

			logic::SetVisible(menu.open);

			engine->ClientCmd_Unrestricted(menu.open ? "cl_mouseenable 0" : "cl_mouseenable 1");
		}

		if (menu.open)
		{
			switch (msg)
			{
			case WM_ACTIVATE: case WM_KILLFOCUS:
			{
				if ((msg == WM_ACTIVATE && wparam == WA_INACTIVE) || (msg == WM_KILLFOCUS))
					logic::SetDragging(false);

				break;
			}
			case WM_LBUTTONDOWN:
			{
				logic::SetDragging(true);

				break;
			}

			case WM_LBUTTONUP:
			{
				logic::SetDragging(false), logic::HandleClick();

				break;
			}
			}

			static HCURSOR cursor = LoadCursor(NULL, IDC_ARROW);

			SetCursor(cursor);
			ShowCursor(true);
		}

		return CallWindowProc(oldproc, handle, msg, wparam, lparam);
	}

	void Init()
	{
		if (!handle)
			handle = (HWND)FindWindow("Valve001", NULL);

		if (!oldproc && handle)
			//oldproc = (WNDPROC)SetWindowLong(handle, GWL_WNDPROC, (LONG)WindowProc);
			oldproc = (WNDPROC)SetWindowLongPtr(handle, GWL_WNDPROC, (LONG)WindowProc);
	}

	void Invoke()
	{
		external::EnableInput(!menu.open);

		for (auto& frame : gui::frames)
		{
			frame.Think();
			frame.Draw();
		}
	}
}
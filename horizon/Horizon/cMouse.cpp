#include <windowsx.h>
#include "cMouse.h"
#include "cMenu.h"

cMouse gMouse;
int mouse_y, mouse_x;
/**********************************************************************************/
bool mouse1pressed = false;
bool mouse1released = false;
bool mouse2pressed = false;
bool mouse2released = false;

#define CHEAT_BLACK COLORCODE(0, 0, 0, 255)
#define CHEAT_RED COLORCODE(255, 0, 0, 255)

void cMouse::draw(){
	if (!active || hide)
		return;
	gDrawing.FillRGBA(mousePos[0] - 1, mousePos[1] - 1, 1, 12, CHEAT_BLACK);
	gDrawing.FillRGBA(mousePos[0], mousePos[1] - 1, 1, 1, CHEAT_BLACK);
	gDrawing.FillRGBA(mousePos[0], mousePos[1], 1, 10, CHEAT_RED);
	gDrawing.FillRGBA(mousePos[0], mousePos[1] + 10, 1, 1, CHEAT_BLACK);
	gDrawing.FillRGBA(mousePos[0] + 1, mousePos[1], 1, 1, CHEAT_BLACK);
	gDrawing.FillRGBA(mousePos[0] + 1, mousePos[1] + 1, 1, 8, CHEAT_RED);
	gDrawing.FillRGBA(mousePos[0] + 1, mousePos[1] + 9, 1, 1, CHEAT_BLACK);
	gDrawing.FillRGBA(mousePos[0] + 2, mousePos[1] + 1, 1, 1, CHEAT_BLACK);
	gDrawing.FillRGBA(mousePos[0] + 2, mousePos[1] + 2, 1, 6, CHEAT_RED);
	gDrawing.FillRGBA(mousePos[0] + 2, mousePos[1] + 8, 1, 1, CHEAT_BLACK);
	gDrawing.FillRGBA(mousePos[0] + 3, mousePos[1] + 2, 1, 1, CHEAT_BLACK);
	gDrawing.FillRGBA(mousePos[0] + 3, mousePos[1] + 3, 1, 6, CHEAT_RED);
	gDrawing.FillRGBA(mousePos[0] + 3, mousePos[1] + 9, 1, 2, CHEAT_BLACK);
	gDrawing.FillRGBA(mousePos[0] + 4, mousePos[1] + 3, 1, 1, CHEAT_BLACK);
	gDrawing.FillRGBA(mousePos[0] + 4, mousePos[1] + 4, 1, 7, CHEAT_RED);
	gDrawing.FillRGBA(mousePos[0] + 4, mousePos[1] + 11, 1, 2, CHEAT_BLACK);
	gDrawing.FillRGBA(mousePos[0] + 5, mousePos[1] + 4, 1, 1, CHEAT_BLACK);
	gDrawing.FillRGBA(mousePos[0] + 5, mousePos[1] + 5, 1, 2, CHEAT_RED);
	gDrawing.FillRGBA(mousePos[0] + 5, mousePos[1] + 7, 1, 2, CHEAT_BLACK);
	gDrawing.FillRGBA(mousePos[0] + 5, mousePos[1] + 9, 1, 4, CHEAT_RED);
	gDrawing.FillRGBA(mousePos[0] + 5, mousePos[1] + 13, 1, 1, CHEAT_BLACK);
	gDrawing.FillRGBA(mousePos[0] + 6, mousePos[1] + 5, 1, 1, CHEAT_BLACK);
	gDrawing.FillRGBA(mousePos[0] + 6, mousePos[1] + 6, 1, 1, CHEAT_RED);
	gDrawing.FillRGBA(mousePos[0] + 6, mousePos[1] + 7, 1, 1, CHEAT_BLACK);
	gDrawing.FillRGBA(mousePos[0] + 6, mousePos[1] + 9, 1, 2, CHEAT_RED);
	gDrawing.FillRGBA(mousePos[0] + 6, mousePos[1] + 11, 1, 2, CHEAT_RED);
	gDrawing.FillRGBA(mousePos[0] + 6, mousePos[1] + 13, 1, 1, CHEAT_BLACK);
	gDrawing.FillRGBA(mousePos[0] + 7, mousePos[1] + 6, 1, 2, CHEAT_BLACK);
	gDrawing.FillRGBA(mousePos[0] + 7, mousePos[1] + 11, 1, 2, CHEAT_BLACK);
}

bool cMouse::peekMessage(UINT uMsg, WPARAM wParam, LPARAM lParam){
	if (!active)
		return false;
	switch (uMsg){
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
		return true;
	case WM_MOUSEMOVE:
		mousePos[0] = GET_X_LPARAM(lParam);
		mousePos[1] = GET_Y_LPARAM(lParam);
		return true;
	}
	return false;
}
void cMouse::ClickHandler()
{
	if ((GetAsyncKeyState(VK_LBUTTON)))
	{
		mouse1pressed = true;
	}
	else if (!(GetAsyncKeyState(VK_LBUTTON)))
	{
		if (mouse1pressed)
			mouse1released = true;
		else
		{
			mouse1released = false;
		}
		mouse1pressed = false;
	}

	if ((GetAsyncKeyState(VK_RBUTTON)))
	{
		mouse2pressed = true;
	}
	else if (!(GetAsyncKeyState(VK_RBUTTON)))
	{
		if (mouse2pressed)
			mouse2released = true;
		else
		{
			mouse2released = false;
		}
		mouse2pressed = false;
	}
}
/**********************************************************************************/
bool cMouse::Leftclick(int x, int y, int w, int h)
{
	if (mouse1pressed &&
		mouse_x > x  &&
		w + x > mouse_x &&
		mouse_y > y  &&
		h + y > mouse_y)
		return true;
	else
		return false;
}
/**********************************************************************************/
bool cMouse::OneLeftclick(int x, int y, int w, int h)
{
	if (mouse1released &&
		mouse_x > x  &&
		w + x > mouse_x&&
		mouse_y > y  &&
		h + y > mouse_y)
		return true;
	else
		return false;
}
/**********************************************************************************/
bool cMouse::Rightclick(int x, int y, int w, int h)
{
	if (mouse2pressed &&
		mouse_x > x  &&
		w + x > mouse_x&&
		mouse_y > y  &&
		h + y > mouse_y)
		return true;
	else
		return false;
}
/**********************************************************************************/
bool cMouse::OneRightclick(int x, int y, int w, int h)
{
	if (mouse2released &&
		mouse_x > x  &&
		w + x > mouse_x&&
		mouse_y > y  &&
		h + y > mouse_y)
		return true;
	else
		return false;
}
/**********************************************************************************/
bool cMouse::IsOver(int x, int y, int w, int h)
{
	if (mouse_x > x		&&
		mouse_x < x + w	&&
		mouse_y > y		&&
		mouse_y < y + h)
		return true;
	else
		return false;
}

void cMouse::buttons()
{
	mouse1Press = GetAsyncKeyState(VK_LBUTTON) & 1;
	mouse1Hold = GetAsyncKeyState(VK_LBUTTON);
	mouse2Press = GetAsyncKeyState(VK_RBUTTON) & 1;
	mouse2Hold = GetAsyncKeyState(VK_RBUTTON);
}

bool cMouse::check(bool key, int x, int y, int w, int h){
	return(key && mousePos[0] > x && w + x > mousePos[0] && mousePos[1] > y && h + y > mousePos[1]);
}

bool cMouse::check(int x, int y, int w, int h){
	return(mousePos[0] > x && w + x > mousePos[0] && mousePos[1] > y && h + y > mousePos[1]);
}

bool cMouse::IsMouseOnTop(int x, int y, int w, int h)
{
	if ((mousePos[0] > x) && (mousePos[0] < x + w) && (mousePos[1] > y) && (mousePos[1] < y + h))
		return true;
	return false;
}
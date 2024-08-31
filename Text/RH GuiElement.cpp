#include "GUIElement.h"

void CGUIElement::LogoUp(int x, int y)
{
	FILLRGBA(x, y, 11, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + 1, y - 1, 1, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + 2, y - 1, 7, 1, Color(255, 255, 255, 255));
	FILLRGBA(x + 2, y - 2, 1, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + 3, y - 2, 5, 1, Color(255, 255, 255, 255));
	FILLRGBA(x + 3, y - 3, 1, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + 4, y - 3, 3, 1, Color(255, 255, 255, 255));
	FILLRGBA(x + 4, y - 4, 1, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + 5, y - 4, 1, 1, Color(255, 255, 255, 255));
	FILLRGBA(x + 5, y - 5, 1, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + 9, y - 1, 1, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + 8, y - 2, 1, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + 7, y - 3, 1, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + 6, y - 4, 1, 1, Color(0, 0, 0, 255));
}
/**********************************************************/

/**********************************************************/
void CGUIElement::DClose(int x, int y)
{
	int w = 12, h = 12;

	// Borders
	FILLRGBA(x, y, w, 1, Color(255, 255, 255, 255));
	FILLRGBA(x, y, 1, h, Color(255, 255, 255, 255));
	FILLRGBA(x + w, y, 1, h + 1, Color(1, 1, 1, 255));
	FILLRGBA(x, y + h, w + 1, 1, Color(1, 1, 1, 255));

	// X
	for (int lu = 0; lu<4; lu++)
	{
		int cross_x = x + 6;
		int cross_y = y + 6;

		FILLRGBA(cross_x - lu, cross_y - lu, 1, 1, Color(255, 255, 255, 255));
		FILLRGBA(cross_x + lu, cross_y - lu, 1, 1, Color(255, 255, 255, 255));
		FILLRGBA(cross_x + lu, cross_y + lu, 1, 1, Color(255, 255, 255, 255));
		FILLRGBA(cross_x - lu, cross_y + lu, 1, 1, Color(255, 255, 255, 255));
	}
}
/**********************************************************/

/**********************************************************/
void CGUIElement::DMinimize(int x, int y)
{
	int w = 12, h = 12;

	// Borders
	FILLRGBA(x, y, w, 1, Color(255, 255, 255, 255));
	FILLRGBA(x, y, 1, h, Color(255, 255, 255, 255));
	FILLRGBA(x + w, y, 1, h + 1, Color(1, 1, 1, 255));
	FILLRGBA(x, y + h, w + 1, 1, Color(1, 1, 1, 255));

	// -
	FILLRGBA(x + 3, y + 6, w - 5, 1, Color(255, 255, 255, 255));
}
/**********************************************************/

/**********************************************************/
void CGUIElement::DHide(int x, int y)
{
	int w = 12, h = 12;

	// Borders
	FILLRGBA(x, y, w, 1, Color(255, 255, 255, 255));
	FILLRGBA(x, y, 1, h, Color(255, 255, 255, 255));
	FILLRGBA(x + w, y, 1, h + 1, Color(1, 1, 1, 255));
	FILLRGBA(x, y + h, w + 1, 1, Color(1, 1, 1, 255));

	int w2 = 6, h2 = 6;

	// Sous Borders
	FILLRGBA(x + 3, y + 3, w2, 2, Color(255, 255, 255, 255));
	FILLRGBA(x + 3, y + 3, 1, h2, Color(255, 255, 255, 255));
	FILLRGBA(x + 3 + w2, y + 3, 1, h2 + 1, Color(255, 255, 255, 255));
	FILLRGBA(x + 3, y + 3 + h2, w2 + 1, 1, Color(255, 255, 255, 255));

}
/**********************************************************/

/**********************************************************/
void CGUIElement::DResize(int x, int y)
{
	int w = 1;
	int h = 1;

	int xx = x - 9;
	int yy = y + 3;
	for (int c = 0; c <= 7; c++)
	{
		FILLRGBA(xx, yy, w, h, Color(255, 255, 255, 255));
		xx++;
		yy--;
	}
	xx = x - 6;
	yy = y + 3;
	for (int c = 0; c <= 4; c++)
	{
		FILLRGBA(xx, yy, w, h, Color(255, 255, 255, 255));
		xx++;
		yy--;
	}
	xx = x - 3;
	yy = y + 3;
	for (int c = 0; c <= 1; c++)
	{
		FILLRGBA(xx, yy, w, h, Color(255, 255, 255, 255));
		xx++;
		yy--;
	}
}
//=================================================================================

//=================================================================================
void CGUIElement::BouttonUnPush(int x, int y, int w, int h, Color dwColor, char* title)
{
	XH.g_pDrawing->Tint2(x, y, w + 1, h, dwColor, Color(220, 230, 247, 255), 6);
	XH.g_pDrawing->FillRGBA(x, y, 3, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 3, y - 1, 2, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 5, y - 2, w - 5, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x, y + 1, 1, h - 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x, y + h, w + 2, 1, Color(59, 97, 156, 255));
	XH.g_pDrawing->FillRGBA(x + w + 1, y, 1, h, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + w, y - 1, 1, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 1, y + 1, 2, 1, Color(255, 255, 255, 255));
	XH.g_pDrawing->FillRGBA(x + 3, y, 2, 1, Color(255, 255, 255, 255));
	XH.g_pDrawing->FillRGBA(x + 5, y - 1, w - 5, 1, Color(255, 255, 255, 255));

	// Title
	XH.g_pDrawing->DrawString(true, x + (w / 2), y + (h / 2) - 7, Height, COLOR_WHITE, title);
}
//=================================================================================

//=================================================================================
void CGUIElement::BouttonPush(int x, int y, int w, int h, Color dwColor, char* title)
{
	XH.g_pDrawing->Tint2(x, y, w + 1, h, dwColor, Color(40, 40, 40, 255), 5);
	XH.g_pDrawing->FillRGBA(x, y, 3, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 3, y - 1, 2, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 5, y - 2, w - 5, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x, y + 1, 1, h - 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x, y + h, w + 2, 1, Color(59, 97, 156, 255));
	XH.g_pDrawing->FillRGBA(x + w + 1, y, 1, h, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + w, y - 1, 1, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 1, y + 1, 2, 1, Color(255, 255, 255, 255));
	XH.g_pDrawing->FillRGBA(x + 3, y, 2, 1, Color(255, 255, 255, 255));
	XH.g_pDrawing->FillRGBA(x + 5, y - 1, w - 5, 1, Color(255, 255, 255, 255));

	// Title
	XH.g_pDrawing->DrawString(true, x + (w / 2), y + (h / 2) - 7, Height, COLOR_WHITE, title);
}
//=================================================================================

//=================================================================================
void CGUIElement::SelectUnPush(int x, int y, int w, int h, Color dwColor, char* title)
{
	XH.g_pDrawing->Tint2(x, y, w + 1, h, dwColor, Color(220, 230, 247, 255), 6);
	XH.g_pDrawing->FillRGBA(x, y, 3, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 3, y - 1, 2, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 5, y - 2, w - 5, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x, y + 1, 1, h - 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x, y + h, w + 2, 1, Color(59, 97, 156, 255));
	XH.g_pDrawing->FillRGBA(x + w + 1, y, 1, h, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + w, y - 1, 1, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 1, y + 1, 2, 1, Color(255, 255, 255, 255));
	XH.g_pDrawing->FillRGBA(x + 3, y, 2, 1, Color(255, 255, 255, 255));
	XH.g_pDrawing->FillRGBA(x + 5, y - 1, w - 5, 1, Color(255, 255, 255, 255));

	// Logo
	XH.g_pDrawing->FillRGBA(x + w - 13, y + 5, 1, 1, Color(0, 0, 0, 255));
	XH.g_pDrawing->FillRGBA(x + w - 12, y + 5, 1, 2, Color(0, 0, 0, 255));
	XH.g_pDrawing->FillRGBA(x + w - 11, y + 5, 1, 3, Color(0, 0, 0, 255));
	XH.g_pDrawing->FillRGBA(x + w - 10, y + 5, 1, 4, Color(0, 0, 0, 255));
	XH.g_pDrawing->FillRGBA(x + w - 9, y + 5, 1, 3, Color(0, 0, 0, 255));
	XH.g_pDrawing->FillRGBA(x + w - 8, y + 5, 1, 2, Color(0, 0, 0, 255));
	XH.g_pDrawing->FillRGBA(x + w - 7, y + 5, 1, 1, Color(0, 0, 0, 255));

	// Title
	XH.g_pDrawing->DrawString(true, x + (w / 2) - 9, y, Height, COLOR_WHITE, title);
}
void CGUIElement::SelectPush(int x, int y, int w, int h, Color dwColor, char* title)
{
	XH.g_pDrawing->Tint2(x, y, w + 1, h, dwColor, Color(40, 40, 40, 255), 5);
	XH.g_pDrawing->FillRGBA(x, y, 3, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 3, y - 1, 2, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 5, y - 2, w - 5, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x, y + 1, 1, h - 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x, y + h, w + 2, 1, Color(59, 97, 156, 255));
	XH.g_pDrawing->FillRGBA(x + w + 1, y, 1, h, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + w, y - 1, 1, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 1, y + 1, 2, 1, Color(255, 255, 255, 255));
	XH.g_pDrawing->FillRGBA(x + 3, y, 2, 1, Color(255, 255, 255, 255));
	XH.g_pDrawing->FillRGBA(x + 5, y - 1, w - 5, 1, Color(255, 255, 255, 255));

	// Logo
	FILLRGBA(x + w - 13, y + 8, 1, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + w - 12, y + 7, 1, 2, Color(0, 0, 0, 255));
	FILLRGBA(x + w - 11, y + 6, 1, 3, Color(0, 0, 0, 255));
	FILLRGBA(x + w - 10, y + 5, 1, 4, Color(0, 0, 0, 255));
	FILLRGBA(x + w - 9, y + 6, 1, 3, Color(0, 0, 0, 255));
	FILLRGBA(x + w - 8, y + 7, 1, 2, Color(0, 0, 0, 255));
	FILLRGBA(x + w - 7, y + 8, 1, 1, Color(0, 0, 0, 255));

	// Title
	XH.g_pDrawing->DrawString(true, x + (w / 2) - 9, y, Height, COLOR_WHITE, title);
}
/**********************************************************/

/**********************************************************/
void CGUIElement::InputUnPush(int x, int y, int w, int h, Color dwColor)
{
	XH.g_pDrawing->Tint2(x, y, w + 1, h, dwColor, Color(220, 230, 247, 255), 6);
	XH.g_pDrawing->FillRGBA(x, y, 3, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 3, y - 1, 2, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 5, y - 2, w - 5, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x, y + 1, 1, h - 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x, y + h, w + 2, 1, Color(59, 97, 156, 255));
	XH.g_pDrawing->FillRGBA(x + w + 1, y, 1, h, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + w, y - 1, 1, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 1, y + 1, 2, 1, Color(255, 255, 255, 255));
	XH.g_pDrawing->FillRGBA(x + 3, y, 2, 1, Color(255, 255, 255, 255));
	XH.g_pDrawing->FillRGBA(x + 5, y - 1, w - 5, 1, Color(255, 255, 255, 255));
}
void CGUIElement::InputPush(int x, int y, int w, int h, Color dwColor)
{
	XH.g_pDrawing->Tint2(x, y, w + 1, h, dwColor, Color(40, 40, 40, 255), 5);
	XH.g_pDrawing->FillRGBA(x, y, 3, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 3, y - 1, 2, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 5, y - 2, w - 5, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x, y + 1, 1, h - 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x, y + h, w + 2, 1, Color(59, 97, 156, 255));
	XH.g_pDrawing->FillRGBA(x + w + 1, y, 1, h, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + w, y - 1, 1, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 1, y + 1, 2, 1, Color(255, 255, 255, 255));
	XH.g_pDrawing->FillRGBA(x + 3, y, 2, 1, Color(255, 255, 255, 255));
	XH.g_pDrawing->FillRGBA(x + 5, y - 1, w - 5, 1, Color(255, 255, 255, 255));
}
/**********************************************************/

/**********************************************************/
void CGUIElement::CheckBoxUnPush(int x, int y, Color dwColor, char* title)
{
	// Backround
	FILLRGBA(x, y, 12, 12, dwColor);

	// Border
	FILLRGBA(x - 1, y - 1, 12 + 2, 1, Color(255, 255, 255, 255));
	FILLRGBA(x - 1, y - 1, 1, 12 + 2, Color(255, 255, 255, 255));
	FILLRGBA(x, y + 12, 12, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + 12, y, 1, 12 + 1, Color(0, 0, 0, 255));

	// Title
	XH.g_pDrawing->DrawString(true, x + 16, y, NULL, COLOR_WHITE, title);
}
void CGUIElement::CheckBoxPush(int x, int y, Color dwColor, char* title)
{
	// Backround
	FILLRGBA(x, y, 12, 12, dwColor);

	// Border
	FILLRGBA(x - 1, y - 1, 12 + 2, 1, Color(0, 0, 0, 255));
	FILLRGBA(x - 1, y - 1, 1, 12 + 2, Color(0, 0, 0, 255));
	FILLRGBA(x, y + 12, 12, 1, Color(255, 255, 255, 255));
	FILLRGBA(x + 12, y, 1, 12 + 1, Color(255, 255, 255, 255));

	// V
	FILLRGBA(x + 3, y + 5, 1, 3, Color(0, 0, 0, 255));
	FILLRGBA(x + 4, y + 6, 1, 3, Color(0, 0, 0, 255));
	FILLRGBA(x + 5, y + 7, 1, 3, Color(0, 0, 0, 255));
	FILLRGBA(x + 6, y + 6, 1, 3, Color(0, 0, 0, 255));
	FILLRGBA(x + 7, y + 5, 1, 3, Color(0, 0, 0, 255));
	FILLRGBA(x + 8, y + 4, 1, 3, Color(0, 0, 0, 255));
	FILLRGBA(x + 9, y + 3, 1, 3, Color(0, 0, 0, 255));

	// Title
	XH.g_pDrawing->DrawString(true, x + 16, y, NULL, COLOR_WHITE, title);
}
/**********************************************************/

/**********************************************************/
void CGUIElement::ColorBoxDraw(int x, int y, int w, int h, int r, int g, int b, int t)
{
	// Backround
	FILLRGBA(x, y, w, h, Color(r, g, b, t));

	// Border
	FILLRGBA(x - 1, y - 1, w + 2, 1, Color(0, 0, 0, 255));
	FILLRGBA(x - 1, y - 1, 1, h + 2, Color(0, 0, 0, 255));
	FILLRGBA(x, y + h, w, 1, Color(255, 255, 255, 255));
	FILLRGBA(x + w, y, 1, h + 1, Color(255, 255, 255, 255));
}
/**********************************************************/

/**********************************************************/
void CGUIElement::MemoDraw(int x, int y, int w, int h, Color dwColor)
{
	XH.g_pDrawing->Tint2(x, y, w + 1, h, dwColor, Color(0, 0, 0, 255), 1);
	XH.g_pDrawing->FillRGBA(x, y, 3, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 3, y - 1, 2, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 5, y - 2, w - 5, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x, y + 1, 1, h - 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x, y + h, w + 2, 1, Color(59, 97, 156, 255));
	XH.g_pDrawing->FillRGBA(x + w + 1, y, 1, h, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + w, y - 1, 1, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 1, y + 1, 2, 1, Color(255, 255, 255, 255));
	XH.g_pDrawing->FillRGBA(x + 3, y, 2, 1, Color(255, 255, 255, 255));
	XH.g_pDrawing->FillRGBA(x + 5, y - 1, w - 5, 1, Color(255, 255, 255, 255));
}
/**********************************************************/

/**********************************************************/
void CGUIElement::ScroolBarUpUnPush(int x, int y, Color dwColor)
{
	// Backround
	FILLRGBA(x, y, 12, 12, dwColor);

	// Border
	FILLRGBA(x - 1, y - 1, 12 + 2, 1, Color(255, 255, 255, 255));
	FILLRGBA(x - 1, y - 1, 1, 12 + 2, Color(255, 255, 255, 255));
	FILLRGBA(x, y + 12, 12, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + 12, y, 1, 12 + 1, Color(0, 0, 0, 255));

	// Logo
	FILLRGBA(x + 6, y + 4, 1, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + 5, y + 5, 3, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + 4, y + 6, 5, 1, Color(0, 0, 0, 255));
}
/**********************************************************/

/**********************************************************/
void CGUIElement::ScroolBarUpPush(int x, int y, Color dwColor)
{
	// Backround
	FILLRGBA(x, y, 12, 12, dwColor);

	// Border
	FILLRGBA(x - 1, y - 1, 12 + 2, 1, Color(0, 0, 0, 255));
	FILLRGBA(x - 1, y - 1, 1, 12 + 2, Color(0, 0, 0, 255));
	FILLRGBA(x, y + 12, 12, 1, Color(255, 255, 255, 255));
	FILLRGBA(x + 12, y, 1, 12 + 1, Color(255, 255, 255, 255));

	// Logo
	FILLRGBA(x + 6, y + 4, 1, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + 5, y + 5, 3, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + 4, y + 6, 5, 1, Color(0, 0, 0, 255));
}
/**********************************************************/

/**********************************************************/
void CGUIElement::ScroolBarDownUnPush(int x, int y, Color dwColor)
{
	// Backround
	FILLRGBA(x, y, 12, 12, dwColor);

	// Border
	FILLRGBA(x - 1, y - 1, 12 + 2, 1, Color(255, 255, 255, 255));
	FILLRGBA(x - 1, y - 1, 1, 12 + 2, Color(255, 255, 255, 255));
	FILLRGBA(x, y + 12, 12, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + 12, y, 1, 12 + 1, Color(0, 0, 0, 255));

	// Logo
	FILLRGBA(x + 4, y + 5, 5, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + 5, y + 6, 3, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + 6, y + 7, 1, 1, Color(0, 0, 0, 255));
}
/**********************************************************/

/**********************************************************/
void CGUIElement::ScroolBarDownPush(int x, int y, Color dwColor)
{
	// Backround
	FILLRGBA(x, y, 12, 12, dwColor);

	// Border
	FILLRGBA(x - 1, y - 1, 12 + 2, 1, Color(0, 0, 0, 255));
	FILLRGBA(x - 1, y - 1, 1, 12 + 2, Color(0, 0, 0, 255));
	FILLRGBA(x, y + 12, 12, 1, Color(255, 255, 255, 255));
	FILLRGBA(x + 12, y, 1, 12 + 1, Color(255, 255, 255, 255));

	// Logo
	FILLRGBA(x + 4, y + 5, 5, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + 5, y + 6, 3, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + 6, y + 7, 1, 1, Color(0, 0, 0, 255));
}
/**********************************************************/

/**********************************************************/
void CGUIElement::ScroolDownUnPush(int x, int y, int w, int h, Color dwColor)
{
	// Backround
	FILLRGBA(x, y, w, h, dwColor);

	// Border
	FILLRGBA(x - 1, y - 1, w + 2, 1, Color(0, 0, 0, 255));
	FILLRGBA(x - 1, y - 1, 1, h + 2, Color(0, 0, 0, 255));
	FILLRGBA(x, y + h, w, 1, Color(255, 255, 255, 255));
	FILLRGBA(x + w, y, 1, h + 1, Color(255, 255, 255, 255));
}
/**********************************************************/

/**********************************************************/
void CGUIElement::ScroolDownPush(int x, int y, int w, int h, Color dwColor)
{
	// Backround
	FILLRGBA(x, y, w, h, dwColor);

	// Border
	FILLRGBA(x - 1, y - 1, w + 2, 1, Color(255, 255, 255, 255));
	FILLRGBA(x - 1, y - 1, 1, h + 2, Color(255, 255, 255, 255));
	FILLRGBA(x, y + h, w, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + w, y, 1, h + 1, Color(0, 0, 0, 255));
}
/**********************************************************/

/**********************************************************/
void CGUIElement::SnakeBox(int x, int y, int w, int h, Color dwColor)
{
	// Backround
	FILLRGBA(x, y, w, h, dwColor);

	// Border
	FILLRGBA(x - 1, y - 1, w + 2, 1, Color(0, 0, 0, 255));
	FILLRGBA(x - 1, y - 1, 1, h + 2, Color(0, 0, 0, 255));
	FILLRGBA(x, y + h, w, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + w, y, 1, h + 1, Color(0, 0, 0, 255));
}
/**********************************************************/

/**********************************************************/
void CGUIElement::BouttonUnPushTaskBar(int x, int y, int w, int h, Color dwColor, char* title)
{
	XH.g_pDrawing->Tint2(x, y, w + 1, h, dwColor, Color(220, 230, 247, 255), 6);
	XH.g_pDrawing->FillRGBA(x, y, 3, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 3, y - 1, 2, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 5, y - 2, w - 5, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x, y + 1, 1, h - 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x, y + h, w + 2, 1, Color(59, 97, 156, 255));
	XH.g_pDrawing->FillRGBA(x + w + 1, y, 1, h, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + w, y - 1, 1, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 1, y + 1, 2, 1, Color(255, 255, 255, 255));
	XH.g_pDrawing->FillRGBA(x + 3, y, 2, 1, Color(255, 255, 255, 255));
	XH.g_pDrawing->FillRGBA(x + 5, y - 1, w - 5, 1, Color(255, 255, 255, 255));

	// Title
	XH.g_pDrawing->DrawString(true, x + (w / 2), y + 1, Height, COLOR_WHITE, title);
}
void CGUIElement::BouttonPushTaskBar(int x, int y, int w, int h, Color dwColor, char* title)
{
	XH.g_pDrawing->Tint2(x, y, w + 1, h, dwColor, Color(40, 40, 40, 255), 5);
	XH.g_pDrawing->FillRGBA(x, y, 3, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 3, y - 1, 2, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 5, y - 2, w - 5, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x, y + 1, 1, h - 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x, y + h, w + 2, 1, Color(59, 97, 156, 255));
	XH.g_pDrawing->FillRGBA(x + w + 1, y, 1, h, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + w, y - 1, 1, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 1, y + 1, 2, 1, Color(255, 255, 255, 255));
	XH.g_pDrawing->FillRGBA(x + 3, y, 2, 1, Color(255, 255, 255, 255));
	XH.g_pDrawing->FillRGBA(x + 5, y - 1, w - 5, 1, Color(255, 255, 255, 255));

	// Title
	XH.g_pDrawing->DrawString(true, x + (w / 2), y + 1, Height, COLOR_WHITE, title);
}
void CGUIElement::ListDrawTaskBar(int x, int y, int w, int h, Color dwColor)
{
	XH.g_pDrawing->Tint2(x, y, w + 1, h, dwColor, Color(220, 230, 247, 255), 1);
	XH.g_pDrawing->FillRGBA(x, y, 3, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 3, y - 1, 2, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 5, y - 2, w - 5, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x, y + 1, 1, h - 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x, y + h, w + 2, 1, Color(59, 97, 156, 255));
	XH.g_pDrawing->FillRGBA(x + w + 1, y, 1, h, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + w, y - 1, 1, 1, Color(0, 53, 154, 255));
	XH.g_pDrawing->FillRGBA(x + 1, y + 1, 2, 1, Color(255, 255, 255, 255));
	XH.g_pDrawing->FillRGBA(x + 3, y, 2, 1, Color(255, 255, 255, 255));
	XH.g_pDrawing->FillRGBA(x + 5, y - 1, w - 5, 1, Color(255, 255, 255, 255));
}
/**********************************************************/

/**********************************************************/
void CGUIElement::SliderDraw(int x, int y, int w, int h, int r, int g, int b, int a)
{
	// Backround
	FILLRGBA(x, y, w, h, Color(r, g, b, a));

	// Border
	FILLRGBA(x, y - 1, w + 1, 1, Color(0, 0, 0, 255));
	FILLRGBA(x - 1, y - 1, 1, h + 2, Color(0, 0, 0, 255));
	FILLRGBA(x, y + h, w, 1, Color(0, 0, 0, 255));
	FILLRGBA(x + w, y, 1, h + 1, Color(0, 0, 0, 255));
}
/**********************************************************/

/**********************************************************/
void CGUIElement::DrawWindowBox(int x, int y, int w, int h, bool mode, bool maxilize, bool f1, bool f2, bool f3)
{
	FILLRGBA(x, y, w, 1, Color(0, 0, 0, 254));
	FILLRGBA(x - 2, y + 1, 3, 1, Color(0, 0, 0, 254));
	FILLRGBA(x - 3, y + 2, 2, 1, Color(0, 0, 0, 254));
	FILLRGBA(x - 3, y + 3, 1, 2, Color(0, 0, 0, 254));
	if (mode)
	{
		FILLRGBA(x - 4, y + 4, 1, h, Color(0, 0, 0, 254));
	}
	else {
		FILLRGBA(x - 4, y + 4, 1, 22, Color(0, 0, 0, 254));
		FILLRGBA(x - 4, y + 26, w + 8, 1, Color(0, 0, 0, 254));
	}

	// Angle Haut-Droit
	FILLRGBA(x + w - 1, y + 1, 3, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w + 1, y + 2, 2, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w + 2, y + 3, 1, 2, Color(0, 0, 0, 254));
	if (mode)
	{
		FILLRGBA(x + w + 3, y + 4, 1, h, Color(0, 0, 0, 254));
	}
	else {
		FILLRGBA(x + w + 3, y + 4, 1, 22, Color(0, 0, 0, 254));
	}

	if (mode)
	{
		FILLRGBA(x - 3, y + 3 + h, 1, 3, Color(0, 0, 0, 254));
		FILLRGBA(x - 2, y + 5 + h, 1, 2, Color(0, 0, 0, 254));
		FILLRGBA(x - 1, y + 6 + h, w + 2, 1, Color(0, 0, 0, 254));

		FILLRGBA(x + w + 2, y + 3 + h, 1, 3, Color(0, 0, 0, 254));
		FILLRGBA(x + w + 1, y + 5 + h, 1, 2, Color(0, 0, 0, 254));
	}

	FILLRGBA(x + 1, y + 1, w - 2, 1, Color(170,234,255));
	FILLRGBA(x - 1, y + 2, w + 2, 1, Color(170,234,255));
	FILLRGBA(x - 2, y + 3, w + 4, 2, Color(170,234,255));
	FILLRGBA(x - 3, y + 5, w + 6, 21, Color(170,234,255));

	if (mode)
	{
		FILLRGBA(x - 3, y + 26, 7, h - 29, Color(170,234,255));
		FILLRGBA(x + w - 4, y + 26, 7, h - 29, Color(170,234,255));
		FILLRGBA(x - 3, y - 3 + h, w + 6, 6, Color(170,234,255));
		FILLRGBA(x - 2, y + 3 + h, w + 4, 2, Color(170,234,255));
		FILLRGBA(x - 1, y + h + 5, w + 2, 1, Color(170,234,255));

		FILLRGBA(x + 4, y + 26, w - 9, 1, Color(0, 0, 0, 254));
		FILLRGBA(x + 4, y + 26, 1, h - 30, Color(0, 0, 0, 254));
		FILLRGBA(x + 4, y + h - 4, w - 8, 1, Color(0, 0, 0, 254));
		FILLRGBA(x - 5 + w, y + 26, 1, h - 30, Color(0, 0, 0, 254));
	}
	if (maxilize)
	{
		if (!f1)
			XH.g_pDrawing->Tint2(x + w - 96, y + 1, 25, 16, Color(189, 189, 189, 255), Color(121, 122, 130, 255), 7);
		else
			XH.g_pDrawing->Tint2(x + w - 96, y + 1, 25, 16, Color(255, 255, 255, 255), Color(121, 122, 130, 255), 7);
		if (!f2)
			XH.g_pDrawing->Tint2(x + w - 71, y + 1, 25, 16, Color(189, 189, 189, 255), Color(121, 122, 130, 255), 7);
		else
			XH.g_pDrawing->Tint2(x + w - 71, y + 1, 25, 16, Color(255, 255, 255, 255), Color(121, 122, 130, 255), 7);
	}
	else
	{
		if (!f1)
			XH.g_pDrawing->Tint2(x + w - 72, y + 1, 25, 16, Color(189, 189, 189, 255), Color(121, 122, 130, 255), 7);
		else
			XH.g_pDrawing->Tint2(x + w - 72, y + 1, 25, 16, Color(255, 255, 255, 255), Color(121, 122, 130, 255), 7);
	}

	if (!f3)
		XH.g_pDrawing->Tint2(x + w - 46, y + 1, 41, 16, Color(230, 171, 158, 255), Color(191, 96, 85, 255), 7);
	else
		XH.g_pDrawing->Tint2(x + w - 46, y + 1, 41, 16, Color(255, 185, 175, 255), Color(175, 85, 75, 255), 7);

	// Task
	if (maxilize)
	{

		FILLRGBA(x + w - 89, y + 9, 10, 3, Color(220, 219, 214, 200));


		FILLRGBA(x + w - 64, y + 5, 2, 7, Color(220, 219, 214, 200));
		FILLRGBA(x + w - 64, y + 5, 8, 2, Color(220, 219, 214, 200));
		FILLRGBA(x + w - 64, y + 11, 8, 2, Color(220, 219, 214, 200));
		FILLRGBA(x + w - 56, y + 5, 2, 8, Color(220, 219, 214, 200));
	}
	else {
		FILLRGBA(x + w - 89 + 25, y + 9, 10, 3, Color(220, 219, 214, 200));
	}

	FILLRGBA(x + w - 5, y, 1, 16, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 47, y, 1, 17, Color(0, 0, 0, 254));
	if (maxilize)
	{
		FILLRGBA(x + w - 72, y, 1, 17, Color(0, 0, 0, 254));
		FILLRGBA(x + w - 97, y, 1, 16, Color(0, 0, 0, 254));
		FILLRGBA(x + w - 96, y + 16, 1, 1, Color(0, 0, 0, 254));
		FILLRGBA(x + w - 95, y + 17, 89, 1, Color(0, 0, 0, 254));
	}
	else {
		FILLRGBA(x + w - 72, y, 1, 16, Color(0, 0, 0, 254));
		FILLRGBA(x + w - 72, y, 1, 16, Color(0, 0, 0, 254));
		FILLRGBA(x + w - 71, y + 16, 1, 1, Color(0, 0, 0, 254));
		FILLRGBA(x + w - 70, y + 17, 64, 1, Color(0, 0, 0, 254));
	}
	FILLRGBA(x + w - 6, y + 16, 1, 1, Color(0, 0, 0, 254));

	int maxi = 0;
	if (!maxilize)
		maxi = 25;

	FILLRGBA(x + w - 90 + maxi, y + 8, 11, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 90 + maxi, y + 8, 1, 4, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 90 + maxi, y + 12, 11, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 79 + maxi, y + 8, 1, 5, Color(0, 0, 0, 254));

	if (maxilize)
	{
		FILLRGBA(x + w - 65, y + 4, 11, 1, Color(0, 0, 0, 254));
		FILLRGBA(x + w - 65, y + 4, 1, 10, Color(0, 0, 0, 254));
		FILLRGBA(x + w - 65, y + 13, 11, 1, Color(0, 0, 0, 254));
		FILLRGBA(x + w - 54, y + 4, 1, 10, Color(0, 0, 0, 254));
		//------
		FILLRGBA(x + w - 62, y + 7, 6, 1, Color(0, 0, 0, 254));
		FILLRGBA(x + w - 62, y + 7, 1, 3, Color(0, 0, 0, 254));
		FILLRGBA(x + w - 62, y + 10, 6, 1, Color(0, 0, 0, 254));
		FILLRGBA(x + w - 57, y + 7, 1, 3, Color(0, 0, 0, 254));
	}

	FILLRGBA(x + w - 30, y + 5, 3, 1, Color(220, 219, 214, 200));
	FILLRGBA(x + w - 24, y + 5, 3, 1, Color(220, 219, 214, 200));
	FILLRGBA(x + w - 29, y + 6, 3, 1, Color(220, 219, 214, 200));
	FILLRGBA(x + w - 25, y + 6, 3, 1, Color(220, 219, 214, 200));
	FILLRGBA(x + w - 28, y + 7, 5, 1, Color(220, 219, 214, 200));
	FILLRGBA(x + w - 27, y + 8, 3, 2, Color(220, 219, 214, 200));
	FILLRGBA(x + w - 28, y + 10, 5, 1, Color(220, 219, 214, 200));
	FILLRGBA(x + w - 29, y + 11, 3, 1, Color(220, 219, 214, 200));
	FILLRGBA(x + w - 25, y + 11, 3, 1, Color(220, 219, 214, 200));
	FILLRGBA(x + w - 30, y + 12, 3, 1, Color(220, 219, 214, 200));
	FILLRGBA(x + w - 24, y + 12, 3, 1, Color(220, 219, 214, 200));

	FILLRGBA(x + w - 30, y + 4, 3, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 24, y + 4, 3, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 31, y + 5, 1, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 30, y + 6, 1, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 29, y + 7, 1, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 28, y + 8, 1, 2, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 29, y + 10, 1, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 30, y + 11, 1, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 31, y + 12, 1, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 30, y + 13, 3, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 24, y + 13, 3, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 27, y + 5, 1, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 25, y + 5, 1, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 26, y + 6, 1, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 27, y + 12, 1, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 26, y + 11, 1, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 25, y + 12, 1, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 21, y + 5, 1, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 22, y + 6, 1, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 23, y + 7, 1, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 24, y + 8, 1, 2, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 23, y + 10, 1, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 22, y + 11, 1, 1, Color(0, 0, 0, 254));
	FILLRGBA(x + w - 21, y + 12, 1, 1, Color(0, 0, 0, 254));

	FILLRGBA(x + w - 71, y + 1, 24, 1, Color(252, 252, 252, 255));
	FILLRGBA(x + w - 46, y + 1, 41, 1, Color(252, 252, 252, 255));
	FILLRGBA(x + w - 71, y + 2, 1, 14, Color(182, 183, 186, 255));
	FILLRGBA(x + w - 48, y + 2, 1, 15, Color(182, 183, 186, 255));
	FILLRGBA(x + w - 70, y + 16, 22, 1, Color(182, 183, 186, 255));
	FILLRGBA(x + w - 46, y + 2, 1, 15, Color(223, 166, 158, 255));
	FILLRGBA(x + w - 45, y + 16, 39, 1, Color(223, 166, 158, 255));
	FILLRGBA(x + w - 6, y + 2, 1, 14, Color(223, 166, 158, 255));
	FILLRGBA(x + w - 7, y + 15, 1, 1, Color(223, 166, 158, 255));

	if (maxilize)
	{
		FILLRGBA(x + w - 96, y + 1, 24, 1, Color(252, 252, 252, 255));
		FILLRGBA(x + w - 96, y + 2, 1, 14, Color(182, 183, 186, 255));
		FILLRGBA(x + w - 73, y + 2, 1, 15, Color(182, 183, 186, 255));
		FILLRGBA(x + w - 95, y + 15, 1, 1, Color(182, 183, 186, 255));
		FILLRGBA(x + w - 95, y + 16, 22, 1, Color(182, 183, 186, 255));

		FILLRGBA(x + w - 71, y + 16, 1, 1, Color(182, 183, 186, 255));
	}
	else {
		FILLRGBA(x + w - 70, y + 15, 1, 1, Color(182, 183, 186, 255));
	}

	FILLRGBA(x + w - 6, y + 17, 2, 1, Color(223, 223, 223, 255));
	FILLRGBA(x + w - 5, y + 16, 2, 1, Color(223, 223, 223, 255));
	FILLRGBA(x + w - 4, y + 1, 1, 15, Color(223, 223, 223, 255));
	FILLRGBA(x + w - 3, y + 1, 2, 1, Color(223, 223, 223, 255));
	FILLRGBA(x + w - 2, y + 2, 3, 1, Color(223, 223, 223, 255));
	FILLRGBA(x + w, y + 3, 2, 1, Color(223, 223, 223, 255));
	FILLRGBA(x + w + 1, y + 4, 1, 2, Color(223, 223, 223, 255));

	if (maxilize)
	{
		FILLRGBA(x + w - 98, y + 1, 1, 16, Color(223, 223, 223, 255));
		FILLRGBA(x + w - 97, y + 16, 1, 1, Color(223, 223, 223, 255));
		FILLRGBA(x + w - 97, y + 17, 2, 1, Color(223, 223, 223, 255));
		FILLRGBA(x + w - 96, y + 18, 91, 1, Color(223, 223, 223, 255));
		FILLRGBA(x + 1, y + 1, w - 99, 1, Color(223, 223, 223, 255));
	}
	else {
		FILLRGBA(x + w - 73, y + 1, 1, 16, Color(223, 223, 223, 255));
		FILLRGBA(x + w - 72, y + 16, 1, 1, Color(223, 223, 223, 255));
		FILLRGBA(x + w - 72, y + 17, 2, 1, Color(223, 223, 223, 255));
		FILLRGBA(x + w - 71, y + 18, 66, 1, Color(223, 223, 223, 255));
		FILLRGBA(x + 1, y + 1, w - 74, 1, Color(223, 223, 223, 255));
	}

	FILLRGBA(x - 1, y + 2, 3, 1, Color(223, 223, 223, 255));
	FILLRGBA(x - 2, y + 3, 2, 1, Color(223, 223, 223, 255));
	FILLRGBA(x - 2, y + 4, 1, 2, Color(223, 223, 223, 255));

	if (mode)
	{
		FILLRGBA(x + w + 2, y + 5, 1, h - 3, Color(223, 223, 223, 255));
		FILLRGBA(x - 3, y + 5, 1, h - 2, Color(223, 223, 223, 255));
		FILLRGBA(x - 2, y + h + 2, 1, 3, Color(223, 223, 223, 255));
		FILLRGBA(x - 1, y + h + 4, 1, 1, Color(223, 223, 223, 255));
		FILLRGBA(x - 1, y + h + 5, w + 2, 1, Color(223, 223, 223, 255));
		FILLRGBA(x + w, y + h + 4, 2, 1, Color(223, 223, 223, 255));
		FILLRGBA(x + w + 1, y + h + 3, 1, 1, Color(223, 223, 223, 255));
		FILLRGBA(x + w + 1, y + h + 2, 2, 1, Color(223, 223, 223, 255));
	}
	else {
		FILLRGBA(x - 3, y + 5, 1, 21, Color(223, 223, 223, 255));
		FILLRGBA(x + w + 2, y + 5, 1, 21, Color(223, 223, 223, 255));
	}

	if (mode)
	{
		FILLRGBA(x + 5, y + 27, w - 10, 1, Color(193, 194, 198, 255));
		FILLRGBA(x + 5, y + 28, 1, h - 32, Color(193, 194, 198, 255));
		FILLRGBA(x + 5, y + h - 5, w - 10, 1, Color(193, 194, 198, 255));
		FILLRGBA(x - 6 + w, y + 28, 1, h - 32, Color(193, 194, 198, 255));
	}
}
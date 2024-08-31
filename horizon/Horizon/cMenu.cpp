#include "cMenu.h"
#include "cMouse.h"

cMenu gMenu;

bool bKeyPress[256];
bool IsKeyPressed(int iKey)
{
	if (GetAsyncKeyState(iKey))
	{
		if (!bKeyPress[iKey])
		{
			bKeyPress[iKey] = true;
			return true;
		}
	}
	else
		bKeyPress[iKey] = false;
	return false;
}

int MenuX = 120;
int MenuY = 120;

#define MENU_BG COLORCODE(255, 150, 0, 255)

struct a_menu{ char title[1000]; float* value; float min; float max; float step; };
int menuIndex = 0; int menuItems = 0;
a_menu amenu[150];
float menu, menu1, menu2, menu3, menu4, menu5;
bool bMenu;

int cMenu::addItem(int n, char title[1000], float* value, float min, float max, float step)
{
	strcpy(amenu[n].title, title);
	amenu[n].value = value;
	amenu[n].min = min;
	amenu[n].max = max;
	amenu[n].step = step;
	return (n + 1);
}

void cMenu::InitMenu()
{
	int i = 0;

	i = addItem(i, "[ESP Features]", &menu, 0, 1, 1);
	{
		if (menu == 1)
		{
			i = addItem(i, "   ESP Active", &gCvar.esp_active, 0, 1, 1);
			i = addItem(i, "   Name", &gCvar.esp_name, 0, 1, 1);
			i = addItem(i, "   Health", &gCvar.esp_health, 0, 1, 1);
			i = addItem(i, "   GUID", &gCvar.esp_guid, 0, 1, 1);
			i = addItem(i, "   Distance", &gCvar.esp_distance, 0, 1, 1);
			i = addItem(i, "   Bounding Box", &gCvar.esp_box, 0, 2, 1);
			i = addItem(i, "   Crosshair", &gCvar.esp_crosshair, 0, 1, 1);
		}
	}

	i = addItem(i, "[Misc Features]", &menu1, 0, 1, 1);
	{
		if (menu1 == 1)
		{
			i = addItem(i, "   Bunnyhop", &gCvar.misc_bunnyhop, 0, 1, 1);
		}
	}

	i = addItem(i, "[Removal Features]", &menu2, 0, 1, 1);
	{
		if (menu2 == 1)
		{
			i = addItem(i, "   No Spread", &gCvar.rem_spread, 0, 1, 1);
			i = addItem(i, "   No Recoil", &gCvar.rem_recoil, 0, 1, 1);
		}
	}
	menuItems = i;
}

bool hasFocus; 
#define drag( x,  y,  w,  h){\
	static int ptr[2];\
	static bool mouseOver;\
	if(gMouse.mouse1Hold){\
		if(gMouse.check(*x, *y /*- 12*/, w, h) && !hasFocus){\
			mouseOver = true;\
			hasFocus = true;\
		}\
		if(mouseOver){\
			*x += gMouse.mousePos[0] - ptr[0];\
			*y += gMouse.mousePos[1] - ptr[1];\
		}\
	}else{\
		mouseOver = false;\
		hasFocus = false;\
	}\
	ptr[0] = gMouse.mousePos[0];\
	ptr[1] = gMouse.mousePos[1];\
}

void blackBorder(int x, int y, int w, int h)
{
	gDrawing.FillRGBA(x - 1, y - 1, w + 2, 1, COLORCODE(0, 0, 0, 255)); //top
	gDrawing.FillRGBA(x - 1, y, 1, h - 1, COLORCODE(0, 0, 0, 255)); //top
	gDrawing.FillRGBA(x + w, y, 1, h - 1, COLORCODE(0, 0, 0, 255)); //top
	gDrawing.FillRGBA(x - 1, y + h - 1, w + 2, 1, COLORCODE(0, 0, 0, 255)); //top
}

void AimMenu(float *var, int x, int y, char *name)
{
	blackBorder(x - 20, y, 15, 15); //On/off box!
	if (gMouse.check(x, y, 15, 15))
	{
		if (gMouse.mouse1Press)
		{
			if (*var == 0)
			{
				*var = 1;
			}
			else
			{
				*var = 0;
			}
		}
	}

	if (*var == 1)
	{
		gDrawing.DrawString(x - 15, y, COLORCODE(0, 0, 0, 255), "x");
	}
	gDrawing.DrawString(x, y, COLORCODE(255, 255, 255, 255), name);
}

void cMenu::DrawMenu()
{
	if (IsKeyPressed(VK_INSERT))
	{
		bMenu = !bMenu;
		gMouse.active = !gMouse.active;
	}
	menuEvent();
	if (!bMenu)
		return;

	int i = menuItems;

	// Attempt at checkbox Menu //
	gDrawing.FillRGBA(gScreenSize.m_iWidth / 3 - 81, gScreenSize.m_iHeight / 3 - 61, 352, 402, COLORCODE(0, 0, 0, 255));			// Main Background border
	gDrawing.FillRGBA(gScreenSize.m_iWidth / 3 - 80, gScreenSize.m_iHeight / 3 - 60, 350, 400, COLORCODE(121, 188, 56, 255));		// Main Background
	gDrawing.FillRGBA(gScreenSize.m_iWidth / 3 - 77, gScreenSize.m_iHeight / 3 - 31, 344, 368, COLORCODE(0, 0, 0, 255));			// Inner Border
	gDrawing.FillRGBA(gScreenSize.m_iWidth / 3 - 76, gScreenSize.m_iHeight / 3 - 30, 342, 366, COLORCODE(255, 255, 255, 255));		// Inner Inner White

	// Buttons


	// Aimbot //
	gDrawing.FillRGBA(gScreenSize.m_iWidth / 3 - 77, gScreenSize.m_iHeight / 3 - 51, 62, 19, COLORCODE(0, 0, 0, 255));
	gDrawing.FillRGBA(gScreenSize.m_iWidth / 3 - 76, gScreenSize.m_iHeight / 3 - 50, 60, 17, COLORCODE(230, 230, 230, 255));
	gDrawing.DrawString(gScreenSize.m_iWidth / 3 - 64, gScreenSize.m_iHeight / 3 - 50, COLORCODE(255, 255, 255, 255), "Aimbot");

	// Visuals // 
	gDrawing.FillRGBA(gScreenSize.m_iWidth / 3 - 10, gScreenSize.m_iHeight / 3 - 51, 62, 19, COLORCODE(0, 0, 0, 255));
	gDrawing.FillRGBA(gScreenSize.m_iWidth / 3 - 9, gScreenSize.m_iHeight / 3 - 50, 60, 17, COLORCODE(230, 230, 230, 255));
	gDrawing.DrawString(gScreenSize.m_iWidth / 3 - 1, gScreenSize.m_iHeight / 3 - 50, COLORCODE(255, 255, 255, 255), "Visuals");

	// Misc // 
	gDrawing.FillRGBA(gScreenSize.m_iWidth / 3 + 58, gScreenSize.m_iHeight / 3 - 51, 62, 19, COLORCODE(0, 0, 0, 255));
	gDrawing.FillRGBA(gScreenSize.m_iWidth / 3 + 59, gScreenSize.m_iHeight / 3 - 50, 60, 17, COLORCODE(230, 230, 230, 255));
	gDrawing.DrawString(gScreenSize.m_iWidth / 3 + 78, gScreenSize.m_iHeight / 3 - 50, COLORCODE(255, 255, 255, 255), "Misc");

	// Settings // 
	gDrawing.FillRGBA(gScreenSize.m_iWidth / 3 + 126, gScreenSize.m_iHeight / 3 - 51, 62, 19, COLORCODE(0, 0, 0, 255));
	gDrawing.FillRGBA(gScreenSize.m_iWidth / 3 + 127, gScreenSize.m_iHeight / 3 - 50, 60, 17, COLORCODE(230, 230, 230, 255));
	gDrawing.DrawString(gScreenSize.m_iWidth / 3 + 138, gScreenSize.m_iHeight / 3 - 50, COLORCODE(255, 255, 255, 255), "Settings");

	// X // 
	gDrawing.FillRGBA(gScreenSize.m_iWidth / 3 + 197, gScreenSize.m_iHeight / 3 - 50, 69, 17, COLORCODE(255, 0, 0, 255));
	gDrawing.DrawString(gScreenSize.m_iWidth / 3 + 216, gScreenSize.m_iHeight / 3 - 50, COLORCODE(255, 255, 255, 255), "Close");

	AimMenu(&gCvar.esp_active, gScreenSize.m_iWidth / 3 - 50, gScreenSize.m_iHeight / 3 - 20, "ESP Active");
	AimMenu(&gCvar.esp_guid, gScreenSize.m_iWidth / 3 - 50, gScreenSize.m_iHeight / 3, "SteamID");
	AimMenu(&gCvar.esp_crosshair, gScreenSize.m_iWidth / 3 - 50, gScreenSize.m_iHeight / 3 + 20, "Crosshair");
	AimMenu(&gCvar.esp_box, gScreenSize.m_iWidth / 3 - 50, gScreenSize.m_iHeight / 3 + 40, "Bounding Box");
	AimMenu(&gCvar.esp_bones, gScreenSize.m_iWidth / 3 - 50, gScreenSize.m_iHeight / 3 + 60, "Bones");
	AimMenu(&gCvar.esp_bones, gScreenSize.m_iWidth / 3 - 50, gScreenSize.m_iHeight / 3 + 80, "Distance");

	// End of Checkbox Menu //
	gDrawing.FillRGBA(MenuX, MenuY - 25, 140, 20, MENU_BG);
	gDrawing.DrawString(MenuX + 40, MenuY - 25, COLORCODE(255, 255, 255, 255), "Horizon Hack");
	gDrawing.FillRGBA(MenuX, MenuY, 140, (12 * i), COLORCODE(44, 62, 80, 120));

	for (int i = 0; i < menuItems; i++)
	if (i != menuIndex)
	{
		gDrawing.DrawString(MenuX + 5, MenuY + (12 * i), COLORCODE(255, 255, 255, 255), amenu[i].title);
		gDrawing.DrawString(MenuX + 30, MenuY + (12 * i), COLORCODE(255, 255, 255, 255), "                                %2.1f", amenu[i].value[0]);
	}
	else
	{
		gDrawing.DrawString(MenuX + 5, MenuY + (12 * i), COLORCODE(255, 0, 0, 200), amenu[i].title);
		gDrawing.DrawString(MenuX + 30, MenuY + (12 * i), COLORCODE(255, 0, 0, 200), "                               %2.1f", amenu[i].value[0]);
	}
	gMouse.buttons();
	gMouse.draw();
	drag(&MenuX, &MenuY, 120, 14);
	for (int x = 0; x < menuItems; x++)
	if (gMouse.check(MenuX, MenuY + (12 * x), 120, 14)) 
		menuIndex = x;
	if (gMouse.check(MenuX, MenuY, 120, 12 * menuItems))
	{
		if (gMouse.mouse1Press)
		{
			if (amenu[menuIndex].value)
			{
				amenu[menuIndex].value[0] -= amenu[menuIndex].step;
				if (amenu[menuIndex].value[0] < amenu[menuIndex].min)
					amenu[menuIndex].value[0] = amenu[menuIndex].max;
			}
		}
		else if (gMouse.mouse2Press)
		{
			if (amenu[menuIndex].value)
			{
				amenu[menuIndex].value[0] += amenu[menuIndex].step;
				if (amenu[menuIndex].value[0] > amenu[menuIndex].max)
					amenu[menuIndex].value[0] = amenu[menuIndex].min;
			}
		}
	}
}

bool cMenu::menuEvent()
{
	return 1;
}
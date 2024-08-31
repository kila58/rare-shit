#include "Menu.h"
#include "CDrawManager.h"
//EEngine pEngine;
CMenu pMenu;
COptions pOptions;

#define DM gDrawManager
#define M pMenu
void CMenu::Render(int x, int y, int w, int h)
{
	//tabs
	M.TabOperator(x - 35, y - 35, w, 35, pOptions.tabAIM, pOptions.tabVISUALS, pOptions.tabMISC, pOptions.tabSPECIAL, pOptions.tabCOLORS);
	//Main square
	DM.DrawRect(x, y, w, h, colDarkGrey);
	DM.OutlineRect(x, y, w, h, colBlack);


	//Box for tooltip
	DM.DrawRect(x + 10, y + 10, w - 20, 30, colGrey);
	DM.OutlineRect(x + 10, y + 10, w - 20, 30, colBlack);


	//Main Inner Window
	DM.DrawRect(x + 15, y + 40, w - 40, h - 50, colGrey);
	DM.OutlineRect(x + 15, y + 40, w - 40, h - 50, colBlack);

	//1st Tab
	if (pOptions.tabAIM)
	{
		M.DrawCheckBoxF(x + 34, y + 68, colDarkGrey, "aim bot", gCvars.aimassist, colWhite, "Helps correct your aim");
		M.DrawCheckBoxF(x + 34, y + 88, colDarkGrey, "autoshoot", gCvars.aimbot_autoshoot, colWhite, "Shoots when you can hit the enemy.");
		M.DrawCheckBoxF(x + 34, y + 108, colDarkGrey, "silent", gCvars.aimbot_silent, colWhite, "Silent aimbot");
		/*M.DrawSlider(x + 43, y + h / 2 + 70, w - 100, 1,361, gCvars.fov, pOptions.s1,"AIM_FOV");*/
		/*M.DrawSlider(x + 43, y + h / 2 + 150, w - 100, 1, 21, gCvars.smooth, pOptions.s2, "AIM_SMOOTH");*/
		//80 diff
		M.DrawCheckBoxF(x + 235, y + 68, colDarkGrey, "Triggerbot", gCvars.triggerbot, colWhite, "Shoots if you can hit the enemy. (Reccomended gun: AWP)");
		M.DrawCheckBoxF(x + 235, y + 88, colDarkGrey, "AIMBOT RCS", gCvars.aimbot_rcs, colWhite, "Controlls recoil when aimbotting");
		
		M.DrawSlider(x + 43, y + h / 2 + 70, w - 120, 1, 361, gCvars.fov, pOptions.s1, "FOV");
		static float temp;
		M.DrawSlider(x + 43, y + h / 2 + 150, w - 120, 1, 51, temp, pOptions.s2, "SMOOTH AMOUNT");
		gCvars.smoothamount = 50 - temp;
		//Line Boxes
		DM.DrawLineBox(x + 23, y + 48, 60, w - 55, h / 2 - 58, colWhite, colGrey, "Main");
		DM.DrawLineBox(x + 23, y + 48 + (h / 2 - 58) + 10, 60, w - 55, h / 2 - 20, colWhite, colGrey, "Sliders");




	}
	if (pOptions.tabVISUALS)
	{

		M.DrawCheckBoxF(x + 34, y + 68, colDarkGrey, "ESP", gCvars.esp, colWhite, "Lets you see where players are");
		M.DrawCheckBoxF(x + 34, y + 88, colDarkGrey, "ESP_TEAM", gCvars.esp_team, colWhite, "Draws team ESP");
		M.DrawCheckBoxF(x + 34, y + 108, colDarkGrey, "ESP_HEALTH", gCvars.esp_health, colWhite, "Draws health");
		M.DrawCheckBoxF(x + 34, y + 128, colDarkGrey, "ESP_BONE", gCvars.esp_bone, colWhite, "Bone ESP");
		M.DrawCheckBoxF(x + 34, y + 148, colDarkGrey, "esp_fov", gCvars.esp_fov, colWhite, "Draws chams");


		M.DrawCheckBoxF(x + 234, y + 68, colDarkGrey, "ESP_NAME", gCvars.esp_name, colWhite, "Draws name ESP");
		M.DrawCheckBoxF(x + 234, y + 88, colDarkGrey, "ESP_HEALTHBAR", gCvars.esp_healthbar, colWhite, "Draw Healthbar");
		M.DrawCheckBoxF(x + 234, y + 108, colDarkGrey, "ESP_DISTANCE", gCvars.esp_distance, colWhite, "Draws distance");
		M.DrawCheckBoxF(x + 234, y + 128, colDarkGrey, "esp_weapon", gCvars.esp_weapon, colWhite, "No hands are drawn.");
		M.DrawCheckBoxF(x + 234, y + 148, colDarkGrey, "RADAR HACK", gCvars.radar, colWhite, "Shows enemy on the radar");



		DM.DrawLineBox(x + 23, y + 48, 50, w - 55, h - 65, colWhite, colGrey, "ESP");


	}

	if (pOptions.tabMISC)
	{


		DM.DrawLineBox(x + 23, y + 48, 60, w - 55, h - 65, colWhite, colGrey, "Misc");
		M.DrawCheckBoxF(x + 35, y + 68, colDarkGrey, "bunny hop", gCvars.bhop, colWhite, "This will automatically jump when the time is right.");
		M.DrawCheckBoxF(x + 35, y + 88, colDarkGrey, "auto strafe", gCvars.bhop_strafe, colWhite, "Automatically strafes when bhopping for maximum speed.");



		M.DrawCheckBoxF(x + 234, y + 68, colDarkGrey, "No Vis Recoil", gCvars.novisrecoil, colWhite, "No visual recoil");
		M.DrawCheckBoxF(x + 234, y + 88, colDarkGrey, "RCS", gCvars.rcs, colWhite, "No recoil whenever you shoot.");




	}
	if (pOptions.tabSPECIAL)
	{
		//FUN TAB
		DM.DrawLineBox(x + 23, y + 48, 50, w - 55, h - 65, colWhite, colGrey, "Fun");
		M.DrawCheckBoxF(x + 35, y + 68, colDarkGrey, "Chiken Glow", gCvars.chiken_glow, colRed, "Glow ESP on chickens");
		
	}
	if (pOptions.tabCOLORS)
	{
		DM.DrawLineBox(x + 23, y + 48, 50, w - 55, h - 65, colWhite, colGrey, "HvH");
		//M.DrawCheckBoxF(x + 35, y + 68, colDarkGrey, "Fakedownback [UD]", gCvars.aa_fakedownback, colWhite, "fake angles");
		M.DrawCheckBoxF(x + 235, y + 68, colDarkGrey, "spinbot [ud]", gCvars.spinbot, colWhite, "Anti-aim");
		M.DrawCheckBoxF(x + 235, y + 88, colDarkGrey, "Fakeangles [UNTRUTSED]", gCvars.fakeangle, colRed, "-181 pitch");
		


		M.DrawCheckBoxF(x + 35, y + 68, colDarkGrey, "Nospread [HvH]", gCvars.nospread, colWhite, "Nospread in HvH only");
		M.DrawCheckBoxF(x + 35, y + 88, colDarkGrey, "Fakeside [UNTRUSTED]", gCvars.fakeside, colRed, "fake side");
		M.DrawCheckBoxF(x + 35, y + 108, colDarkGrey, "FakeLag", gCvars.fakelag, colRed, "Fakelag");
	}

	//DrawMouse
	pMenu.GetMouse();

	//Menu Mover
	pMenu.Mover(pOptions.Menu_X, pOptions.Menu_Y, w, 80, 0);


}

void CMenu::AddTab(int x, int y, int w, int h, Color Fill, Color Outline, const char* Text)
{
	gDrawManager.DrawRect(x, y, w, h, Fill);
	gDrawManager.OutlineRect(x, y, w, h, Outline);
	gDrawManager.DrawString(false, false, x + 20, y + 10, colWhite, Text);
}

void CMenu::AddOtherTab(int x, int y, int w, int h, Color Fill, Color Outline, const char* Text)
{

}



void CMenu::SideButton(int x, int y, int w, int h, Color Fill, Color Text, int letters, const char* letter1, const char* letter2, const char* letter3, const char* letter4, const char* letter5, const char* letter6, const char* letter7, bool &pOption)
{
	DM.DrawRect(x, y, w, h, Fill);
	DM.OutlineRect(x, y, w, h, colBlack);
	DM.DrawString(false, true, x + 10, y + 5, Text, letter1);
	DM.DrawString(false, true, x + 10, y + 25, Text, letter2);
	DM.DrawString(false, true, x + 10, y + 45, Text, letter3);
	DM.DrawString(false, true, x + 10, y + 65, Text, letter4);

	if (Mousein(x, y, w, h))
	{
		DM.DrawRect(x, y, w, h, Color(200, 200, 200, 80));
		DM.OutlineRect(x, y, w, h, colBlack);

		if (GetAsyncKeyState(0x1) & 1)
		{
			//pOption = !pOption;
		}
	}
}

void CMenu::SideLabel(int x, int y, int w, int h, Color Fill, Color Text, int letters, const char* letter1, const char* letter2, const char* letter3, const char* letter4, const char* letter5, const char* letter6, const char* letter7, bool &pOption)
{

	DM.DrawString(false, true, x + 10, y + 5, Text, letter1);
	DM.DrawString(false, true, x + 10, y + 15, Text, letter2);
	DM.DrawString(false, true, x + 10, y + 25, Text, letter3);
	DM.DrawString(false, true, x + 10, y + 35, Text, letter4);
	DM.DrawString(false, true, x + 10, y + 45, Text, letter5);
	DM.DrawString(false, true, x + 10, y + 55, Text, letter6);
	DM.DrawString(false, true, x + 10, y + 65, Text, letter7);

	if (Mousein(x, y, w, h))
	{
		DM.DrawString(false, true, x + 10, y + 5, Color(200, 200, 200, 80), letter1);
		DM.DrawString(false, true, x + 10, y + 15, Color(200, 200, 200, 80), letter2);
		DM.DrawString(false, true, x + 10, y + 25, Color(200, 200, 200, 80), letter3);
		DM.DrawString(false, true, x + 10, y + 35, Color(200, 200, 200, 80), letter4);
		DM.DrawString(false, true, x + 10, y + 45, Color(200, 200, 200, 80), letter5);
		DM.DrawString(false, true, x + 10, y + 55, Color(200, 200, 200, 80), letter6);
		DM.DrawString(false, true, x + 10, y + 65, Color(200, 200, 200, 80), letter7);
	}
}


void CMenu::SideLabel2(int x, int y, int w, int h, Color Fill, Color Text, int letters, const char* letter1, const char* letter2, const char* letter3, const char* letter4, const char* letter5, const char* letter6, const char* letter7, bool &pOption)
{

	DM.DrawString(false, true, x + 10, y + 5, Text, letter1);
	DM.DrawString(false, true, x + 10, y + 15, Text, letter2);
	DM.DrawString(false, true, x + 10, y + 25, Text, letter3);
	DM.DrawString(false, true, x + 10, y + 35, Text, letter4);
	DM.DrawString(false, true, x + 10, y + 45, Text, letter5);


	if (Mousein(x, y, w, h))
	{
		DM.DrawString(false, true, x + 10, y + 5, Color(200, 200, 200, 80), letter1);
		DM.DrawString(false, true, x + 10, y + 15, Color(200, 200, 200, 80), letter2);
		DM.DrawString(false, true, x + 10, y + 25, Color(200, 200, 200, 80), letter3);
		DM.DrawString(false, true, x + 10, y + 35, Color(200, 200, 200, 80), letter4);
		DM.DrawString(false, true, x + 10, y + 45, Color(200, 200, 200, 80), letter5);

	}
}

void CMenu::SideButtonL(int x, int y, int w, int h, Color Fill, Color Text, int letters, const char* letter1, const char* letter2, const char* letter3, const char* letter4, const char* letter5, const char* letter6, const char* letter7, bool &pOption)
{
	DM.DrawRect(x, y, w, h, Fill);
	DM.OutlineRect(x, y, w, h, colBlack);
	DM.DrawString(false, true, x + 10, y + 5, Text, letter1);
	DM.DrawString(false, true, x + 10, y + 25, Text, letter2);
	DM.DrawString(false, true, x + 10, y + 45, Text, letter3);
	DM.DrawString(false, true, x + 10, y + 65, Text, letter4);

	if (Mousein(x, y, w, h))
	{
		DM.DrawRect(x, y, w, h, Color(200, 200, 200, 80));
		DM.OutlineRect(x, y, w, h, colBlack);

		bool RunOnce = false;
		if (GetAsyncKeyState(0x1) & 1)
		{
			//pOption = !pOption;
			//gCvars.Load();
			RunOnce = !RunOnce;

		}

		if (RunOnce)
		{

		}
	}
}
void CMenu::TabDraw(int x, int y, int w, int h)
{

}


void CMenu::TabOperator(int x, int y, int w, int h, bool &tab1, bool &tab2, bool &tab3, bool &tab4, bool &tab5)
{
	DM.DrawRect(x + 70, y, w - 55, h, colDarkGrey);
	DM.DrawRhombusFill(x, y, w / 5 - 20, h, colGrey);
	DM.DrawRhombusFill(x + w / 5 * 1, y, w / 5 - 20, h, colGrey);
	DM.DrawRhombusFill(x + w / 5 * 2, y, w / 5 - 20, h, colGrey);
	DM.DrawRhombusFill(x + w / 5 * 3, y, w / 5 - 20, h, colGrey);
	DM.DrawRhombusFill(x + w / 5 * 4, y, w / 5 - 20, h, colGrey);


	DM.DrawRhombus(x, y, w / 5 - 20, h, colWhite);
	DM.DrawRhombus(x + w / 5 * 1, y, w / 5 - 20, h, colWhite);
	DM.DrawRhombus(x + w / 5 * 2, y, w / 5 - 20, h, colWhite);
	DM.DrawRhombus(x + w / 5 * 3, y, w / 5 - 20, h, colWhite);
	DM.DrawRhombus(x + w / 5 * 4, y, w / 5 - 20, h, colWhite);

	int w2 = w / 5;
	int w5 = w2 / 2.5;

	DM.DrawString(false, true, (x + w5), y + h / 2, menuGreen, "aim");
	DM.DrawString(false, true, (x + w / 5 * 1) + w5, y + h / 1.8, menuGreen, "visuals");
	DM.DrawString(false, true, (x + w / 5 * 2) + w5, y + h / 1.8, menuGreen, "misc");
	DM.DrawString(false, true, (x + w / 5 * 3) + w5, y + h / 1.8, menuGreen, "fun");
	DM.DrawString(false, true, (x + w / 5 * 4) + w5, y + h / 1.8, menuGreen, "HvH");

	if (!tab1 && !tab2 && !tab3 && !tab4 && !tab5)
	{
		tab1 = true;
	}

	if (Mousein(x, y, w / 5 - 20, h))
	{
		DM.DrawRhombus(x, y, w / 5 - 20, h, colBlack);
		if (GetAsyncKeyState(0x1) & 1)
		{
			tab1 = !tab1;
			tab2 = false;
			tab3 = false;
			tab4 = false;
			tab5 = false;

		}
	}

	if (tab1)
	{
		DM.DrawRhombus(x, y, w / 5 - 20, h, menuGreen);
	}

	if (Mousein(x + w / 5 * 1, y, w / 5 - 20, h))
	{
		DM.DrawRhombus(x + w / 5 * 1, y, w / 5 - 20, h, colBlack);
		if (GetAsyncKeyState(0x1) & 1)
		{
			tab1 = false;
			tab2 = !tab2;
			tab3 = false;
			tab4 = false;
			tab5 = false;

		}
	}

	if (tab2)
	{
		DM.DrawRhombus(x + w / 5 * 1, y, w / 5 - 20, h, menuGreen);
	}

	if (Mousein(x + w / 5 * 2, y, w / 5 - 20, h))
	{
		DM.DrawRhombus(x + w / 5 * 2, y, w / 5 - 20, h, colBlack);
		if (GetAsyncKeyState(0x1) & 1)
		{
			tab1 = false;
			tab2 = false;
			tab3 = !tab3;
			tab4 = false;
			tab5 = false;

		}
	}

	if (tab3)
	{
		DM.DrawRhombus(x + w / 5 * 2, y, w / 5 - 20, h, menuGreen);
	}

	if (Mousein(x + w / 5 * 3, y, w / 5 - 20, h))
	{
		DM.DrawRhombus(x + w / 5 * 3, y, w / 5 - 20, h, colBlack);
		if (GetAsyncKeyState(0x1) & 1)
		{
			tab1 = false;
			tab2 = false;
			tab3 = false;
			tab4 = !tab4;
			tab5 = false;

		}
	}

	if (tab4)
	{
		DM.DrawRhombus(x + w / 5 * 3, y, w / 5 - 20, h, menuGreen);
	}

	if (Mousein(x + w / 5 * 4, y, w / 5 - 20, h))
	{
		DM.DrawRhombus(x + w / 5 * 4, y, w / 5 - 20, h, colBlack);
		if (GetAsyncKeyState(0x1) & 1)
		{
			tab1 = false;
			tab2 = false;
			tab3 = false;
			tab4 = false;
			tab5 = !tab5;

		}
	}

	if (tab5)
	{
		DM.DrawRhombus(x + w / 5 * 4, y, w / 5 - 20, h, menuGreen);
	}


}



bool CMenu::MouseClick(int x, int y, int w, int h)
{
	POINT Cur;
	GetCursorPos(&Cur);
	bool Clicked;

	if (Cur.x > x && Cur.x < x + w && Cur.y > y && Cur.y < y + h && GetAsyncKeyState(VK_LBUTTON) & 1)
		Clicked = true;
	else
		Clicked = false;

	return Clicked;
}

bool CMenu::Mousein(int x, int y, int w, int h)
{
	POINT Cur;
	GetCursorPos(&Cur);

	if (Cur.x > x && Cur.x < x + w && Cur.y > y && Cur.y < y + h)
	{
		return true;
	}

	return false;
}

void CMenu::GetMouse()
{
	POINT Cur;
	GetCursorPos(&Cur);
	//gDrawManager.DrawRect(Cur.x, Cur.y, 10, 10, colBlack);

	for (int i = 0; i <= 9; i++)
	{
		DM.DrawLine(Cur.x, Cur.y, Cur.x + i, Cur.y + 11, colWhite);
	}
	for (int i = 0; i <= 7; i++)
	{
		DM.DrawLine(Cur.x, Cur.y + 9 + i, Cur.x + i, Cur.y + 9, colWhite);
	}
	for (int i = 0; i <= 3; i++)
	{
		DM.DrawLine(Cur.x + 6 + i, Cur.y + 11, Cur.x, Cur.y + i, colWhite);
	}
	DM.DrawLine(Cur.x + 5, Cur.y + 11, Cur.x + 8, Cur.y + 18, colWhite);
	DM.DrawLine(Cur.x + 4, Cur.y + 11, Cur.x + 7, Cur.y + 18, colWhite);

	DM.DrawLine(Cur.x, Cur.y, Cur.x, Cur.y + 17, colBlack);
	DM.DrawLine(Cur.x, Cur.y + 17, Cur.x + 3, Cur.y + 14, colBlack);

	DM.DrawLine(Cur.x + 4, Cur.y + 14, Cur.x + 7, Cur.y + 19, colBlack);
	DM.DrawLine(Cur.x + 5, Cur.y + 14, Cur.x + 7, Cur.y + 19, colBlack);

	DM.DrawLine(Cur.x + 7, Cur.y + 18, Cur.x + 9, Cur.y + 18, colBlack);

	DM.DrawLine(Cur.x + 10, Cur.y + 18, Cur.x + 7, Cur.y + 12, colBlack);

	DM.DrawLine(Cur.x + 7, Cur.y + 12, Cur.x + 12, Cur.y + 12, colBlack);

	DM.DrawLine(Cur.x + 12, Cur.y + 12, Cur.x, Cur.y, colBlack);
}
//where is the code where you move menu
void CMenu::DrawCheckBox(int x, int y, Color colour, const char* fmt, bool &option, Color back, const char* desc)
{
	POINT Cur;
	GetCursorPos(&Cur);



	DM.DrawString(false, true, x, y, colWhite, fmt);
	DM.DrawRect(x + 130, y, 15, 15, colour);
	DM.OutlineRect(x + 130, y, 15, 15, colBlack);

	if (Mousein(x + 130, y, 15, 15))
	{
		DM.DrawRect(x + 130, y, 15, 15, Color(120, 120, 120, 40));

	}

	if (Mousein(x, y, 145, 145))
	{
		if (pOptions.Tooltip)
		{
			DM.DrawString(false, true, pOptions.Menu_X + 20, pOptions.Menu_Y + 15, menuGreen, desc);
		}
	}

	if (Mousein(x + 130, y, 15, 15))
	{
		if (GetAsyncKeyState(0x01) & 1)
		{
			option = !option;
		}
	}

	if (option){
		DM.DrawRect(x + 130, y, 15, 15, colWhite);
		DM.OutlineRect(x + 130, y, 15, 15, colBlack);
	}


}

void CMenu::DrawCheckBoxF(int x, int y, Color colour, const char* fmt, float &option, Color back, const char* desc)
{
	POINT Cur;
	GetCursorPos(&Cur);



	DM.DrawString(false, true, x, y, colWhite, fmt);
	DM.DrawRect(x + 130, y, 15, 15, colour);
	DM.OutlineRect(x + 130, y, 15, 15, colBlack);

	if (Mousein(x + 130, y, 15, 15))
	{
		DM.DrawRect(x + 130, y, 15, 15, Color(120, 120, 120, 40));

	}

	if (Mousein(x + 130, y, 15, 15))
	{
		if (pOptions.Tooltip)
		{
			DM.DrawString(false, true, pOptions.Menu_X + 20, pOptions.Menu_Y + 15, menuGreen, desc);
		}
	}

	if (Mousein(x + 130, y, 15, 15))
	{
		if (GetAsyncKeyState(0x01) & 1)
		{
			option = !option;
		}
	}

	if (option){
		DM.DrawRect(x + 130, y, 15, 15, colWhite);
		DM.OutlineRect(x + 130, y, 15, 15, colBlack);
	}


}

void CMenu::DrawListBoxThing(int x, int y, int w, int h, int letters, Color background, Color text, const char* fmt)
{
	gDrawManager.DrawRect(x, y, w, h, background);
	gDrawManager.OutlineRect(x, y, w, h, colMenu);
	gDrawManager.DrawLine(x + 8, y, x + 10 + letters * 10, y, colWhite2);
	gDrawManager.DrawString(false, false, x + 17, y - 12, text, fmt);
}

//float sliderx2 = 0;
char SliderValue2[101];

//float sliderx = 0;
char SliderValue[101];

void CMenu::DrawSliderINT(float x, float y, float w, int min, int max, int &SmoothValue, int &sliderx2)
{

	float sliderw = 10.f;
	float sliderh = 15.f;

	POINT cursor;
	GetCursorPos(&cursor);

	float clickx = sliderx2 - cursor.x;
	float moveto = sliderx2 - clickx - sliderw / 2;
	if (cursor.x >= x - sliderw / 2 && cursor.y >= y - 2 && cursor.x <= x + w + sliderw / 2 && cursor.y <= y + sliderh + 2)//this checking if ure n slider?yes
	{
		if (GetAsyncKeyState(0x1))
		{
			sliderx2 = moveto;
		}
	}
	if (sliderx2 < x - sliderw / 2){ sliderx2 = x - sliderw / 2; }
	if (sliderx2 > x + w - sliderw / 2){ sliderx2 = x + w - sliderw / 2; }
	gDrawManager.DrawRect(x, y, w, sliderh, colGrey);
	gDrawManager.DrawRect(x, y, w, sliderh, colWhite2);
	gDrawManager.OutlineRect(x, y, w, sliderh, colBlack);
	gDrawManager.DrawRect(sliderx2, y, sliderw, sliderh, colBlack);
	gDrawManager.DrawRect(x, y, sliderx2 - x, sliderh, colMenu);
	SmoothValue = ((max - min) / (w))*(sliderx2 - x + sliderw / 2);
	sprintf_s(SliderValue2, " %1.0f", SmoothValue);

	gDrawManager.DrawString(false, false, x + 5, y, colBlack, SliderValue2);

}

void CMenu::DrawSlider(float x, float y, float w, int min, int max, float &SmoothValue, int &sliderx, const char* option)
{

	float sliderw = 10.f;
	float sliderh = 8.0f;

	POINT cursor;
	GetCursorPos(&cursor);

	float clickx = sliderx - cursor.x;
	float moveto = sliderx - clickx - sliderw / 2;
	if (cursor.x >= x - sliderw / 2 && cursor.y >= y - 2 && cursor.x <= x + w + sliderw / 2 && cursor.y <= y + sliderh + 2)//this checking if ure n slider?yes
	{
		if (GetAsyncKeyState(0x1))
		{
			sliderx = moveto;
		}
	}
	if (sliderx < x - sliderw / 2){ sliderx = x - sliderw / 2; }
	if (sliderx > x + w - sliderw / 2){ sliderx = x + w - sliderw / 2; }
	gDrawManager.DrawRect(x, y, w, sliderh, colGrey);
	gDrawManager.DrawRect(x, y, w, sliderh, colGrey);
	gDrawManager.DrawRect(x, y, sliderx - x, sliderh, menuGreen);
	gDrawManager.OutlineRect(x, y, w, sliderh, colWhite);
	gDrawManager.DrawRect(sliderx, y - 3.5, sliderw, 15, colBlack);
	gDrawManager.OutlineRect(sliderx, y - 3.5, sliderw, 15, colWhite);
	SmoothValue = ((max - min) / (w))*(sliderx - x + sliderw / 2);
	sprintf_s(SliderValue, " %1.0f", SmoothValue);

	gDrawManager.DrawString(false, true, x + 5, y - 30, colWhite, option);
	//x + 200
	gDrawManager.DrawString(false, true, x + w + 10, y  - 3, colWhite, SliderValue);

}



void CMenu::DrawCombobox(int x, int y, int w, int h, Color Outline, Color back, Color String, const char* title, const char* item1, const char* item2, float &option1, float &option2, bool &Click, bool &Clicker, const char* desc)
{
	POINT Cur;
	GetCursorPos(&Cur);

	gDrawManager.DrawRect(x, y, w, h, back);
	gDrawManager.OutlineRect(x, y, w, h, Outline);
	gDrawManager.DrawString(false, true, x + 10, y, String, title);

	if (Mousein(x, y, w, h))
	{
		gDrawManager.DrawRect(x, y, w, h, Color(220, 220, 220, 80));
		if (pOptions.Tooltip)
		{
			DM.DrawString(false, true, pOptions.Menu_X + 20, pOptions.Menu_Y + 15, menuGreen, desc);
		}
	}

	if (Cur.x > x && Cur.x < x + w && Cur.y > y && Cur.y < y + h)
	{
		if (GetAsyncKeyState(0x01) & 1)
		{
			Click = !Click;
		}
	}

	if (Click){
		gDrawManager.DrawRect(x, y + h * 1, w, h, back);
		gDrawManager.OutlineRect(x, y + h * 1, w, h, Outline);
		gDrawManager.DrawString(false, true, x + 10, y + h * 1, String, item1);

		gDrawManager.DrawRect(x, y + h * 2, w, h, back);
		gDrawManager.OutlineRect(x, y + h * 2, w, h, Outline);
		gDrawManager.DrawString(false, true, x + 10, y + h * 2, String, item2);

		if (Mousein(x, y + h * 1, w, h))
		{
			gDrawManager.DrawRect(x, y + h * 1, w, h, Color(220, 220, 220, 80));

			if (GetAsyncKeyState(0x01) & 1)
			{
				option1 = !option1;
				option2 = false;
				Click = false;
				Clicker = true;
			}
		}

		if (Mousein(x, y + h * 2, w, h))
		{
			gDrawManager.DrawRect(x, y + h * 2, w, h, Color(220, 220, 220, 80));

			if (GetAsyncKeyState(0x01) & 1)
			{
				option2 = !option2;
				option1 = false;
				Click = false;
				Clicker = true;
			}
		}
	}

	if (Clicker)
	{
		if (option1 == true)
		{
			gDrawManager.DrawRect(x, y, w, h, back);
			gDrawManager.OutlineRect(x, y, w, h, Outline);
			gDrawManager.DrawString(false, true, x + 10, y, String, item1);
		}
		else if (option2 == true)
		{
			gDrawManager.DrawRect(x, y, w, h, back);
			gDrawManager.OutlineRect(x, y, w, h, Outline);
			gDrawManager.DrawString(false, true, x + 10, y, String, item2);
		}
	}
}

bool Move[8][2];
POINT Cursor;
bool CMenu::Mover(int &X, int &Y, int W, int H, int index)
{
	for (int i = 0; i < 8; i++)
	if (Move[i][0] && i != index)
		return false;

	POINT Cur;
	GetCursorPos(&Cur);

	if (GetAsyncKeyState(VK_LBUTTON) < 0)
	{
		if (Cur.x > X && Cur.x < X + W && Cur.y >(Y - 20 - 3) && Cur.y < (Y - 20 - 3) + H || Move[index][0])
		{
			Move[index][0] = true;

			if (!Move[index][1])
			{
				Cursor.x = Cur.x - X;
				Cursor.y = Cur.y - Y;
				Move[index][1] = true;

			}
		}
		else
		{
			Move[index][0] = false;
			Move[index][1] = false;
		}
	}

	if (GetAsyncKeyState(VK_LBUTTON) == 0 && Move[index][0])
	{
		Move[index][0] = false;
		Move[index][1] = false;
	}

	if (Move[index][0])
	{
		X = Cur.x - Cursor.x;
		Y = Cur.y - Cursor.y;
	}

	return true;
}

bool Move2[8][2];
POINT Cursor2;
bool CMenu::MoverWH(int &X, int &Y, int W, int H, int index)
{
	for (int i = 0; i < 8; i++)
	if (Move2[i][0] && i != index)
		return false;

	POINT Cur2;
	GetCursorPos(&Cur2);

	if (GetAsyncKeyState(VK_LBUTTON) < 0)
	{
		if (Cur2.x > X && Cur2.x < X + W && Cur2.y >(Y - 20 - 3) && Cur2.y < (Y - 20 - 3) + H || Move2[index][0])
		{
			Move2[index][0] = true;

			if (!Move2[index][1])
			{
				Cursor2.x = Cur2.x - X;
				Cursor2.y = Cur2.y - Y;
				Move2[index][1] = true;

			}
		}
		else
		{
			Move2[index][0] = false;
			Move2[index][1] = false;
		}
	}

	if (GetAsyncKeyState(VK_LBUTTON) == 0 && Move2[index][0])
	{
		Move2[index][0] = false;
		Move2[index][1] = false;
	}

	if (Move2[index][0])
	{
		X = Cur2.x - Cursor2.x;
		Y = Cur2.y - Cursor2.y;
	}

	return true;
}


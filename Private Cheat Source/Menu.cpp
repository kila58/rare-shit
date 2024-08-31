#include "Menu.h"
#include "CDrawManager.h"
#include "Control Variables.h"
#include "File Manager.h"

//EEngine pEngine;



void DrawLinedBox(int x, int y, int w, int h, int p, Color color)
{
	ALX.pDrawManager->FillRGBA(x, y, w, p, color);

	ALX.pDrawManager->FillRGBA(x, y, p, h, color);

	ALX.pDrawManager->FillRGBA(x + w, y, p, h, color);

	ALX.pDrawManager->FillRGBA(x, y + h, w + p, p, color);
}


#define DM ALX.pDrawManager->
#define M ALX.pMenu->

void CMenu::Render(int x, int y, int w, int h)
{
	//Main square
	ALX.pDrawManager->FillRGBA(x - 200, y - 170, 900, 370, Color(35,35,25,250));
	
	ALX.pDrawManager->DrawGradient(x - 205, y - 170, 5, 370, GRADIENT_VERTICAL_FILL, colGrey, colGrey);
	ALX.pDrawManager->DrawGradient(x - 205, y + 200, 905, 5, GRADIENT_VERTICAL_FILL, colGrey, colGrey);
	ALX.pDrawManager->DrawGradient(x + 700, y - 170, 5, 375, GRADIENT_VERTICAL_FILL, colGrey, colGrey);

	//ALX.pDrawManager->OutlineRect1(x - 200, y - 160, 900, 240, colBlack);
	//ALX.pDrawManager->OutlineRect1(x - 205, y - 205, 910, 405, colBlack);

	ALX.pDrawManager->FillRGBA(x - 200, y - 160, 175, 360, ClrDGrey);
	ALX.pDrawManager->OutlineRect1(x - 200, y - 160, 175, 360, colBlack);
//	ALX.pDrawManager->FillRGBA(x - 200, y + 140, 175, 2, colBlack);
//	ALX.pDrawManager->FillRGBA(x - 25, y - 160, 2, 350, colBlack);
	ALX.pDrawManager->DrawGradient(x - 205, y - 175, 910, 20, GRADIENT_VERTICAL_FILL, colGrey, colGrey);
	ALX.pDrawManager->DrawString1(true,x - 190, y - 173, colWhite, "CS:GO MULTIHACK ");
	//DrawLinedBox(x - 200, y - 200, 900, 445, 2,colBlack);
    DrawLinedBox(x - 205, y - 175, 910, 380, 1, colBlack);

	//tabs
	ALX.pDrawManager->DrawString1(true,x - 180, y - 140, colWhite,"1");
	ALX.pDrawManager->DrawString1(true,x - 180, y - 100, colWhite,"2");
	ALX.pDrawManager->DrawString1(true,x - 180, y - 60, colWhite, "3");
	ALX.pDrawManager->DrawString1(true,x - 180, y - 20, colWhite, "4");
	ALX.pDrawManager->DrawString1(true,x - 180, y + 20, colWhite, "5");
	ALX.pDrawManager->DrawString1(true,x - 180, y + 60, colWhite, "6");
	ALX.pDrawManager->DrawString1(true, x - 180, y + 100, colWhite, "7");

	

	//inner squares.





	//ALX.pDrawManager->FillRGBA(x - 10, y - 135, 15, 15,colBlack);
		//ALX.pDrawManager->FillRGBA(x - 6, y - 131, 7.5, 7.5, Color(255, 153, 0,255));
	//TABS 

	if (ALX.pEnable->AimEnable)
	{
		ALX.pDrawManager->FillRGBA(x - 20, y - 145, 350, 250, ClrLGrey);
		ALX.pDrawManager->FillRGBA(x - 20, y - 145, 350, 25, colBlack);

		ALX.pDrawManager->DrawString1(true, x - 10, y - 140, colWhite, "Main");
		

		ALX.pDrawManager->FillRGBA(x + 350, y - 145, 340, 250, ClrLGrey);
		ALX.pDrawManager->FillRGBA(x + 350, y - 145, 340, 25, colBlack);

		ALX.pDrawManager->DrawString1(true, x + 360, y - 140, colWhite, "Options");

		ALX.pDrawManager->FillRGBA(x - 20, y + 115, 705, 75, ClrLGrey);

		ALX.pMenu->DrawCheckBox(x , y - 111, "Active", ALX.pCvar->aimbot);
		ALX.pMenu->DrawCheckBox(x , y - 91, "Autowall", ALX.pCvar->autowall);
		ALX.pMenu->DrawCheckBox(x , y - 71, "AutoShoot", ALX.pCvar->autoshoot);
		ALX.pMenu->DrawCheckBox(x , y - 51, "Spray Control", ALX.pCvar->rcs);
		ALX.pMenu->DrawCheckBox(x , y - 31, "Prediction", ALX.pCvar->prediction);
		ALX.pMenu->DrawCheckBox(x , y - 11, "HitScan", ALX.pCvar->hitscan);
		ALX.pMenu->DrawCheckBox(x, y + 11, "Perfect Silent", ALX.pCvar->silent);

		//ALX.pMenu->DrawCheckBox(x + 370, y - 111, "Recoil Control System", ALX.pCvar->rcs);
	
		if (ALX.pCvar->aim_head == 0.0f && ALX.pCvar->aim_chest == 0.0f && ALX.pCvar->aim_neck == 0.0f && ALX.pCvar->aim_stomach == 0.0f)
		{
			ALX.pCvar->aim_head = 1.0f;
		}

		ALX.pDrawManager->FillRGBA(x + 370, y - 111, 310, 125, ClrDGrey);
		ALX.pDrawManager->FillRGBA(x + 370, y - 111, 310, 25, colBlack);
		ALX.pDrawManager->DrawString1(true, x + 490, y - 105, colWhite, "Aimspot");
		ALX.pDrawManager->DrawString1(true, x + 375, y - 83, colWhite, "Head");
		ALX.pDrawManager->DrawString1(true, x + 375, y - 58, colWhite, "Neck");
		ALX.pDrawManager->DrawString1(true, x + 375, y - 33, colWhite, "Chest");
		ALX.pDrawManager->DrawString1(true, x + 375, y - 8, colWhite, "Stomach");

		if (Mousein(x + 370, y - 86, 310, 25))
		{
			ALX.pDrawManager->FillRGBA(x + 370, y - 86, 310, 25,Color(220,220,220,120));
		}
		
		if (MouseClick(x + 370, y - 86, 310, 25))
		{
			ALX.pCvar->aim_chest = 0.0f;
			ALX.pCvar->aim_neck = 0.0f;
			ALX.pCvar->aim_stomach = 0.0f;
			ALX.pCvar->aim_head = 1.0f;
		}

		if (ALX.pCvar->aim_head)
		{
			ALX.pDrawManager->FillRGBA(x + 370, y - 84, 310, 23, colBlack);
			ALX.pDrawManager->DrawString1(true, x + 375, y - 83, colWhite, "Head");
		}

		if (Mousein(x + 370, y - 61, 310, 25))
		{
			ALX.pDrawManager->FillRGBA(x + 370, y - 61, 310, 25, Color(220, 220, 220, 120));
		}

		if (MouseClick(x + 370, y - 61, 310, 25))
		{
			ALX.pCvar->aim_chest = 0.0f;
			ALX.pCvar->aim_neck = 1.0f;
			ALX.pCvar->aim_stomach = 0.0f;
			ALX.pCvar->aim_head = 0.0f;
		}

		if (ALX.pCvar->aim_neck)
		{
			ALX.pDrawManager->FillRGBA(x + 370, y - 61, 310, 25, colBlack);
			ALX.pDrawManager->DrawString1(true, x + 375, y - 58, colWhite, "Neck");
		}

		if (Mousein(x + 370, y - 36, 310, 25))
		{
			ALX.pDrawManager->FillRGBA(x + 370, y - 36, 310, 25, Color(220, 220, 220, 120));
		}

		if (MouseClick(x + 370, y - 36, 310, 25))
		{
			ALX.pCvar->aim_chest = 1.0f;
			ALX.pCvar->aim_neck = 0.0f;
			ALX.pCvar->aim_stomach = 0.0f;
			ALX.pCvar->aim_head = 0.0f;
		}

		if (ALX.pCvar->aim_chest)
		{
			ALX.pDrawManager->FillRGBA(x + 370, y - 36, 310, 25, colBlack);
			ALX.pDrawManager->DrawString1(true, x + 375, y - 33, colWhite, "Chest");
		}

		if (Mousein(x + 370, y - 11, 310, 25))
		{
			ALX.pDrawManager->FillRGBA(x + 370, y - 11, 310, 25, Color(220, 220, 220, 120));
		}

		if (MouseClick(x + 370, y - 11, 310, 25))
		{
			ALX.pCvar->aim_chest = 0.0f;
			ALX.pCvar->aim_neck = 0.0f;
			ALX.pCvar->aim_stomach = 1.0f;
			ALX.pCvar->aim_head = 0.0f;
		}

		if (ALX.pCvar->aim_stomach)
		{
			ALX.pDrawManager->FillRGBA(x + 370, y - 11, 310, 25, colBlack);
			ALX.pDrawManager->DrawString1(true, x + 375, y - 8, colWhite, "Stomach");
		}

	//	ALX.pMenu->DrawCheckBox(x + 370, y - 51, "Silent Aim", ALX.pCvar->silent);



		//ALX.pMenu->KeyPicker(x + 120, y - 111, 100, 20, "Aim Key",ALX.pOptions->Click,ALX.pOptions->Clicker,ALX.pOptions->Clicky);
		ALX.pMenu->DrawSlider(x, y + 81, 233, 0, 180, ALX.pCvar->fov, ALX.pOptions->s1, "Field Of View");
		ALX.pMenu->DrawSlider(x + 370, y + 81, 233, 0, 100, ALX.pCvar->smooth, ALX.pOptions->s2, "Smoothness");

		ALX.pMenu->DrawCombobox(x + 370, y + 21, 100, 20, colBlack, colBlack, colWhite, "Off", "Auto", "Key", ALX.pCvar->aimonfire, ALX.pCvar->aimkey, ALX.pOptions->KEYCLICK, ALX.pOptions->KEYCLICKER, "Aim Toggle Selection");
		ALX.pDrawManager->DrawString1(true, x + 370 + 108, y + 21, colWhite, "Aim Type");
		//ALX.pMenu->DrawCheckBox(x + 10, y + 31, "Silent Aim", ALX.pCvar->silent);
		//ALX.pMenu->DrawCheckBox(x + 10, y + 51, "AA2", ALX.pCvar->aa2);
		//ALX.pMenu->DrawCheckBox(x + 10, y + 71, "AA1", ALX.pCvar->aa1);
		//ALX.pMenu->DrawCheckBox(x + 10, y + 91, "AA4", ALX.pCvar->aa4);
	}

	if (ALX.pEnable->TriggerEnable)
	{
		//ALX.pMenu->DrawCheckBox(x, y - 41, "Standalone RCS", ALX.pCvar->standrcs);
		ALX.pMenu->DrawCheckBox(x, y - 21, "Autostrafe", ALX.pCvar->autostrafe);
		ALX.pMenu->DrawCheckBox(x, y - 1, "Visible", ALX.pCvar->autostrafe_vis);
		ALX.pMenu->DrawCheckBox(x, y + 21, "Sideways", ALX.pCvar->autostrafe_sideways);
		ALX.pMenu->DrawCheckBox(x, y + 41, "Head Triggerbot", ALX.pCvar->head_trigger);
		ALX.pMenu->DrawCheckBox(x, y + 61, "Stop Crouch", ALX.pCvar->stop_crouch);

		ALX.pMenu->DrawSlider(x, y + 140, 150, 0, 13, ALX.pCvar->fakelag, ALX.pCvar->fakelag_s, "Fake Lag");
	}

	if (ALX.pEnable->VisualsEnable)
	{
		ALX.pDrawManager->FillRGBA(x - 20, y - 145, 350, 250, ClrLGrey);
		ALX.pDrawManager->FillRGBA(x - 20, y - 145, 350, 25, colBlack);

		ALX.pDrawManager->DrawString1(true, x - 10, y - 140, colWhite, "Main");


		ALX.pDrawManager->FillRGBA(x + 350, y - 145, 340, 250, ClrLGrey);
		ALX.pDrawManager->FillRGBA(x + 350, y - 145, 340, 25, colBlack);

		ALX.pDrawManager->DrawString1(true, x + 360, y - 140, colWhite, "Preview");

		ALX.pDrawManager->FillRGBA(x - 20, y + 115, 705, 75, ClrLGrey);

		//ALX.pMenu->DrawCheckBox(x, y - 111, "Box", ALX.pCvar->aimbot);
		
		//ALX.pMenu->DrawCheckBox(x, y - 91, "Name", ALX.pCvar->Name);

		ALX.pMenu->DrawCheckBox(x, y - 41, "Name", ALX.pCvar->Name);

		
		ALX.pMenu->DrawCheckBox(x, y - 21, "Weapon", ALX.pCvar->Weapons);
		ALX.pMenu->DrawCheckBox(x, y - 1, "Skeleton", ALX.pCvar->Skeleton);
		ALX.pMenu->DrawCheckBox(x, y + 21, "Chams", ALX.pCvar->chams);
		ALX.pMenu->DrawCheckBox(x, y + 41, "Shader Chams", ALX.pCvar->shaderchams);
		ALX.pMenu->DrawCheckBox(x, y + 61, "Glow", ALX.pCvar->glow);

	
			ALX.pMenu->DrawCombobox(x, y - 81, 100, 20, colBlack, colBlack, colWhite, "Off", "Broken", "Bottom", ALX.pCvar->hbarL, ALX.pCvar->hbarB, ALX.pOptions->SKEYCLICK, ALX.pOptions->SKEYCLICKER, "Picks either bottom or left sided health bar.");

			ALX.pDrawManager->DrawString1(true, x + 108, y - 81, colWhite, "Healthbar Type");
		

		ALX.pMenu->DrawCombobox(x, y - 111, 100, 20, colBlack, colBlack, colWhite, "Off", "Normal", "Frame", ALX.pCvar->boxesp, ALX.pCvar->CornerBox, ALX.pOptions->ESPCLICK, ALX.pOptions->ESPCLICKER, "Picks either a Normal or Frame ESP Box.");
		ALX.pDrawManager->DrawString1(true, x + 108, y - 111, colWhite, "Box Type");

		if (ALX.pCvar->CornerBox)
		{
			ALX.pDrawManager->DrawOC(x + 450, y - 100, 80, 200, colBlue);
		}

		if (ALX.pCvar->boxesp)
		{
			ALX.pDrawManager->OutlineRect1(x + 450, y - 100, 80, 200, colBlue);
		}

		if (ALX.pCvar->Name)
		{
			ALX.pDrawManager->DrawString1(true, x + 430, y - 120, colWhite, "Gaben");
		}

	
	}

	if (ALX.pEnable->RadarEnable)
	{
		//ALX.pMenu->DrawSlider(x, y - 81, 233, 0, 15, ALX.pCvar->aim_human_scale, ALX.pOptions->human_scale_s, "Humanize Scale");
		//ALX.pMenu->DrawSlider(x, y - 11, 233, 1, 20, ALX.pCvar->aim_human_speed, ALX.pOptions->human_speed_s, "Humanize Speed");
	}

	if (ALX.pEnable->MiscEnable)
	{
		ALX.pDrawManager->FillRGBA(x - 20, y - 145, 350, 250, ClrLGrey);
		ALX.pDrawManager->FillRGBA(x - 20, y - 145, 350, 25, colBlack);

		ALX.pDrawManager->DrawString1(true, x - 10, y - 140, colWhite, "Main");


		ALX.pDrawManager->FillRGBA(x + 350, y - 145, 340, 250, ClrLGrey);
		ALX.pDrawManager->FillRGBA(x + 350, y - 145, 340, 25, colBlack);

		ALX.pDrawManager->DrawString1(true, x + 360, y - 140, colWhite, "Options");

		ALX.pDrawManager->FillRGBA(x - 20, y + 115, 705, 75, ClrLGrey);

		ALX.pMenu->DrawCheckBox(x, y - 111, "No Recoil", ALX.pCvar->norecoil);
		ALX.pMenu->DrawCheckBox(x, y - 71, "No Spread", ALX.pCvar->nospread);
		ALX.pMenu->DrawCheckBox(x, y - 91, "No Visual Recoil", ALX.pCvar->novisualrecoil);
		ALX.pMenu->DrawCheckBox(x, y - 51, "Autopistol", ALX.pCvar->autopistol);
		ALX.pMenu->DrawCheckBox(x, y - 31, "Bunnyhop", ALX.pCvar->Bunny);
		//ALX.pMenu->DrawCheckBox(x, y - 11, "Barrel", ALX.pCvar->barrels);
		//ALX.pMenu->DrawCheckBox(x, y + 11, "Skins", ALX.pCvar->skins);
		//ALX.pMenu->DrawCheckBox(x, y + 31, "Bounding Box", ALX.pCvar->bbox);
		//ALX.pMenu->DrawCheckBox(x, y + 51, "AABB", ALX.pCvar->AABB);
		//ALX.pMenu->DrawCheckBox(x, y + 11, "Silent Aim", ALX.pCvar->silent);

		//ALX.pMenu->DrawSlider(x, y + 81, 233, 0, 14, ALX.pCvar->fakelag, ALX.pOptions->s5, "FakeLag");
		

	}

	if (ALX.pEnable->AntiaimEnable)
	{
		ALX.pDrawManager->FillRGBA(x - 20, y - 145, 350, 250, ClrLGrey);
		ALX.pDrawManager->FillRGBA(x - 20, y - 145, 350, 25, colBlack);

		ALX.pDrawManager->DrawString1(true, x - 10, y - 140, colWhite, "Main");


		ALX.pDrawManager->FillRGBA(x + 350, y - 145, 340, 250, ClrLGrey);
		ALX.pDrawManager->FillRGBA(x + 350, y - 145, 340, 25, colBlack);

		ALX.pDrawManager->DrawString1(true, x + 360, y - 140, colWhite, "Options");

		ALX.pDrawManager->FillRGBA(x - 20, y + 115, 705, 75, ClrLGrey);

		ALX.pMenu->DrawCheckBox(x, y - 111, "Anti Aim", ALX.pCvar->AntiAim);
		//ALX.pMenu->DrawCheckBox(x, y - 91, "Fakedown", ALX.pCvar->AntiAim2);
	}

	if (ALX.pEnable->ConfigEnable)
	{

	}
	//DrawMouse

	ALX.pMenu->TabOperator(x, y, w, h, ALX.pEnable->AimEnable, ALX.pEnable->TriggerEnable, ALX.pEnable->VisualsEnable, ALX.pEnable->RadarEnable, ALX.pEnable->MiscEnable, ALX.pEnable->AntiaimEnable,ALX.pEnable->ConfigEnable);
	ALX.pMenu->GetMouse();


	//Menu Mover
	ALX.pMenu->MoveMenu(ALX.pOptions->Menu_X, ALX.pOptions->Menu_Y, 900, 80,0);


}

void CMenu::AddTab(int x, int y, int w, int h, Color Fill, Color Outline, const char* Text)
{
	ALX.pDrawManager->FillRGBA(x, y, w, h, Fill);
	ALX.pDrawManager->OutlineRect1(x, y, w, h, Outline);
	ALX.pDrawManager->DrawString1(false, x + 20, y + 10, colWhite, Text);
}

void CMenu::AddOtherTab(int x, int y, int w, int h, Color Fill, Color Outline, const char* Text)
{
	
}



void CMenu::SideButton(int x, int y, int w, int h, Color Fill, Color Text, int letters, const char* letter1, const char* letter2, const char* letter3, const char* letter4, const char* letter5, const char* letter6, const char* letter7,bool &pOption)
{
	ALX.pDrawManager->FillRGBA(x, y, w, h, Fill);
	ALX.pDrawManager->OutlineRect1(x, y, w, h, colBlack);
	ALX.pDrawManager->DrawString1(true, x + 10, y + 5, Text, letter1);
	ALX.pDrawManager->DrawString1(true, x + 10, y + 25, Text, letter2);
	ALX.pDrawManager->DrawString1(true, x + 10, y + 45, Text, letter3);
	ALX.pDrawManager->DrawString1(true, x + 10, y + 65, Text, letter4);

	if (Mousein(x, y, w, h))
	{
		ALX.pDrawManager->FillRGBA(x, y, w, h, Color(200,200,200,80));
		ALX.pDrawManager->OutlineRect1(x, y, w, h, colBlack);

		if (GetAsyncKeyState(0x1) & 1)
		{
			//pOption = !pOption;
			ALX.pCvar->Save();
		}
	}
}

void CMenu::SideLabel(int x, int y, int w, int h, Color Fill, Color Text, int letters, const char* letter1, const char* letter2, const char* letter3, const char* letter4, const char* letter5, const char* letter6, const char* letter7, bool &pOption)
{

	ALX.pDrawManager->DrawString1(true, x + 10, y + 5, Text, letter1);
	ALX.pDrawManager->DrawString1(true, x + 10, y + 15, Text, letter2);
	ALX.pDrawManager->DrawString1(true, x + 10, y + 25, Text, letter3);
	ALX.pDrawManager->DrawString1(true, x + 10, y + 35, Text, letter4);
	ALX.pDrawManager->DrawString1(true, x + 10, y + 45, Text, letter5);
	ALX.pDrawManager->DrawString1(true, x + 10, y + 55, Text, letter6);
	ALX.pDrawManager->DrawString1(true, x + 10, y + 65, Text, letter7);

	if (Mousein(x, y, w, h))
	{
		ALX.pDrawManager->DrawString1(true, x + 10, y + 5, Color(200,200,200,80), letter1);
		ALX.pDrawManager->DrawString1(true, x + 10, y + 15, Color(200, 200, 200, 80), letter2);
		ALX.pDrawManager->DrawString1(true, x + 10, y + 25, Color(200, 200, 200, 80), letter3);
		ALX.pDrawManager->DrawString1(true, x + 10, y + 35, Color(200, 200, 200, 80), letter4);
		ALX.pDrawManager->DrawString1(true, x + 10, y + 45, Color(200, 200, 200, 80), letter5);
		ALX.pDrawManager->DrawString1(true, x + 10, y + 55, Color(200, 200, 200, 80), letter6);
		ALX.pDrawManager->DrawString1(true, x + 10, y + 65, Color(200, 200, 200, 80), letter7);
	}
}


void CMenu::SideLabel2(int x, int y, int w, int h, Color Fill, Color Text, int letters, const char* letter1, const char* letter2, const char* letter3, const char* letter4, const char* letter5, const char* letter6, const char* letter7, bool &pOption)
{

	ALX.pDrawManager->DrawString1(true, x + 10, y + 5, Text, letter1);
	ALX.pDrawManager->DrawString1(true, x + 10, y + 15, Text, letter2);
	ALX.pDrawManager->DrawString1(true, x + 10, y + 25, Text, letter3);
	ALX.pDrawManager->DrawString1(true, x + 10, y + 35, Text, letter4);
	ALX.pDrawManager->DrawString1(true, x + 10, y + 45, Text, letter5);


	if (Mousein(x, y, w, h))
	{
		ALX.pDrawManager->DrawString1(true, x + 10, y + 5, Color(200, 200, 200, 80), letter1);
		ALX.pDrawManager->DrawString1(true, x + 10, y + 15, Color(200, 200, 200, 80), letter2);
		ALX.pDrawManager->DrawString1(true, x + 10, y + 25, Color(200, 200, 200, 80), letter3);
		ALX.pDrawManager->DrawString1(true, x + 10, y + 35, Color(200, 200, 200, 80), letter4);
		ALX.pDrawManager->DrawString1(true, x + 10, y + 45, Color(200, 200, 200, 80), letter5);

	}
}

void CMenu::SideButtonL(int x, int y, int w, int h, Color Fill, Color Text, int letters, const char* letter1, const char* letter2, const char* letter3, const char* letter4, const char* letter5, const char* letter6, const char* letter7, bool &pOption)
{
	ALX.pDrawManager->FillRGBA(x, y, w, h, Fill);
	ALX.pDrawManager->OutlineRect1(x, y, w, h, colBlack);
	ALX.pDrawManager->DrawString1(true, x + 10, y + 5, Text, letter1);
	ALX.pDrawManager->DrawString1(true, x + 10, y + 25, Text, letter2);
	ALX.pDrawManager->DrawString1(true, x + 10, y + 45, Text, letter3);
	ALX.pDrawManager->DrawString1(true, x + 10, y + 65, Text, letter4);

	if (Mousein(x, y, w, h))
	{
		ALX.pDrawManager->FillRGBA(x, y, w, h, Color(200, 200, 200, 80));
		ALX.pDrawManager->OutlineRect1(x, y, w, h, colBlack);

		bool RunOnce = false;
		if (GetAsyncKeyState(0x1) & 1)
		{

			RunOnce = !RunOnce;
			
		}

		if (RunOnce)
		{

			ALX.pCvar->CornerBox = true;
			ALX.pCvar->Name = true;
			ALX.pCvar->Healthbar = true;
			ALX.pCvar->Bunny = true;
			ALX.pCvar->shaderchams = true;
			ALX.pCvar->aimbot = true;
			ALX.pCvar->prediction = true;

			ALX.pCvar->fov = 360.0f;
		}
	}
}
void CMenu::DrawLineBox(int x, int y,int howfaryo, int w, int h, Color Line, Color bground, const char* Text)
{
	ALX.pDrawManager->OutlineRect1(x, y, w, h, Line);
	ALX.pDrawManager->DrawLine1(x + 10, y, x + howfaryo, y, bground);
	ALX.pDrawManager->DrawString1(true, x + 20, y - 5, colWhite, Text);
}

void CMenu::TabDraw(int x, int y, int w, int h)
{
	
}

void CMenu::DrawRhombusFill(int x, int y, int w, int h, Color dwColor)
{
	int W = w / 2;
	ALX.pSurface->DrawSetColor(dwColor);
	for (int i = 0; i < 20; i++)
	{
		ALX.pSurface->DrawLine(x + W - i, y + i, x + W + w - i, y + i);
	}
}

void CMenu::TabOperator(int x, int y, int w, int h,bool &tab1,bool &tab2, bool &tab3, bool &tab4, bool &tab5, bool &tab6, bool &tab7)
{


	ALX.pDrawManager->FillRGBA(x - 40, y - 140, 10, 35, ClrLGrey);
	ALX.pDrawManager->FillRGBA(x - 40, y - 100, 10, 35, ClrLGrey);
	ALX.pDrawManager->FillRGBA(x - 40, y - 60, 10, 35, ClrLGrey);
	ALX.pDrawManager->FillRGBA(x - 40, y - 20, 10, 35, ClrLGrey);
	ALX.pDrawManager->FillRGBA(x - 40, y + 20, 10, 35, ClrLGrey);
	ALX.pDrawManager->FillRGBA(x - 40, y + 60, 10, 35, ClrLGrey);
	ALX.pDrawManager->FillRGBA(x - 40, y + 100, 10, 35, ClrLGrey);

	if (!tab1 && !tab2 && !tab3 && !tab4 && !tab5 && !tab6 && !tab7)
	{
		tab1 = true;
	}

	if (Mousein(x - 200,y - 140, 175, 40))
	{
		ALX.pDrawManager->FillRGBA(x - 200, y - 140, 175, 35, Color(120, 120, 120, 40));
		if (GetAsyncKeyState(0x1) & 1)
		{
			tab1 = !tab1;
			tab2 = false;
			tab3 = false;
			tab7 = false;
			tab4 = false;
			tab5 = false;
			tab6 = false;
		
		}
	}

	if (tab1)
	{
		ALX.pDrawManager->FillRGBA(x - 40, y - 140, 10, 35, colBlack);
	}

	if (Mousein(x - 200, y - 100, 175, 40))
	{
		ALX.pDrawManager->FillRGBA(x - 200, y - 100, 175, 35, Color(120, 120, 120, 40));
		if (GetAsyncKeyState(0x1) & 1)
		{
			tab1 = false;
			tab2 = !tab2;
			tab3 = false;
			tab7 = false;
			tab4 = false;
			tab5 = false;
			tab6 = false;

		}
	}

	if (tab2)
	{
		ALX.pDrawManager->FillRGBA(x - 40, y - 100, 10, 35, colBlack);
	}

	if (Mousein(x - 200, y - 60, 175, 40))
	{
		ALX.pDrawManager->FillRGBA(x - 200, y - 60, 175, 35, Color(120, 120, 120, 40));
		if (GetAsyncKeyState(0x1) & 1)
		{
			tab1 = false;
			tab2 = false;
			tab3 = !tab3;
			tab7 = false;
			tab4 = false;
			tab5 = false;
			tab6 = false;

		}
	}

	if (tab3)
	{
		ALX.pDrawManager->FillRGBA(x - 40, y - 60, 10, 35, colBlack);
	}

	if (Mousein(x - 200, y - 20, 175, 40))
	{
		ALX.pDrawManager->FillRGBA(x - 200, y - 20, 175, 35, Color(120, 120, 120, 40));
		if (GetAsyncKeyState(0x1) & 1)
		{
			tab1 = false;
			tab2 = false;
			tab3 = false;
			tab4 = !tab4;
			tab5 = false;
			tab7 = false;
			tab6 = false;

		}
	}

	if (tab4)
	{
		ALX.pDrawManager->FillRGBA(x - 40, y - 20, 10, 35, colBlack);
	}

	if (Mousein(x - 200, y + 20, 175, 40))
	{
		ALX.pDrawManager->FillRGBA(x - 200, y + 20, 175, 35, Color(120, 120, 120, 40));
		if (GetAsyncKeyState(0x1) & 1)
		{
			tab1 = false;
			tab2 = false;
			tab3 = false;
			tab4 = false;
			tab5 = !tab5;
			tab7 = false;
			tab6 = false;

		}
	}

	if (tab5)
	{
		ALX.pDrawManager->FillRGBA(x - 40, y + 20, 10, 35, colBlack);
	}

	if (Mousein(x - 200, y + 60, 175, 40))
	{
		ALX.pDrawManager->FillRGBA(x - 200, y + 60, 175, 35, Color(120, 120, 120, 40));
		if (GetAsyncKeyState(0x1) & 1)
		{
			tab1 = false;
			tab2 = false;
			tab3 = false;
			tab4 = false;
			tab5 = false;
			tab7 = false;
			tab6 = !tab6;
			

		}
	}

	if (tab6)
	{
		ALX.pDrawManager->FillRGBA(x - 40, y + 60, 10, 35, colBlack);
	}
	

	if (Mousein(x - 200, y + 100, 175, 40))
	{
		ALX.pDrawManager->FillRGBA(x - 200, y + 100, 175, 35, Color(120, 120, 120, 40));
		if (GetAsyncKeyState(0x1) & 1)
		{
			tab1 = false;
			tab2 = false;
			tab3 = false;
			tab4 = false;
			tab5 = false;
			tab6 = false;
			tab7 = !tab7;

		}
	}

	if (tab7)
	{
		ALX.pDrawManager->FillRGBA(x - 40, y + 100, 10, 35, colBlack);
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
	//ALX.pDrawManager->FillRGBA(Cur.x, Cur.y, 10, 10, colBlack);

	for (int i = 0; i <= 9; i++)
	{
		ALX.pDrawManager->DrawLine1(Cur.x, Cur.y, Cur.x + i, Cur.y + 11, colWhite);
	}
	for (int i = 0; i <= 7; i++)
	{
		ALX.pDrawManager->DrawLine1(Cur.x, Cur.y + 9 + i, Cur.x + i, Cur.y + 9, colWhite);
	}
	for (int i = 0; i <= 3; i++)
	{
		ALX.pDrawManager->DrawLine1(Cur.x + 6 + i, Cur.y + 11, Cur.x, Cur.y + i, colWhite);
	}
	ALX.pDrawManager->DrawLine1(Cur.x + 5, Cur.y + 11, Cur.x + 8, Cur.y + 18, colWhite);
	ALX.pDrawManager->DrawLine1(Cur.x + 4, Cur.y + 11, Cur.x + 7, Cur.y + 18, colWhite);

	ALX.pDrawManager->DrawLine1(Cur.x, Cur.y, Cur.x, Cur.y + 17, colBlack);
	ALX.pDrawManager->DrawLine1(Cur.x, Cur.y + 17, Cur.x + 3, Cur.y + 14, colBlack);

	ALX.pDrawManager->DrawLine1(Cur.x + 4, Cur.y + 14, Cur.x + 7, Cur.y + 19, colBlack);
	ALX.pDrawManager->DrawLine1(Cur.x + 5, Cur.y + 14, Cur.x + 7, Cur.y + 19, colBlack);

	ALX.pDrawManager->DrawLine1(Cur.x + 7, Cur.y + 18, Cur.x + 9, Cur.y + 18, colBlack);

	ALX.pDrawManager->DrawLine1(Cur.x + 10, Cur.y + 18, Cur.x + 7, Cur.y + 12, colBlack);

	ALX.pDrawManager->DrawLine1(Cur.x + 7, Cur.y + 12, Cur.x + 12, Cur.y + 12, colBlack);

	ALX.pDrawManager->DrawLine1(Cur.x + 12, Cur.y + 12, Cur.x, Cur.y, colBlack);
}
//where is the code where you move menu
void CMenu::DrawCheckBox(int x, int y, const char* fmt, float &option)
{
	POINT Cur;
	GetCursorPos(&Cur);

	

	ALX.pDrawManager->DrawString1(true, x + 20, y, colWhite, fmt);

	ALX.pDrawManager->FillRGBA(x, y, 15, 15,colCrimson);
	//ALX.pDrawManager->FillRGBA(x - 6, y - 131, 7.5, 7.5, Magneta);

	if (Mousein(x, y, 15, 15))
	{
		ALX.pDrawManager->FillRGBA(x, y, 15, 15, Color(120, 120, 120, 40));
	
	}

	

	if (Mousein(x, y,15,15))
	{
		if (GetAsyncKeyState(0x01) & 1)
		{
			option = !option;
		}	
	}

	if (option){
		ALX.pDrawManager->FillRGBA(x + 4,y + 4, 7.5, 7.5, colBlack);
	}


}


void CMenu::KeyPicker(int x, int y, int w, int h, const char* option, bool &Click, bool &Clicker, bool &Clicky)
{
	int AimKey = 0x0;

	char aimKey[32];

	sprintf(aimKey, "%d", AimKey);

	ALX.pDrawManager->FillRGBA(x, y, w, h,ClrLGrey);
	DrawLinedBox(x, y, w, h, 3, colBlack);
	ALX.pDrawManager->DrawString1(true, x + 20, y + h / 2 - 5, colWhite, "No Key");
	ALX.pDrawManager->DrawString1(true, x + 108, y, colWhite, option);



	if (Mousein(x, y, w, h))
	{
		ALX.pDrawManager->FillRGBA(x, y, w, h, Color(200, 200, 200, 190));
	}

	if (MouseClick(x, y, w, h))
	{
		Click = !Click;
	}

	if (Click)
	{
		ALX.pDrawManager->FillRGBA(x, y, w, h, ClrLGrey);
		DrawLinedBox(x, y, w, h, 3, colBlack);
		ALX.pDrawManager->DrawString1(true, x + 20, y + h / 2 - 5, colWhite, "Press a Key..");
		ALX.pDrawManager->DrawString1(true, x + 108, y, colWhite, option);
		Clicky = !Clicky;

	}

	if (Clicky)
	{

		for (int i = 0x0; i < 0x87; i += 0x1)
		{
			if (GetAsyncKeyState(i))
			{
				AimKey = i;
				Click = !Click;
				Clicker = !Clicker;
				Clicky = !Clicky;
			}
		}
	}

	if (Clicker)
	{
		ALX.pDrawManager->FillRGBA(x, y, w, h, ClrLGrey);
		DrawLinedBox(x, y, w, h, 3, colBlack);
		ALX.pDrawManager->DrawString1(true, x + 20, y + h / 2 - 5, colWhite, aimKey);
		printf(aimKey);
		ALX.pDrawManager->DrawString1(true, x + 108, y, colWhite, option);
	}
}

void CMenu::DrawCheckBoxF(int x, int y, Color colour, const char* fmt, float &option, Color back, const char* desc)
{
	POINT Cur;
	GetCursorPos(&Cur);



	ALX.pDrawManager->DrawString1(true, x, y, colWhite, fmt);
	ALX.pDrawManager->FillRGBA(x + 130, y, 15, 15, colour);
	ALX.pDrawManager->OutlineRect1(x + 130, y, 15, 15, colBlack);

	if (Mousein(x + 130, y, 15, 15))
	{
		ALX.pDrawManager->FillRGBA(x + 130, y, 15, 15, Color(120, 120, 120, 40));

	}

	if (Mousein(x + 130, y, 15, 15))
	{
		if (ALX.pOptions->Tooltip)
		{
			ALX.pDrawManager->DrawString1(true, ALX.pOptions->Menu_X + 20, ALX.pOptions->Menu_Y + 15, menuGreen, desc);
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
		ALX.pDrawManager->FillRGBA(x + 130, y, 15, 15, colWhite);
		ALX.pDrawManager->OutlineRect1(x + 130, y, 15, 15, colBlack);
	}


}

void CMenu::DrawListBoxThing(int x, int y, int w, int h, int letters, Color background, Color text, const char* fmt)
{
	ALX.pDrawManager->FillRGBA(x, y, w, h, background);
	ALX.pDrawManager->OutlineRect1(x, y, w, h, colMenu);
	ALX.pDrawManager->DrawLine1(x + 8, y, x + 10 + letters * 10, y, colWhite2);
	ALX.pDrawManager->DrawString1(false, x + 17, y - 12, text, fmt);
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
	ALX.pDrawManager->FillRGBA(x, y, w, sliderh, colGrey);
	ALX.pDrawManager->FillRGBA(x, y, w, sliderh, colWhite2);
	ALX.pDrawManager->OutlineRect1(x, y, w, sliderh, colBlack);
	ALX.pDrawManager->FillRGBA(sliderx2, y, sliderw, sliderh, colBlack);
	ALX.pDrawManager->FillRGBA(x, y, sliderx2 - x, sliderh, colMenu);
	SmoothValue = ((max - min) / (w))*(sliderx2 - x + sliderw / 2);
	sprintf_s(SliderValue2, " %1.0f", SmoothValue);

	ALX.pDrawManager->DrawString1(false, x + 5, y, colBlack, SliderValue2);

}

void CMenu::DrawSlider(float x, float y, float w, int min, int max, float &SmoothValue,int &sliderx,const char* option)
{

	float sliderw = 10.f;
	float sliderh = 8.0f;

	INT Width, Height;
	ALX.pEngine->GetScreenSize(Width, Height);

	int W = Width / 2;
	int H = Height / 2;

	POINT cursor;
	GetCursorPos(&cursor);

	float clickx = sliderx - cursor.x;
	float moveto = sliderx - clickx - sliderw / 2;
	if (cursor.x >= x - sliderw / 2 && cursor.y >= y - 2 && cursor.x <= x + w + sliderw / 2 && cursor.y <= y + sliderh + 2)//this checking if ure n slider?yes
	{
		if (GetAsyncKeyState(0x1))
		{
			sliderx = moveto;
			ALX.pDrawManager->DrawOutlinedCircle(W, H, SmoothValue, colBlack);
		}
	}
	if (sliderx < x - sliderw / 2){ sliderx = x - sliderw / 2; }
	if (sliderx > x + w - sliderw / 2){ sliderx = x + w - sliderw / 2; }
	ALX.pDrawManager->FillRGBA(x, y, w, sliderh, ClrDGrey);
	ALX.pDrawManager->FillRGBA(x, y, w, sliderh, ClrDGrey);
	ALX.pDrawManager->FillRGBA(x, y, sliderx - x, sliderh, colBlack);
	//ALX.pDrawManager->OutlineRect1(x, y, w, sliderh, colWhite);
	ALX.pDrawManager->FillRGBA(sliderx, y - 3.5, sliderw, 15, colBlack);
	//ALX.pDrawManager->OutlineRect1(sliderx, y - 3.5, sliderw, 15, colWhite);
	SmoothValue = ((max - min) / (w))*(sliderx - x + sliderw / 2);
	sprintf_s(SliderValue, " %1.0f", SmoothValue);

	ALX.pDrawManager->DrawString1(true, x + 5, y - 30, colWhite, option);
	ALX.pDrawManager->DrawString1(true, x + 130, y - 30, colWhite, SliderValue);

}



void CMenu::DrawCombobox(int x, int y, int w, int h, Color Outline, Color back, Color String, const char* title, const char* item1, const char* item2, float &option1, float &option2, bool &Click,bool &Clicker,const char* desc)
{
	POINT Cur;
	GetCursorPos(&Cur);

	DrawLinedBox(x, y, w, h, 3, colBlack);
	ALX.pDrawManager->DrawString1(true, x + 10, y + 2, String, title);

	if (Mousein(x, y, w, h))
	{
		ALX.pDrawManager->FillRGBA(x, y, w, h, Color(220, 220, 220, 80));
		if (ALX.pOptions->Tooltip)
		{
			ALX.pDrawManager->DrawString1(true, ALX.pOptions->Menu_X + 30, ALX.pOptions->Menu_Y + 55 + 70, colWhite, desc);
		}
	}

	if (Cur.x > x && Cur.x < x + w && Cur.y > y && Cur.y < y + h)
	{
		if (GetAsyncKeyState(0x01) & 1)
		{
			Click = !Click;
		}
	}

	if (Click)
	{
		ALX.pDrawManager->FillRGBA(x, y + h * 1, w, h, ClrLGrey);
		DrawLinedBox(x, y + h * 1, w, h,3, colBlack);

		ALX.pDrawManager->DrawString1(true, x + 10, y + h * 1, String, item1);

		ALX.pDrawManager->FillRGBA(x, y + h * 2, w, h, ClrLGrey);
		DrawLinedBox(x, y + h * 2, w, h, 3, colBlack);
	
		ALX.pDrawManager->DrawString1(true, x + 10 , y + h * 2, String, item2);

		if (Mousein(x, y + h * 1, w, h))
		{
			ALX.pDrawManager->FillRGBA(x, y + h * 1, w, h, Color(220, 220, 220, 80));

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
			ALX.pDrawManager->FillRGBA(x, y + h * 2, w, h, Color(220, 220, 220, 80));

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
			ALX.pDrawManager->FillRGBA(x, y, w, h, ClrLGrey);
			DrawLinedBox(x, y, w, h,3, colBlack);
			
			ALX.pDrawManager->DrawString1(true, x + 10, y, String, item1);
		}
		else if (option2 == true)
		{
			ALX.pDrawManager->FillRGBA(x, y, w, h, ClrLGrey);
			DrawLinedBox(x, y, w, h,3, colBlack);

			ALX.pDrawManager->DrawString1(true, x + 10, y, String, item2);
		}
	}
}

bool Window[8][2];
POINT Click;

bool CMenu::MoveMenu(int &X, int &Y, int W, int H, int index)
{
	for (int i = 0; i < 8; i++)
	if (Window[i][0] && i != index)
		return false;

	POINT Cur;
	GetCursorPos(&Cur);

	if (GetAsyncKeyState(VK_LBUTTON) < 0)
	{
		if (Cur.x > X && Cur.x < X + W && Cur.y >(Y - 20 - 3) && Cur.y < (Y - 20 - 3) + H || Window[index][0])
		{
			Window[index][0] = true;

			if (!Window[index][1])
			{
				Click.x = Cur.x - X;
				Click.y = Cur.y - Y;
				Window[index][1] = true;

			}
		}
		else
		{
			Window[index][0] = false;
			Window[index][1] = false;
		}
	}

	if (GetAsyncKeyState(VK_LBUTTON) == 0 && Window[index][0])
	{
		Window[index][0] = false;
		Window[index][1] = false;
	}

	if (Window[index][0])
	{
		X = Cur.x - Click.x;
		Y = Cur.y - Click.y;
	}

	return true;
}
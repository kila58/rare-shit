#pragma once
#include "client.h"
#include <math.h>

typedef unsigned long ulong;

POINT mousepos;
/* rand example: guess the number */
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


float Lerp(float flFraction, float flStart, float flEnd)
{
	return (1 - flFraction) * flStart + flFraction * flEnd;
}

float Clamp(float x, float a, float b)
{
	/*int iReturn = 0;
	iReturn = x;

	if (iReturn < a)
	iReturn = a;
	if (iReturn > b)
	iReturn = b;

	return iReturn;// x < a ? a : (x > b ? b : x);*/
	return x < a ? a : (x > b ? b : x);
}

namespace variables
{
	namespace Aimbot
	{
		bool Active = true;
		bool TargetTeammates = true;

		// Basic Settings
		bool IgnoreSpawnProtection = true;
		bool IgnoreSteamFriends = true;
		bool IgnoreNPCs = true;
		bool Silent = false;
		bool pSilent = false;
		bool BoneScan = true;

		// Legit Aimbot
		bool Legit = false;
		float LegitSpeed = 4;
		float LegitFOV = 10;
	};

	namespace Visuals
	{
		bool Active = true;
		bool ShowTeammates = true;
		bool ShowSteamFriends = true;
		bool ShowNPCs = false;
		bool ShowWeapons = false;
		bool ShowSENTs = false;

		// Basic Settings
		bool Name = true;
		bool Health = true;
		bool Weapon = true;
		bool Distance = false;

		bool Box = true;
		bool FilledBox = false;

		bool Lines = false;

		bool Crosshair = true; // float Crosshair = 7;

		// Settings
		bool Skeleton = false;
		bool HealthBar = true;
		bool AABB_Box = true;

		// Useless
		bool Watermark = true;
	};

	namespace Radar
	{
		bool Active = false;
		float Size = 200;

		float XPos = 50;
		float YPos = 200;
	};

	namespace Removals
	{
		bool Seed = true;
		bool sed = true;
	};

	namespace Misc
	{
		float pSpeed = 6;
		bool pSpeedRunCommand = true;
		bool RapidFire = true;
		bool AltRapidFire = false;
		bool RapidUse = false;
		bool BunnyHop = true;
		bool Spinbot = true;
		float SpinSpeed = 6;
		bool Fakelag = false;
		bool FakeCrouch = false;
		float AntiAim = 1;
		float AAX = 90;
		float AAY = 180;
		float FAX = 180;
		float FAY = 90;
		// ^ Kelse's angles ^
		/*float AAX = 179;
		float AAY = 181;
		float FAX = 179;
		float FAY = 179;*/
		bool FlashlightSpam = true;
		bool Spam = false;
		bool RPSpam = false;
		bool KillSpam = false;
		bool KillSounds = false;
		bool Namesteal = false;
		bool RPNamesteal = false;
		bool AntiAntiAim = true;
		/*
		19:29 - LYVKV 2K: use 90/180 swap
		*/
	};

	namespace Colors
	{
		namespace Menu
		{
			float Red = 94;		// 255
			float Green = 187;	// 111
			float Blue = 201;	// 111
			float Alpha = 255;
		};

		namespace Teammate
		{
			float Red = 0;
			float Green = 135;
			float Blue = 255;
			float Alpha = 255;
		};

		namespace Enemy
		{
			float Red = 255;
			float Green = 155;
			float Blue = 55;
			float Alpha = 255;
		};

		namespace SteamFriend // VisibleEnemy
		{
			float Red = 155;
			float Green = 255;
			float Blue = 0;
			float Alpha = 255;
		};
	};

	namespace Gamemodes
	{
		bool IgnoreJBSpectators = false;
	};

	namespace Lua
	{
		bool BlockLuaCmd = false;
		bool BlockRunString = false;
		float LoadCmdSource = 1;
	};

	namespace Menu
	{
		char* Tab = "Credits";
		float XPos = 10;
		float YPos = 10;
	};
};

namespace draw {
	int __stdcall GetTextLenght(char *string, ulong hFont)
	{
		int sizeW, sizeH;

		wchar_t szString[1024] = { '\0' };
		wsprintfW(szString, L"%S", string);

		cl.surface->GetTextSize(hFont, szString, sizeW, sizeH);
		return sizeW;
	}

	int __stdcall GetTextHeight(char *string, ulong hFont)
	{
		int sizeW, sizeH;

		wchar_t szString[1024] = { '\0' };
		wsprintfW(szString, L"%S", string);

		cl.surface->GetTextSize(hFont, szString, sizeW, sizeH);
		return sizeH;
		// (20 / 1.5f) * multiplier; /*12 * multiplier;*/
	}

	void __stdcall String(bool bCenter, float x, float y, ulong font, Color cColor, char* text, ...) {
		char szBuffer[256] = { 0 };

		va_list va;

		va_start(va, text);
		_vsnprintf(szBuffer, sizeof(szBuffer), text, va);
		va_end(va);

		if (bCenter)
			x -= GetTextLenght(szBuffer, font) / 2;

		char szString[1024] = { '\0' };
		sprintf(szString, "%s", szBuffer);
		cl.surface->SetTextPos(x, y);
		cl.surface->SetFont(font);
		cl.surface->SetTextColor(cColor);
		cl.surface->DrawTextA(szString);
	}

	void __stdcall Line(float startX, float startY, float endX, float endY, Color cColor) {
		cl.surface->SetDrawColor(cColor);
		cl.surface->DrawLine(startX, startY, endX, endY);
	}

	void __stdcall Rectangle(float x, float y, float w, float h, Color cColor) {
		cl.surface->SetDrawColor(cColor);
		cl.surface->DrawOutlined(x, y, w, h);
	}

	void __stdcall FilledRectangle(float x, float y, float w, float h, Color cColor) {
		cl.surface->SetDrawColor(cColor);
		cl.surface->DrawRect(x, y, w, h);
	}
};

namespace GUI {
	float flWidth = 0;
	float flHeight = 0;
	Color colMenu = Color(50, 150, 255, 255);

	void __stdcall Reset()
	{
		flWidth = 0;
		flHeight = 0;
	}
	void __stdcall Separator()
	{
		flHeight += 20;
	}
	void __stdcall Column(float flSpacer)
	{
		flHeight = 0;
		flWidth += flSpacer;
	}
	bool __stdcall isMouseHovering(float x, float y, float w, float h)
	{
		if (mousepos.x >= x && mousepos.x <= x + w && mousepos.y >= y && mousepos.y <= y + h)
			return true;

		return false;
	}
	bool __stdcall isMousePressing(float x, float y, float w, float h)
	{
		if (mousepos.x >= x && mousepos.x <= x + w && mousepos.y >= y && mousepos.y <= y + h && GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			return true;

		return false;
	}


	float __stdcall Button(void(*f)(), char* strText, float posX, float posY, bool bBool)
	{
		if (bBool) {
			posX += flWidth;
			posY += flHeight;
		}

		float flButtonWidth = 10;
		float flButtonHeight = 15 + 4;

		flButtonWidth += draw::GetTextLenght(strText, 5);

		Color ButtonColor = colMenu;
		ButtonColor.a = 150;
		if (isMousePressing(posX, posY, flButtonWidth, flButtonHeight)) {
			ButtonColor = Color(ButtonColor.r, ButtonColor.g, ButtonColor.b, 255);
			f();
		}
		else if (isMouseHovering(posX, posY, flButtonWidth, flButtonHeight))
			ButtonColor = Color(ButtonColor.r, ButtonColor.g, ButtonColor.b, 200);

		if (!bBool)
			draw::FilledRectangle(posX, posY, flButtonWidth, flButtonHeight, Color(5, 5, 5, 150));


		draw::FilledRectangle(posX, posY, flButtonWidth, flButtonHeight, ButtonColor);
		draw::Rectangle(posX, posY, flButtonWidth, flButtonHeight, Color(5, 5, 5, 150));
		draw::String(true, posX + flButtonWidth / 2, posY + 2.5f, 5, Color(240, 240, 240, 255), strText);

		if (bBool)
			flHeight += flButtonHeight + 5;

		return flButtonWidth;
	}
	void __stdcall Text(bool bCenter, float posX, float posY, ulong dwFont, Color colColor, char* strText, ...)
	{
		posX += flWidth;
		posY += flHeight;

		char szBuffer[256] = { 0 };

		va_list va;

		va_start(va, strText);
		_vsnprintf(szBuffer, sizeof(szBuffer), strText, va);
		va_end(va);

		draw::String(bCenter, posX, posY, dwFont, colColor, szBuffer);

		flHeight += draw::GetTextHeight(szBuffer, dwFont) + 2;
	}

	void __stdcall Slider(float& flVariable, char* strText, float posX, float posY, float min, float max, float width = 200)
	{
		posX += flWidth;
		posY += flHeight + 15;

		max -= min;
		int flBarLenght = ((flVariable - min) * width) / max;
		int flStaticBarLenght = (max * width) / max;

		if (isMousePressing(posX, posY, flStaticBarLenght, 20))
			flVariable = (mousepos.x - posX) * (max / width) + min;

		char strSliderText[500];
		sprintf_s(strSliderText, "%s %i", strText, (int)flVariable);

		Color colSlider = colMenu;
		colSlider.a = 150;
		draw::FilledRectangle(posX, posY, flStaticBarLenght, 15, Color(100, 100, 100, 200));
		draw::FilledRectangle(posX, posY + 1, flBarLenght, 13, colSlider);
		draw::Line(posX + flBarLenght, posY, posX + flBarLenght, posY + 14, colSlider);
		draw::String(true, posX + flStaticBarLenght / 2, posY - 15, 5, Color(240, 240, 240, 255), strSliderText);

		flHeight += 35;
	}

	void __stdcall Checkbox(bool& bVariable, char* strText, float posX, float posY)
	{
		posX += flWidth;
		posY += flHeight;

		Color CheckboxColor = Color(variables::Colors::Menu::Red, variables::Colors::Menu::Green, variables::Colors::Menu::Blue, 0);

		if (isMousePressing(posX, posY, 15 + 2 + draw::GetTextLenght(strText, 5), 15)) {
			CheckboxColor.a = 50;
			bVariable = !bVariable;
			Sleep(100);
		}
		else if (isMouseHovering(posX, posY, 15 + 2 + draw::GetTextLenght(strText, 5), 15))
			CheckboxColor.a = 20;

		draw::FilledRectangle(posX, posY, 15, 15, CheckboxColor);
		if (bVariable) {
			/*draw::Line(posX, posY, posX + 14, posY + 14, colMenu);
			draw::Line(posX, posY + 14, posX + 14, posY, colMenu);*/
			draw::FilledRectangle(posX + 5, posY + 5, 5, 5, colMenu);
		}
		draw::Rectangle(posX, posY, 15, 15, Color(5, 5, 5, 150));

		draw::String(false, posX + 15 + 2, posY, 5, Color(240, 240, 240, 255), strText);

		flHeight += 20;
	}

	void __stdcall Tab(char* strTab, float& tabX, float& tabY, float& flTabProgress)
	{
		/*tabX += 0;
		tabY += 0;*/

		if (isMousePressing(tabX, tabY, 175 - 10, 30))
			variables::Menu::Tab = strTab;

		Color colProgressColor = colMenu;
		if (isMouseHovering(tabX, tabY, 175 - 10, 30) || (variables::Menu::Tab == strTab))
			flTabProgress = Lerp(/*g_pGlobals->frametime * 5*/0.05, flTabProgress, 150 + 1);
		else
			flTabProgress = Lerp(/*g_pGlobals->frametime * 5*/0.05, flTabProgress, 0);

		flTabProgress = Clamp(flTabProgress, 0, 150);

		colProgressColor.a = ((flTabProgress * 255) / 150);

		Color colTextColor = Color(240, 240, 240, 255);
		if ((variables::Menu::Tab == strTab)) {
			colTextColor.r = colMenu.r;
			colTextColor.g = colMenu.g;
			colTextColor.a = colMenu.a;
		}

		draw::FilledRectangle(tabX - 2, tabY - 2, 175 - 10, 30 + 4, Color(20, 20, 20, 100));
		draw::FilledRectangle(tabX, tabY, 7, 30, colMenu);
		draw::FilledRectangle(tabX + 7 + 5, tabY, flTabProgress, 30, colProgressColor);
		draw::String(false, tabX + 7 + 10, tabY + 8, 5, colTextColor, strTab);

		tabY += 30 + 5 + 2;
	}

	void __stdcall shitMenu()
	{
		// variables::Menu::XPos
		// variables::Menu::YPos
		static float sizeW = 640;
		static float sizeH = 400;

		if (isMousePressing(variables::Menu::XPos + 175, variables::Menu::YPos, sizeW - 175, 21))
		{
			int wantedX = mousepos.x - sizeW / 2;
			int wantedY = mousepos.y - 21 / 2;

			variables::Menu::XPos = wantedX;
			variables::Menu::YPos = wantedY;
		}

		variables::Menu::XPos = Clamp(variables::Menu::XPos, 0, cl.sw - sizeW);
		variables::Menu::YPos = Clamp(variables::Menu::YPos, 0, cl.sh - sizeH);

		colMenu = Color(variables::Colors::Menu::Red, variables::Colors::Menu::Green, variables::Colors::Menu::Blue, variables::Colors::Menu::Alpha);

		draw::FilledRectangle(variables::Menu::XPos, variables::Menu::YPos, sizeW, sizeH, Color(5, 5, 5, 150));
		draw::Rectangle(variables::Menu::XPos, variables::Menu::YPos, sizeW, sizeH, colMenu);
		draw::FilledRectangle(variables::Menu::XPos, variables::Menu::YPos, sizeW, 21, colMenu);

		Color colTextColor = Color(240, 240, 240, 255);
		if (isMouseHovering(variables::Menu::XPos + 175, variables::Menu::YPos, sizeW - 175, 21))
			colTextColor = Color(rand() % 255, rand() % 255, rand() % 255, 255);
		draw::String(true, variables::Menu::XPos + sizeW / 2, variables::Menu::YPos + 3, 5, colTextColor, "de$u");

		// Tabs Background
		draw::FilledRectangle(variables::Menu::XPos, variables::Menu::YPos + 21, 175, sizeH - 21 - 1, Color(5, 5, 5, 50));
		draw::Line(variables::Menu::XPos + 175 - 1, variables::Menu::YPos + 21, variables::Menu::XPos + 175 - 1, variables::Menu::YPos + sizeH - 1, Color(5, 5, 5, 50));

		Reset();

		float posX = variables::Menu::XPos + 175 + 5;
		float posY = variables::Menu::YPos + 21 + 5;
		float posW = sizeW - 175 - 10;
		/*float flButtonSize1 = Button(cConfigs::SaveConfig, "Save", variables::Menu::XPos + 1, variables::Menu::YPos + 1, false);
		Button(cConfigs::ReadConfig, "Load", variables::Menu::XPos + 1 + flButtonSize1 + 5, variables::Menu::YPos + 1, false);
		*/

		float posH = sizeH - 21 - 10;
		if (variables::Menu::Tab == "Aimbot")
		{
			Checkbox(variables::Aimbot::Active, "Active [ F ]", posX, posY);

			Column(posW / 2);

		}
		else if (variables::Menu::Tab == "Visuals")
		{
			/*cESP::DrawPlayer(false, "Teammate", "Unarmed", 75, 100, 15, posX + 10, posY + 25, 35, 65, true, false, Color(variables::Colors::Teammate::Red, variables::Colors::Teammate::Green, variables::Colors::Teammate::Blue, variables::Colors::Teammate::Alpha));
			cESP::DrawPlayer(true, "Enemy", "Unarmed", 25, 100, 15, posX + 10, posY + 25 + 65 + 45 + 10 + 10, 35, 65, true, false, Color(variables::Colors::Enemy::Red, variables::Colors::Enemy::Green, variables::Colors::Enemy::Blue, variables::Colors::Enemy::Alpha));
			cESP::DrawPlayer(false, "Squadmate", "Unarmed", 69, 100, 15, posX + 10 + 35 + 55, posY + 25, 35, 65, true, true, Color(variables::Colors::Squadmate::Red, variables::Colors::Squadmate::Green, variables::Colors::Squadmate::Blue, variables::Colors::Squadmate::Alpha));
			Column(BmenuW / 3);*/


			Separator();



			Column(posW / 2);

		}
		else if (variables::Menu::Tab == "Radar")
		{
			Checkbox(variables::Radar::Active, "Active (to add)", posX, posY);
			Slider(variables::Radar::Size, "Size", posX, posY, 100, 400);
		}
		else if (variables::Menu::Tab == "Removals")
		{
			Checkbox(variables::Removals::Seed, "Compensate Spread", posX, posY);
		}
		else if (variables::Menu::Tab == "Misc")
		{
			Slider(variables::Misc::pSpeed, "pSpeed [B]", posX, posY, 0, 15);
			Checkbox(variables::Misc::BunnyHop, "IN_JUMP Bunny Hop", posX, posY);
			Separator();

			Column(posW / 2);
		}
		else if (variables::Menu::Tab == "Colors")
		{
			Slider(variables::Colors::Menu::Red, "Menu Red", posX, posY, 0, 255);
			Slider(variables::Colors::Menu::Green, "Menu Green", posX, posY, 0, 255);
			Slider(variables::Colors::Menu::Blue, "Menu Blue", posX, posY, 0, 255);

			Separator();

			Slider(variables::Colors::Teammate::Red, "Teammate Red", posX, posY, 0, 255);
			Slider(variables::Colors::Teammate::Green, "Teammate Green", posX, posY, 0, 255);
			Slider(variables::Colors::Teammate::Blue, "Teammate Blue", posX, posY, 0, 255);

			Column(posW / 2);

			Slider(variables::Colors::Enemy::Red, "Enemy Red", posX, posY, 0, 255);
			Slider(variables::Colors::Enemy::Green, "Enemy Green", posX, posY, 0, 255);
			Slider(variables::Colors::Enemy::Blue, "Enemy Blue", posX, posY, 0, 255);

			Separator();

			Slider(variables::Colors::SteamFriend::Red, "Squadmate Red", posX, posY, 0, 255);
			Slider(variables::Colors::SteamFriend::Green, "Squadmate Green", posX, posY, 0, 255);
			Slider(variables::Colors::SteamFriend::Blue, "Squadmate Blue", posX, posY, 0, 255);
		}
		else if (variables::Menu::Tab == "Gamemodes")
		{
			Text(false, posX, posY, 5, Color(240, 240, 240, 255), "Note: Thoses Settings does NOT save.");
			Checkbox(variables::Gamemodes::IgnoreJBSpectators, "[Jailbreak] Ignore Spectators", posX, posY);
		}
		else if (variables::Menu::Tab == "Lua")
		{
			Text(false, posX, posY, 5, Color(240, 240, 240, 255), "Note: Thoses Settings does NOT save.");
			Checkbox(variables::Lua::BlockLuaCmd, "Block LuaCmd", posX, posY);
			Checkbox(variables::Lua::BlockRunString, "Block RunString", posX, posY);
			Separator();
			Slider(variables::Lua::LoadCmdSource, "de$u", posX, posY, 1, 4);
			Text(false, posX, posY, 5, Color(240, 240, 240, 255), "[1] LuaCmd");
			Text(false, posX, posY, 5, Color(240, 240, 240, 255), "[2] RunString");
			Text(false, posX, posY, 5, Color(240, 240, 240, 255), "[3] [C]");
			Text(false, posX, posY, 5, Color(240, 240, 240, 255), "[4] No Source");
		}
		else if (variables::Menu::Tab == "Credits")
		{
			Text(false, posX, posY, 5, Color(240, 240, 240, 255), "de$u.");
			Text(false, posX + 30, posY, 5, Color(240, 240, 240, 255), "Special Thanks to:");
			Text(false, posX + 45, posY, 5, Color(240, 240, 240, 255), "- _Fami");
			Text(false, posX + 45, posY, 5, Color(240, 240, 240, 255), "- NanoCat");
			Text(false, posX + 45, posY, 5, Color(240, 240, 240, 255), "- Styles");
			Text(false, posX + 45, posY, 5, Color(240, 240, 240, 255), "- Leystryku"); // here u go bby <3 sorry

		}


		/*
		Tabs
		*/
		float tabX = variables::Menu::XPos + 1 + 5;
		float tabY = variables::Menu::YPos + 21 + 5;

		static float flAimbot = 0;
		Tab("Aimbot", tabX, tabY, flAimbot);
		static float flVisuals = 0;
		Tab("Visuals", tabX, tabY, flVisuals);
		static float flRemovals = 0;
		Tab("Removals", tabX, tabY, flRemovals);
		static float flMisc = 0;
		Tab("Misc", tabX, tabY, flMisc);
		static float flColors = 0;
		Tab("Colors", tabX, tabY, flColors);
		tabY += 42.5;

		static float flCredits = 0;
		Tab("Credits", tabX, tabY, flCredits);
	}
}
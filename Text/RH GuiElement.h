#pragma once

#include "SDK.h"

class CGUIElement
{
public:
	void LogoUp(int x, int y);
	void DClose(int x, int y);
	void DMinimize(int x, int y);
	void DHide(int x, int y);
	void DResize(int x, int y);
	void BouttonUnPush(int x, int y, int w, int h, Color dwColor, char* title);
	void BouttonPush(int x, int y, int w, int h, Color dwColor, char* title);
	void SelectUnPush(int x, int y, int w, int h, Color dwColor, char* title);
	void SelectPush(int x, int y, int w, int h, Color dwColor, char* title);
	void InputUnPush(int x, int y, int w, int h, Color dwColor);
	void InputPush(int x, int y, int w, int h, Color dwColor);
	void CheckBoxUnPush(int x, int y, Color dwColor, char* title);
	void CheckBoxPush(int x, int y, Color dwColor, char* title);
	void ColorBoxDraw(int x, int y, int w, int h, int r, int g, int b, int t);
	void MemoDraw(int x, int y, int w, int h, Color dwColor);
	void SnakeBox(int x, int y, int w, int h, Color dwColor);
	void BouttonUnPushTaskBar(int x, int y, int w, int h, Color dwColor, char* title);
	void BouttonPushTaskBar(int x, int y, int w, int h, Color dwColor, char* title);
	void ListDrawTaskBar(int x, int y, int w, int h, Color dwColor);
	void WinampBox1Draw(int x, int y, int w, int h);
	void WinampBox2Draw(int x, int y, int w, int h, int r, int g, int b, int a);
	void SliderDraw(int x, int y, int w, int h, int r, int g, int b, int a);
	void DrawWindowBox(int x, int y, int w, int h, bool mode, bool maxilize, bool f1, bool f2, bool f3);
	void ScroolBarUpUnPush(int x, int y, Color dwColor);
	void ScroolBarUpPush(int x, int y, Color dwColor);
	void ScroolBarDownUnPush(int x, int y, Color dwColor);
	void ScroolBarDownPush(int x, int y, Color dwColor);
	void ScroolDownUnPush(int x, int y, int w, int h, Color dwColor);
	void ScroolDownPush(int x, int y, int w, int h, Color dwColor);
};
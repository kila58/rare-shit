#ifndef MOUSE_H
#define MOUSE_H

// Credits: AKN Base for the gay ass menu

#include "sdk.h"
#include <Windows.h>

class cMouse{
public:
	bool active;
	float mousePos[2];
	float oldPos[2];
	void buttons();
	void draw();
	bool check(int, int, int, int);
	bool check(bool, int, int, int, int);
	bool peekMessage(UINT, WPARAM, LPARAM);
	bool mouse1Press;
	bool mouse1Hold;
	bool mouse2Press;
	bool mouse2Hold;
	bool hide;
	void ClickHandler();
	bool Leftclick(int x, int y, int w, int h);
	bool OneLeftclick(int x, int y, int w, int h);
	bool Rightclick(int x, int y, int w, int h);
	bool OneRightclick(int x, int y, int w, int h);
	bool IsOver(int x, int y, int w, int h);
	bool IsMouseOnTop(int x, int y, int w, int h);
};

extern cMouse gMouse;

#endif
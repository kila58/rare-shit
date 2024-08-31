#include "sdk.h"
#include "cCvar.h"

class cMenu
{
public:
	int addItem(int n, char title[1000], float* value, float min, float max, float step);
	void InitMenu();
	void DrawMenu();
	bool menuEvent();
};

extern cMenu gMenu;
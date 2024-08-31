static struct keys
{
	bool        pressed;
	DWORD       starttime;
}
pressingkey[256];

class kui_input
{
public:
	int mouse_x;
	int mouse_y;

	void UpdateMousePos();
	bool MouseWithin(int x, int y, int w, int h){ return (mouse_x >= x && mouse_x <= x + w && mouse_y >= y && mouse_y <= y + h); }
	bool KeyState(int key, DWORD timeout);

	//Wrappers
	bool Mouse1Pressed(){ return(KeyState(VK_LBUTTON, 1000)); }
	bool Mouse1Held(){ return(KeyState(VK_LBUTTON, 1)); }
	bool Mouse1Drag(){ return((GetKeyState(VK_LBUTTON) == -128 || GetKeyState(VK_LBUTTON) == -127)); }
	bool Mouse2Pressed(){ return(KeyState(VK_RBUTTON, 1000)); }
	bool Mouse2Held(){ return(KeyState(VK_RBUTTON, 1)); }
};

void kui_input::UpdateMousePos()
{
	POINT curpos;
	GetCursorPos(&curpos);
	ScreenToClient((HWND)FindWindow("Valve001", NULL), &curpos);

	mouse_x = curpos.x;
	mouse_y = curpos.y;
}

bool kui_input::KeyState(int key, DWORD timeout)
{
	if ((HWND)FindWindow("Valve001", NULL) != GetFocus())
	{
		pressingkey[key].pressed = FALSE;
		return false;
	}

	if (HIWORD(GetKeyState(key)))
	{
		if (!pressingkey[key].pressed || (pressingkey[key].starttime && (pressingkey[key].starttime + timeout) <= GetTickCount()))
		{
			pressingkey[key].pressed = TRUE;
			if (timeout > NULL)pressingkey[key].starttime = GetTickCount();
			return true;
		}
	}
	else
		pressingkey[key].pressed = FALSE;
	return false;
}

kui_input Input;
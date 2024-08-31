class kui_keytrap : public kui_base
{
private:
	const char* keyname;

	bool listening;

public:
	Color namecolor = Color(255, 255, 255, 255);
	Color backroundcolor = Color(231, 231, 231, 255);
	Color backroundhighlightcolor = Color(221, 236, 250, 255);
	Color outlinecolor = Color(153, 153, 153, 153);
	Color outlinehovercolor = Color(121, 166, 245, 153);

	const char* KeyToChar(int key);

	void Draw();

	int* Variable;

	kui_keytrap();
};

kui_keytrap::kui_keytrap()
{
	keyname = "Unbound";

	listening = false;
}

const char* kui_keytrap::KeyToChar(int key)
{
	switch (key)
	{
	case VK_A:			return "A";
	case VK_B:			return "B";
	case VK_C:			return "C";
	case VK_D:			return "D";
	case VK_E:			return "E";
	case VK_F:			return "F";
	case VK_G:			return "G";
	case VK_H:			return "H";
	case VK_I:			return "I";
	case VK_J:			return "J";
	case VK_K:			return "K";
	case VK_L:			return "L";
	case VK_M:			return "M";
	case VK_N:			return "N";
	case VK_O:			return "O";
	case VK_P:			return "P";
	case VK_Q:			return "Q";
	case VK_R:			return "R";
	case VK_S:			return "S";
	case VK_T:			return "T";
	case VK_U:			return "U";
	case VK_V:			return "V";
	case VK_W:			return "W";
	case VK_X:			return "X";
	case VK_Y:			return "Y";
	case VK_Z:			return "Z";
	case VK_SPACE:		return "Space";
	case VK_RMENU:		return "R Alt";
	case VK_LMENU:		return "L Alt";
	case VK_INSERT:		return "Ins";
	case VK_DELETE:		return "Del";
	case VK_RSHIFT:		return "R Shift";
	case VK_LSHIFT:		return "L Shift";
	case VK_LBUTTON:	return "LMB";
	case VK_RBUTTON:	return "RMB";
	case VK_MBUTTON:	return "Wheel";
	case VK_XBUTTON1:	return "X1";
	case VK_XBUTTON2:	return "X2";
	case VK_RCONTROL:	return "R Ctrl";
	case VK_LCONTROL:	return "L Ctrl";
	}

	return NULL;
}

void kui_keytrap::Draw()
{
	if (!IsVisible())
		return;

	int _x, _y;
	GetPosition(&_x, &_y);

	if (Input.MouseWithin(_x, _y, w, h))
	{
		if (Input.Mouse1Pressed() && !listening)
			listening = true;
	}

	//append/remove input into char
	if (listening)
	{
		keyname = "Press key...";

		for (int i = 1; i < 256; i++)
		{
			if (Input.KeyState(i, 1000))
			{
				const char* keychar = KeyToChar(i);

				if (keychar == NULL)
				{
					*Variable = 0;

					listening = false;

					continue;
				}

				*Variable = i;

				listening = false;
			}
		}
	}
	else
	{
		if (*Variable)
			keyname = KeyToChar(*Variable);
		else
			keyname = "Unbound";
	}

	//normal backround
	n_draw::FillRGBA(_x, _y, w, h, backroundcolor);

	if (Input.MouseWithin(_x, _y, w, h) || listening)
	{
		//highlight backround
		n_draw::FillRGBA(_x, _y, w, h, backroundhighlightcolor);

		//highlight outlines
		n_draw::OutlineRect(_x, _y, w, h, outlinehovercolor);
	}
	else
		//normal outline
		n_draw::OutlineRect(_x, _y, w, h, outlinecolor);

	//current option name
	n_draw::DrawString(menufont, true, true, _x + (w / 2), (_y + (h / 2)) + 1, namecolor, keyname);
}
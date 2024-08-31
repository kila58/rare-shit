//if you wana give this a go good luck

class kui_textbox : public kui_base
{
private:
	bool typing = false;

	bool isbackspace = false;

	std::string defaulttext;

	int textspacer = 5;

public:
	Color namecolor = Color(255, 255, 255, 255);
	Color backroundcolor = Color(231, 231, 231, 255);
	Color backroundhighlightcolor = Color(221, 236, 250, 255);
	Color outlinecolor = Color(153, 153, 153, 153);
	Color outlinehovercolor = Color(121, 166, 245, 153);

	char* KeyToChar(int key);

	void Draw();

	void SetDefaultText(std::string _name){ defaulttext = _name; }

	std::string stringbuffer;

	std::string* Variable;

	kui_textbox();
};

kui_textbox::kui_textbox()
{
	defaulttext = "Text Box";

	typing = false;
}

char* kui_textbox::KeyToChar(int key)
{
	switch (key)
	{
		case VK_A:	return "A";
		case VK_B:	return "B";
		case VK_C:	return "C";
		case VK_D:	return "D";
		case VK_E:	return "E";
		case VK_F:	return "F";
		case VK_G:	return "G";
		case VK_H:	return "H";
		case VK_I:	return "I";
		case VK_J:	return "J";
		case VK_K:	return "K";
		case VK_L:	return "L";
		case VK_M:	return "M";
		case VK_N:	return "N";
		case VK_O:	return "O";
		case VK_P:	return "P";
		case VK_Q:	return "Q";
		case VK_R:	return "R";
		case VK_S:	return "S";
		case VK_T:	return "T";
		case VK_U:	return "U";
		case VK_V:	return "V";
		case VK_W:	return "W";
		case VK_X:	return "X";
		case VK_Y:	return "Y";
		case VK_Z:	return "Z";
		case VK_SPACE:	return " ";
	}

	return NULL;
}

void kui_textbox::Draw()
{
	if (!IsVisible())
		return;

	int _x, _y;
	GetPosition(&_x, &_y);

	//start typing if you click inside
	if (Input.MouseWithin(_x, _y, w, h) && Input.Mouse1Pressed())
		typing = true;

	//stop typing if you click outside
	if (typing && !Input.MouseWithin(_x, _y, w, h) && Input.Mouse1Pressed())
		typing = false;

	//append/remove input into string
	if (typing)
	{
		for (int i = 1; i < 256; i++)
		{
			if (Input.KeyState(i, 1000))
			{
				if (i == VK_BACK)
				{
					if (!stringbuffer.empty())
						stringbuffer.pop_back();
				}
				else if (i != VK_BACK)
				{
					char* keybuffer = KeyToChar(i);

					char keychar;

					if (keybuffer == NULL)
						continue;

					keychar = keybuffer[0];

					int strw, strh;
					n_draw::GetTextLength(menufont, (char*)stringbuffer.c_str(), strw, strh);

					if (strw < (w - (textspacer * 2)))
						stringbuffer.push_back(Input.KeyState(VK_LSHIFT, 1) ? keychar : tolower(keychar));
				}

				//copy our buffer to destination ONLY when key input happens
				*Variable = stringbuffer;
			}
		}
	}

	//normal backround
	n_draw::FillRGBA(_x, _y, w, h, backroundcolor);

	if (typing || Input.MouseWithin(_x, _y, w, h))
	{
		//highlight backround
		n_draw::FillRGBA(_x, _y, w, h, backroundhighlightcolor);

		//highlight outlines
		n_draw::OutlineRect(_x, _y, w, h, outlinehovercolor);
	}
	else
		//normal outline
		n_draw::OutlineRect(_x, _y, w, h, outlinecolor);

	//text handler
	if (stringbuffer.empty() && (!typing))
		n_draw::DrawString(menufont, false, true, _x + textspacer, (_y + (h / 2)) + 1, namecolor, defaulttext.c_str());
	else
		n_draw::DrawString(menufont, false, true, _x + textspacer, (_y + (h / 2)) + 1, namecolor, stringbuffer.c_str());
}
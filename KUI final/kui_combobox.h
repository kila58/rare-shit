class option
{
public:
	std::string name;
	bool* var;
};

class kui_combobox : public kui_base
{
private:
	std::string name;

	bool displaylist = false;

	std::string selectedname;

	int textspacer = 5;

public:
	Color namecolor = Color(255, 255, 255, 255);
	Color backroundcolor = Color(231, 231, 231, 255);
	Color backroundhighlightcolor = Color(221, 236, 250, 255);
	Color outlinecolor = Color(153, 153, 153, 153);
	Color outlinehovercolor = Color(121, 166, 245, 153);

	std::vector<option*> list;

	void AddOption(std::string name, bool* var);

	void Draw();

	void MouseInput();

	void SetDefaultText(std::string _name){ selectedname = _name; }

	kui_combobox();
};

std::vector<kui_combobox*> comboboxes;

kui_combobox::kui_combobox()
{
	name = "Combo Box";

	selectedname = "";

	comboboxes.push_back(this);
}

void kui_combobox::AddOption(std::string name, bool* var)
{
	option* New = new option;
	New->name = name;
	New->var = var;

	list.push_back(New);
}

void kui_combobox::Draw()
{
	if (!IsVisible())
		return;

	int _x, _y;
	GetPosition(&_x, &_y);

	for (int i = 0; i < list.size(); i++)
	{
		if (*list[i]->var)
			selectedname = list[i]->name;
	}

	if (displaylist)
	{
		for (int i = 0; i < list.size(); i++)
		{
			//normal option box backround
			n_draw::FillRGBA(_x, (_y + h) + (h * i), w, h, backroundcolor);

			if (Input.MouseWithin(_x, (_y + h) + (h * i), w, h))
			{
				//highlight option box backround
				n_draw::FillRGBA(_x, (_y + h) + (h * i), w, h, backroundhighlightcolor);

				//highlight outline
				n_draw::OutlineRect(_x, (_y + h) + (h * i), w, h, outlinehovercolor);
			}

			//option name
			n_draw::DrawString(menufont, false, true, _x + textspacer, ((_y + h) + (h * i)) + (h / 2), namecolor, list[i]->name.c_str());
		}
	}

	//close list if you click outside
	if (displaylist && !Input.MouseWithin(_x, _y, w, h) && Input.Mouse1Pressed())
		displaylist = false;

	//normal backround
	n_draw::FillRGBA(_x, _y, w, h, backroundcolor);

	if (Input.MouseWithin(_x, _y, w, h) || displaylist)
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
	n_draw::DrawString(menufont, false, true, _x + textspacer, (_y + (h / 2)) + 1, namecolor, selectedname.c_str());
}

void kui_combobox::MouseInput()
{
	if (!IsVisible())
		return;

	int _x, _y;
	GetPosition(&_x, &_y);

	//list toggle input
	if (Input.MouseWithin(_x, _y, w, h))
	{
		if (Input.Mouse1Pressed())
			displaylist = !displaylist;
	}

	//option input
	if (displaylist)
	{
		for (int i = 0; i < list.size(); i++)
		{
			if (Input.MouseWithin(_x, (_y + h) + (h * i), w, h))
			{	
				if (Input.Mouse1Pressed())
				{
					for (int index = 0; index < list.size(); index++)
						*list[index]->var = false;

					*list[i]->var = true;

					displaylist = false;
				}
			}
		}
	}
}
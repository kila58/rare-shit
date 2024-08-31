class kui_tab : public kui_base
{
private:
	std::string name;

	int elevation = 4;

	bool active;

public:
	Color namecolor = Color(255, 255, 255, 255);
	Color backroundcolor = Color(231, 231, 231, 255);
	Color backroundhovercolor = Color(221, 236, 250, 255);
	Color selectedcolor = Color(255, 255, 255, 255);
	Color outlinecolor = Color(153, 153, 153, 255);
	Color outlinehovercolor = Color(121, 166, 245, 255);

	void Draw();

	void SetName(std::string _name){ name = _name; }

	kui_tab();
};

std::vector<kui_tab*> tabs;
std::vector<kui_tab*>::iterator tabiterator;

kui_tab::kui_tab()
{
	name = "Tab";

	active = false;

	tabs.push_back(this);
}

void kui_tab::Draw()
{
	if (!IsVisible())
		return;

	int _x, _y;
	GetPosition(&_x, &_y);

	tabiterator = std::find(tabs.begin(), tabs.end(), this);
	int index = std::distance(tabs.begin(), tabiterator);

	_x += (w * index);

	if (Input.MouseWithin(_x, _y, w, h) && Input.Mouse1Pressed() && !active)
	{
		for (int i = 0; i < tabs.size(); i++)
		{
			tabs[i]->active = false;
		}

		active = !active;
	}

	if (active)
	{
		//tab
		n_draw::FillRGBA(_x, _y - elevation, w, h + elevation, selectedcolor);

		//outline
		n_draw::OutlineRect(_x, _y - elevation, w, h + elevation, outlinecolor);

		//hide lower outline
		n_draw::FillRGBA(_x, _y + (h - 1), w, 1, selectedcolor);

		//name
		n_draw::DrawString(menufont, true, true, _x + (w / 2), (_y + ((h - elevation) / 2)) + 1, Color(230, 230, 230, 255), name.c_str());

		for (int i = 0; i < parented.size(); i++)
			parented[i]->SetVisible(true);
	}
	else
	{
		//tab
		n_draw::FillRGBA(_x, _y, w, h, Input.MouseWithin(_x, _y, w, h) ? backroundhovercolor : backroundcolor);

		//outline
		n_draw::OutlineRect(_x, _y, w, h, Input.MouseWithin(_x, _y, w, h) ? outlinehovercolor : outlinecolor);

		//name
		n_draw::DrawString(menufont, true, true, _x + (w / 2), (_y + (h / 2)) + 1, Color(230, 230, 230, 255), name.c_str());

		for (int i = 0; i < parented.size(); i++)
			parented[i]->SetVisible(false);
	}
}
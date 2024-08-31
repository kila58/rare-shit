class kui_checkbox : public kui_base
{
private:
	std::string name;

	int textspacer = 3;

public:
	Color namecolor = Color(255, 255, 255, 255);
	Color checkcolor = Color(0, 0, 0, 255);
	Color outlinecolor = Color(0, 0, 0, 255);	

	void Draw();

	void SetName(std::string _name){ name = _name; }

	bool* Variable;

	kui_checkbox();
};

kui_checkbox::kui_checkbox()
{
	name = "Check Box";
}

void kui_checkbox::Draw()
{
	if (!IsVisible())
		return;

	int _x, _y;
	GetPosition(&_x, &_y);

	if (Input.MouseWithin(_x, _y, w, h))
	{
		if (Input.Mouse1Pressed())
			*Variable = !*Variable;
	}

	//box
	n_draw::OutlineRect(_x, _y, w, h, outlinecolor);

	//Check
	if (*Variable)
		n_draw::DrawString(symbolfont, true, true, _x + (w / 2), _y + (h / 2), checkcolor, "b");

	//name
	n_draw::DrawString(menufont, false, true, _x + (w + textspacer), _y + (h / 2) + 1, namecolor, name.c_str());
}
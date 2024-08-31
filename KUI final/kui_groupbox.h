class kui_groupbox : public kui_base
{
private:
	std::string name;

	int headerheight = 20;

	int boxspacer = 4;

public:
	Color namecolor = Color(245, 245, 245, 255);
	Color boxcolor = Color(153, 153, 153, 255);
	Color bluehighlight = Color(0, 122, 204, 255);

	void Draw();

	void SetName(std::string _name){ name = _name; }

	kui_groupbox();
};

kui_groupbox::kui_groupbox()
{
	name = "Group Box";
}

void kui_groupbox::Draw()
{
	if (!IsVisible())
		return;

	int _x, _y;
	GetPosition(&_x, &_y);

	//Header
	n_draw::FillRGBA(_x, _y, w, headerheight, bluehighlight);

	//Box
	n_draw::OutlineRect(_x, _y + (headerheight + boxspacer), w, h - (headerheight + boxspacer), boxcolor);

	//name
	n_draw::DrawString(menufont, false, true, _x + 4, _y + (headerheight / 2), Color(230, 230, 230, 255), name.c_str());
}
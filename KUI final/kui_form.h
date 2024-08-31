class kui_form : public kui_base
{
private:
	std::string name;

	int borderwidth = 4;
	int headerheight = 20;

	bool drag;
	int offx = 0, offy = 0;

public:
	Color namecolor = Color(255, 255, 255, 255);
	Color backroundcolor = Color(255, 255, 255, 255);
	Color backroundoutlinecolor = Color(0, 0, 0, 255);
	Color bordercolor = Color(111, 201, 18, 255);
	Color borderoutlinecolor = Color(0, 0, 0, 255);

	void Draw();

	void SetName(std::string _name){ name = _name; }

	kui_form();
};

kui_form::kui_form()
{
	name = "Form";

	drag = false;

	for (int i = 0; i < elements.size(); i++)
	{
		if (elements[i] == this)
			elements.erase(elements.begin() + i);
	}

	windows.push_back(this);
}

void kui_form::Draw()
{
	if (Input.KeyState(VK_INSERT, 1000))
		visible = !visible;

	if (!IsVisible())
		return;

	int _x, _y;
	GetPosition(&_x, &_y);

	if ((Input.MouseWithin(_x - borderwidth, _y - headerheight, w + (borderwidth + borderwidth), headerheight) && Input.Mouse1Drag()) && !drag)
	{
		drag = true;
		offx = x - Input.mouse_x;
		offy = y - Input.mouse_y;
	}
	else if (drag && !Input.Mouse1Drag())
	{
		drag = false;
		offx = 0;
		offy = 0;
	}

	if (drag)
	{
		x = Input.mouse_x + offx;
		y = Input.mouse_y + offy;
	}

	int sw, sh;
	ints.engine->GetScreenSize(sw, sh);

	x = clamp(x, borderwidth + 1, sw - w - borderwidth - 1);
	y = clamp(y, headerheight + 1, sh - h - borderwidth - 1);


	//border + header
	n_draw::RectOutlined(_x - borderwidth, _y - headerheight, w + (borderwidth + borderwidth), h + (headerheight + borderwidth), 1, bordercolor, borderoutlinecolor);

	//header graident
	n_draw::FillRGBA(_x - borderwidth, _y - headerheight, w + (borderwidth + borderwidth), headerheight, bordercolor);

	//backround
	n_draw::RectOutlined(_x, _y, w, h, 1, backroundcolor, backroundoutlinecolor);

	//name
	n_draw::DrawString(menufont, true, true, _x + ((w + (borderwidth * 2)) / 2), _y - (headerheight / 2), namecolor, name.c_str());
}
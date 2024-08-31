class kui_splitter : public kui_base
{
private:
	std::string name;

	int righttextspacer = 10;
	int lefttextspacer = 14;

public:
	Color namecolor = Color(255, 255, 255, 255);
	Color linecolor = Color(0, 0, 0, 255);	

	void Draw();

	void SetName(std::string _name){ name = _name; }

	kui_splitter();
};

kui_splitter::kui_splitter()
{
	name = "Splitter";
}

void kui_splitter::Draw()
{
	if (!IsVisible())
		return;

	int _x, _y;
	GetPosition(&_x, &_y);

	int textw, texth;
	n_draw::GetTextLength(menufont, (char*)name.c_str(), textw, texth);

	//line
	n_draw::FillRGBA(_x, _y, w - (textw + lefttextspacer), 1, linecolor);

	//name
	n_draw::DrawString(menufont, false, true, _x + (w - (textw + righttextspacer)), _y - 1, namecolor, name.c_str());
}
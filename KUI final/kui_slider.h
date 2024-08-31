class kui_slider : public kui_base
{
private:
	std::string name;

	int innerbarh = 4;

	int innerbarseperator = 2;

	//lower the slider away from the text
	int lower = 14;

	bool dragging;

public:
	Color namecolor = Color(255, 255, 255, 255);
	Color backroundcolor = Color(231, 231, 231, 255);
	Color slidercolor = Color(111, 201, 18, 255);
	Color outlinecolor = Color(153, 153, 153, 153);

	void Draw();

	void SetName(std::string _name){ name = _name; }

	float* Variable;

	float Min;

	float Max;

	kui_slider();
};

kui_slider::kui_slider()
{
	name = "Slider";

	dragging = false;
}

void kui_slider::Draw()
{
	if (!IsVisible())
		return;

	int _x, _y;
	GetPosition(&_x, &_y);

	if (Input.MouseWithin(_x, _y + lower, w, h) && Input.Mouse1Pressed() && !dragging)
		dragging = true;

	if (dragging && !Input.Mouse1Drag())
		dragging = false;

	if (dragging)
	{
		//Big thanks to aria and/or deagler for this math
		float diff = (Input.mouse_x - _x);

		float perc = (diff / (w - (innerbarseperator * 2)));
		float range = Max - Min;
		range = range * perc;

		*Variable = clamp(roundf(Min + range), Min, Max);
	}

	int PaintValue = (*Variable * (w - (innerbarseperator * 2))) / Max;

	//backround
	n_draw::FillRGBA(_x, _y + lower, w, h, backroundcolor);

	//outline
	n_draw::OutlineRect(_x, _y + lower, w, h, outlinecolor);

	//bar
	n_draw::FillRGBA(_x + innerbarseperator, _y + (((h / 2) - (innerbarh / 2)) + lower), PaintValue, innerbarh, slidercolor);

	n_draw::DrawString(menufont, false, false, _x, _y, namecolor, name.c_str());

	n_draw::DrawString(menufont, false, false, _x + (w - 11), _y, namecolor, "%i", (int)*Variable);
}
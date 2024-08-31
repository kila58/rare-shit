class LCheckbox : public LBaseObject
{
public:
	void Think(){};
	void Paint();
	void Click();
	int* Var;
};

void LCheckbox::Paint()
{
	this->W = 13;
	this->H = 13;

	Draw->DrawBox(this->X-1, this->Y-1, this->W+2, this->H+2, Color(0,0,0,200));
	Draw->DrawBox(this->X, this->Y, this->W, this->H, ColorBg);
	Draw->DrawBox(this->X, this->Y, this->W, this->H, Color(0,0,0,50));

	if (*this->Var == 1)
		Draw->DrawBox(this->X + 3, this->Y + 3, this->W - 6, this->H - 6, ColorFg);

	int Width, Height;
	GetTextSize(FukoFontMenu, L"X", Width, Height);

	Draw->DrawString(FukoFontMenu, this->X + this->W + 5, this->Y + this->H*.5 - Height*.5, TextColor, this->Text);
}

void LCheckbox::Click()
{

	if (*this->Var == 1)
		*this->Var = 0;
	else
		*this->Var = 1;
}
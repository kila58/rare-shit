class LLabel : public LBaseObject
{
public:
	void Think(){};
	void Click(){};
	void Paint();

	bool IsCentered = false;

};

void LLabel::Paint()
{
	if (this->IsCentered)
		Draw->DrawStringA(FukoFontMenu, this->X, this->Y, TextColor, this->Text);
	else
		Draw->DrawString(FukoFontMenu, this->X, this->Y, TextColor, this->Text);
}


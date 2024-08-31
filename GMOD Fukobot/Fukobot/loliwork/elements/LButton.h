class LButton : public LBaseObject
{
public:
	void Paint();
	void Click();
	bool IsDown = false;
	void(*Callback)(void);
};

void LButton::Paint()
{
	Draw->DrawBox(this->X, this->Y, this->W, this->H, ColorFg);
	Draw->DrawStringA(FukoFont, this->X, this->Y, Color(255, 255, 255, 255), this->Text);
}

void LButton::Click()
{

	if (Callback == NULL)
		return;

	Callback();

}
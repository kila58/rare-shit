class LSlider : public LBaseObject
{
public:
	void Think();
	void Paint();
	void Click(){};
	
	int Max = 100;
	int Min = 0;

	int* Var;

};

void LSlider::Paint()
{

	int LineHeight = 5;
	int BarWidth = 6;

	Draw->DrawString(FukoFontMenu, X, Y - LineHeight - 10, TextColor, "%s: %i", Text, *Var);
	Draw->DrawBox(X, Y + 10, *Var*(W/Max), LineHeight, ColorFg);
	Draw->DrawBox(X + *Var*(W/Max) - BarWidth*.5, Y - 5 + 10, BarWidth, 15, ColorFg);
	Draw->DrawBoxOutline(X, Y + 10, W, LineHeight, ColorFg);
}

void LSlider::Think()
{
	if (this->_Clicked)
	{
		int Value = LoliInput.GetMouseX() - X;
		Value = (Value * Max) / W;

		
		if (Value < Min)
			Value = Min;

		if (Value > Max)
			Value = Max;

		*Var = Value;

	}
}
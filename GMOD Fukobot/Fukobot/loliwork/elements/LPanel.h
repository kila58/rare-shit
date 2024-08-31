class LPanel : public LBaseObject
{
public:
	void Think();
	void Paint();
	void Click();
	bool ShouldDrag();
	
	int MenuBar = 25;
	bool _Dragging = false;

	int DragOffX = 0;
	int DragOffY = 0;

};

bool LPanel::ShouldDrag()
{
	if (!this->_Clicked)
		return false;

	if ((LoliInput.GetMouseX() >= this->X && LoliInput.GetMouseX() <= this->X + this->W) && (LoliInput.GetMouseY() >= this->Y && LoliInput.GetMouseY() <= this->Y + this->MenuBar))
		this->_Dragging = true;

	return (this->_Dragging);

}

void LPanel::Paint()
{
	Draw->DrawBox(this->X, this->Y, this->W, this->H, ColorBg);
	Draw->DrawBox(this->X, this->Y, this->W, this->MenuBar, ColorFg);
	Draw->DrawBoxOutline(this->X, this->Y, this->W, this->H, ColorFg);
	Draw->DrawBoxOutline(this->X-1, this->Y-1, this->W+2, this->H+2, ColorFg);
	Draw->DrawBoxOutline(this->X - 2, this->Y - 2, this->W + 4, this->H + 4, ColorFg);
	Draw->DrawString(FukoFontMenuTitle, this->X + 5, this->Y + 2, Color(255, 255, 255, 255), this->Text);
}

void LPanel::Think()
{
	if (this->ShouldDrag())
	{
		this->_X = LoliInput.GetMouseX() -  this->W*.5;
		this->_Y = LoliInput.GetMouseY() - 10;
	}
}

void LPanel::Click()
{
	this->_Dragging = false;
	this->DragOffX = this->X + LoliInput.GetMouseX() - this->X;
	this->DragOffY = LoliInput.GetMouseY() - this->Y;
}
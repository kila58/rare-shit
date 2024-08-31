class LBaseObject
{
public:

	void Init(std::vector<LBaseObject*>*);

	// Hooks
	virtual void Paint() {};
	virtual void Think() {};
	virtual void Click() {};

	void DoPaint();
	void DoThink();

	// Position/Size
	int _X = 0;
	int _Y = 0;
	int X = 0;
	int Y = 0;
	void SetPos(int x, int y) { _X = x; _Y = y; };
	void GetPos(int &x, int &y) { x = _X; y = _Y; };
	int W = 0;
	int H = 0;
	void SetSize(int w, int h) { W = w; H = h; };
	void GetSize(int &w, int &h) { w = W; h = H; };

	// Misc. Variables
	const char* Text = "LText";
	bool Enabled = true;

	// Input related variables
	bool _Hovered	= false;
	bool _Clicked	= false;
	bool _Released	= false;

	// Children and parents
	LBaseObject* _Children[128];
	int	_ChildCount = 0;
	bool AddChild(LBaseObject* Child) { if (this->_ChildCount <= 128) { this->_Children[_ChildCount] = Child; this->_ChildCount++; return true; } else { return false; } };
	LBaseObject* _Parent = NULL;
	void SetParent(LBaseObject* Parent) { this->_Parent = Parent; };

};

void LBaseObject::DoPaint()
{

	if (!this->Enabled) return;

	this->Paint();
}

void LBaseObject::DoThink()
{

	if (!this->Enabled) return;

	this->Think();
	this->_Hovered = false;

	if (this->_Parent == NULL) // All panels (except LOverlayPanel) should have a parent.
		return;

	this->X = this->_Parent->X + this->_X;
	this->Y = this->_Parent->Y + this->_Y;

	if ((LoliInput.GetMouseX() >= this->X && LoliInput.GetMouseX() <= this->X + this->W) && (LoliInput.GetMouseY() >= this->Y && LoliInput.GetMouseY() <= this->Y + this->H))
		this->_Hovered = true;

	if (LoliInput.IsMouseDown() && this->_Hovered)
	{
		this->_Released = false;
		this->_Clicked = true;
	}

	if (this->_Clicked && !LoliInput.IsMouseDown())
	{
		this->_Clicked = false;
		this->_Released = true;
	}

	if (this->_Released && this->_Hovered)
	{
		this->_Released = false;
		this->Click();
	}

}

void LBaseObject::Init(std::vector<LBaseObject*>* IList)
{

	IList->push_back(this);
}
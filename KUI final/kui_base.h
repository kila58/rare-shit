class kui_base
{
public:
	int x, y;
	int w, h;

	bool visible = true;

	Color color;

	void SetPosition(int _x, int _y){ x = _x, y = _y; }
	void GetPosition(int*, int*);
	void SetDimensions(int _w, int _h){ w = _w, h = _h; }
	void SetColor(Color _color){ color = _color; }

	bool IsVisible();
	void SetVisible(bool vis);

	std::vector<kui_base*> parented;
	kui_base* parent = nullptr;

	void SetParent(kui_base*);
	kui_base* GetParent(){ return parent; }

	virtual void Draw(){}

	kui_base();
};

std::vector<kui_base*> windows;
std::vector<kui_base*> elements;

kui_base::kui_base()
{
	x = 0, y = 0;
	w = 0, h = 0;
	color = Color(255, 255, 255, 255);

	elements.push_back(this);
}

bool kui_base::IsVisible()
{
	if ((parent != nullptr) && !parent->IsVisible())
		return false;

	return (visible);
}

void kui_base::SetVisible(bool vis)
{
	this->visible = vis;
}

void kui_base::SetParent(kui_base* element)
{
	if (element == this)
		return;

	parent = element;
	parent->parented.push_back(this);
}

void kui_base::GetPosition(int* _x, int* _y)
{
	int px, py;

	if (parent == nullptr)
		*_x = x, *_y = y;
	else
	{
		parent->GetPosition(&px, &py);
		*_x = px + x;
		*_y = py + y;
	}
}
#pragma once

#define DEFAULT_WIDTH 16
#define DEFAULT_HEIGHT 16

class CheckBox : public virtual Base, public Child
{
protected:
	bool enabled = false;
public:
	CheckBox() : Base(DEFAULT_WIDTH, DEFAULT_HEIGHT) {};
	
	void Think();
	void Draw();
	void OnClick();
};

void CheckBox::Think()
{

}

void CheckBox::Draw()
{
	Frame* parent = GetParent();
	Vector2& pos = parent->GetPos();

	int x = this->x, y = this->y;

	//if (parent)
	//	x += parent->x, y += parent->y;

	if (enabled)
		draw::SetColor(Color(0, 128, 0));
	else
		draw::SetColor(Color(128, 0, 0));

	draw::FilledRect(x, y, w, h);

	draw::SetColor(Color(0, 0, 0, 128));
	draw::OutlinedRect(x, y, w, h);
}

void CheckBox::OnClick()
{
	cvar->ConsoleColorPrintf(Color(255, 255, 255), "clicked\n");
}
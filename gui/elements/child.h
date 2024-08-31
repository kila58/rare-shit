#pragma once

// inherets base cuz yolo
class Child : public virtual Base
{
protected:
	Frame* parent = nullptr;
public:
	Frame* GetParent();
	void SetParent(Frame* parent);

	virtual void OnClick() {};
};

Frame* Child::GetParent()
{
	return parent;
}

void Child::SetParent(Frame *parent)
{
	this->parent = parent;
}
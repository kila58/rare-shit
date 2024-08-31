#pragma once

#include "../gui.h"
#include "../../features/menu.h"

#define DRAGBOUNDS_HEIGHT 23

class Frame : public virtual Base
{
protected:
	std::string name = "";
	std::vector<std::reference_wrapper<Child>> children;
	bool dragging = false;
	bool moving = false;
	int offx = 0, offy = 0;
public:
	Frame() {}
	Frame(const std::string& name) : name(name), Base() {}

	void Think();
	void Draw();

	std::string GetName();
	void SetName(const std::string& name);

	std::vector<std::reference_wrapper<Child>> GetChildren();

	bool GetDragging();
	void SetDragging(bool dragging);
	
	void AddChild(Child& child);
};

void Frame::Think()
{
	if (!GetVisible())
		return;

	int x = this->x, y = this->y;

	int mx, my;
	util::GetMousePosition(mx, my);

	if (dragging && !moving)
	{
		moving = true;

		offx = x - mx;
		offy = y - my;
	}
	else if (moving && !dragging)
	{
		moving = false;

		offx = 0;
		offy = 0;
	}

	if (moving)
		this->x = mx + offx, this->y = my + offy;

	static bool first = true;

	for (auto& pointer : children)
	{
		auto& child = pointer.get();

		if (first)
			first = false, child.SetParent(this);

		child.Think();
	}
}

void Frame::Draw()
{
	if (!GetVisible())
		return;

	// outside border
	draw::SetColor(Color(0, 0, 0, 215));
	draw::FilledRect(x - 1, y - 1, w + 2, h + 2);

	// main
	draw::SetColor(Color(32, 32, 32));
	draw::FilledRect(x, y, w, h);

	// titlebar
	draw::SetColor(Color(48, 48, 48));
	draw::FilledRect(x, y, w, DRAGBOUNDS_HEIGHT);

	// inside padding
	draw::OutlinedRect(x, y, w, h);
	draw::OutlinedRect(x + 1, y + 1, w - 2, h - 2);
	draw::OutlinedRect(x + 2, y + 2, w - 4, h - 4);

	draw::SetColor(Color(22, 22, 22));
	draw::OutlinedRect(x + 3, y + DRAGBOUNDS_HEIGHT, w - 6, h - DRAGBOUNDS_HEIGHT - 3);

	draw::SetTextColor(Color(215, 215, 215));
	draw::Text(menu.font, Color(215, 215, 215), false, false, false, x + 4, y + 3, name.c_str());

	for (auto& child : children)
	{
		child.get().Draw();
	}
}

std::string Frame::GetName()
{
	return name;
}

void Frame::SetName(const std::string& name)
{
	this->name = name;
}

std::vector<std::reference_wrapper<Child>> Frame::GetChildren()
{
	return children;
}

bool Frame::GetDragging()
{
	return dragging;
}

void Frame::SetDragging(bool dragging)
{
	this->dragging = dragging;
}

void Frame::AddChild(Child& child)
{
	child.x += x, child.y += y;

	children.emplace_back(child);
}
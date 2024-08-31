#pragma once

class Vector2
{
public:
	Vector2() {}
	Vector2(int x, int y) : x(x), y(y) {}

	int x;
	int y;
};

size_t indexcount = 0;

class Base
{
protected:
	size_t index = 0;
	bool visible = false;
public:
	int x = 0, y = 0, w = 0, h = 0;

	Base() { indexcount++, index = indexcount; };
	Base(int w, int h) : w(w), h(h) { Base(); };

	void GetPos(int &x, int &y);
	Vector2 GetPos();
	void SetPos(int x, int y);
	void SetPos(const Vector2& pos);

	void GetSize(int &w, int &h);
	void SetSize(int w, int h);

	size_t GetIndex();
	void SetIndex(size_t index);

	bool GetVisible();
	void SetVisible(bool visible);

	virtual void Think() {};
	virtual void Draw() {};

	friend bool operator==(const Base& first, const Base& second);
	friend bool operator!=(const Base& first, const Base& second);

	virtual ~Base() {}
};

void Base::GetPos(int &x, int &y)
{
	x = this->x, y = this->y;
}

Vector2 Base::GetPos()
{
	return Vector2(x, y);
}

void Base::SetPos(int x, int y)
{
	this->x = x, this->y = y;
}

void Base::SetPos(const Vector2& pos)
{
	x = pos.x, y = pos.y;
}

void Base::GetSize(int &w, int &h)
{
	w = this->w, h = this->h;
}

void Base::SetSize(int w, int h)
{
	this->w = w, this->h = h;
}

size_t Base::GetIndex()
{
	return index;
}

void Base::SetIndex(size_t index)
{
	this->index = index;
}

bool Base::GetVisible()
{
	return visible;
}

void Base::SetVisible(bool visible)
{
	this->visible = visible;
}

bool operator==(const Base& first, const Base& second)
{
	return first.index == second.index;
}

bool operator!=(const Base& first, const Base& second)
{
	return first.index != second.index;
}
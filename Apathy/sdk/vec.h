#pragma once

typedef float matrix3x4[3][4];

#define pi 3.14159265358979323846
#define rad(a) a*(180/pi)
#define deg(a) a*(pi/180)

class Color {
public:
	Color(int _r, int _g, int _b, int _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}
	Color(int _r, int _g, int _b)
	{
		r = _r;
		g = _g;
		b = _b;
		a = 255;
	}
	void operator +=(Color &o)
	{
		r += o.r;
		g += o.g;
		b += o.b;
		a += o.a;
	}
	Color operator -(Color &o)
	{
		return Color(r - o.r, g - o.g, b - o.b, a - o.a);
	}
public:
	char a, r, g, b;
}; // Credits: MeepDarknessMeep

class ang3
{
public:
	float x, y, z;
	ang3(float x1 = 0, float y1 = 0, float z1 = 0)
	{
		x = x1;
		y = y1;
		z = z1;
	}
	float& operator[](int i)
	{
		if (i == 1)
			return x;
		else if (i == 2)
			return y;
		else if (i == 3)
			return z;
	}
	bool operator==(ang3 a)
	{
		return a.x == x && a.y == y && a.z == z;
	}
	bool operator!=(ang3 a)
	{
		return a.x != x || a.y != y || a.z != z;
	}
	void operator+=(ang3 a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
	}
	void operator-=(ang3 a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
	}
	void operator*=(ang3 a)
	{
		x *= a.x;
		y *= a.y;
		z *= a.z;
	}
	void operator*=(float a)
	{
		x *= a;
		y *= a;
		z *= a;
	}
	void operator/=(ang3 a)
	{
		x /= a.x;
		y /= a.y;
		z /= a.z;
	}
	void operator/=(float a)
	{
		x /= a;
		y /= a;
		z /= a;
	}
	ang3 operator+(ang3 a) const
	{
		ang3 result = a;
		result.x += x;
		result.y += y;
		result.z += z;
		return result;
	}
	ang3 operator-(ang3 a)
	{
		ang3 result = a;
		result.x = x - a.x;
		result.y = y - a.y;
		result.z = z - a.z;
		return result;
	}
	ang3 operator*(ang3 a)
	{
		ang3 result = a;
		result.x = x*a.x;
		result.y = y*a.y;
		result.z = z*a.z;
		return result;
	}
	ang3 operator*(float a)
	{
		ang3 result = a;
		result.x = x*a;
		result.y = y*a;
		result.z = z*a;
		return result;
	}
	ang3 operator/(ang3 a)
	{
		ang3 result;
		result.x = x / a.x;
		result.y = y / a.y;
		result.z = z / a.z;
		return result;
	}
	ang3 operator/(float a)
	{
		ang3 result = a;
		result.x = x / a;
		result.y = x / a;
		result.z = x / a;
		return result;
	}
	float Length()
	{
		float root = 0;
		float sqsr = x*x + y*y + z*z;
		_asm
		{
			sqrtss xmm0, sqsr
				movss root, xmm0
		}
		return root;
	}
	float Dot(ang3 a)
	{
		return x*a.x + y*a.y + z*a.z;
	}
	ang3 Normal()
	{
		return (*this)*(1 / (Length() + 1.192092896e-07F));
	}
	ang3 Angle()
	{
		if (!x && !y)
			return ang3();
		ang3 result;
		result.x = rad(atan2(-z, sqrt(x*x + y*y)));
		result.y = rad(atan2(y, x));
		if (result.x < 0)
			result.x += 360;
		if (result.y < 0)
			result.y += 360;
		return result;
	}
	ang3 Forward()
	{
		ang3 s = Sin();
		ang3 c = Cos();
		ang3 result;
		result.x = c.x*c.y;
		result.y = c.x*s.y;
		result.z = -s.x;
		return result;
	}
	ang3 Right()
	{
		ang3 s = Sin();
		ang3 c = Cos();
		ang3 result;
		result.x = -1 * s.z*s.x*c.y + -1 * c.z*-s.y;
		result.y = -1 * s.z*s.x*s.y + -1 * c.z*c.y;
		result.z = -1 * s.z*c.z;
		return result;
	}
	ang3 Up()
	{
		ang3 s = Sin();
		ang3 c = Cos();
		ang3 result;
		result.x = c.z*s.x*c.y + -s.z*-s.y;
		result.y = c.z*s.x*s.y + -s.z*c.y;
		result.z = c.z*c.x;
		return result;
	}
	void Clamp()
	{
		if (x > 180)
			x -= 360;
		if (x < -180)
			x += 360;
		if (y > 180)
			y -= 360;
		if (y < -180)
			y += 360;
	}
private:
	ang3 Sin()
	{
		ang3 result;
		result.x = sin(deg(x));
		result.y = sin(deg(y));
		result.z = sin(deg(z));
		return result;
	}
	ang3 Cos()
	{
		ang3 result;
		result.x = cos(deg(x));
		result.y = cos(deg(y));
		result.z = cos(deg(z));
		return result;
	}
};

class vec3
{
public:
	float x,y,z;
	vec3(float x1 = 0,float y1 = 0,float z1 = 0)
	{
		x = x1;
		y = y1;
		z = z1;
	}
	float& operator[](int i)
	{
		if (i == 1)
			return x;
		else if (i == 2)
			return y;
		else if (i == 3)
			return z;
	}
	bool operator==(vec3 a)
	{
		return a.x == x && a.y == y && a.z == z;
	}
	bool operator!=(vec3 a)
	{
		return a.x != x || a.y != y || a.z != z;
	}
	void operator+=(vec3 a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
	}
	void operator-=(vec3 a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
	}
	void operator*=(vec3 a)
	{
		x *= a.x;
		y *= a.y;
		z *= a.z;
	}
	void operator*=(float a)
	{
		x *= a;
		y *= a;
		z *= a;
	}
	void operator/=(vec3 a)
	{
		x /= a.x;
		y /= a.y;
		z /= a.z;
	}
	void operator/=(float a)
	{
		x /= a;
		y /= a;
		z /= a;
	}
	vec3 operator+(vec3 a) const
	{
		vec3 result = a;
		result.x += x;
		result.y += y;
		result.z += z;
		return result;
	}
	vec3 operator-(vec3 a)
	{
		vec3 result = a;
		result.x = x - a.x;
		result.y = y - a.y;
		result.z = z - a.z;
		return result;
	}
	vec3 operator*(vec3 a)
	{
		vec3 result = a;
		result.x = x*a.x;
		result.y = y*a.y;
		result.z = z*a.z;
		return result;
	}
	vec3 operator*(float a)
	{
		vec3 result = a;
		result.x = x*a;
		result.y = y*a;
		result.z = z*a;
		return result;
	}
	vec3 operator/(vec3 a)
	{
		vec3 result;
		result.x = x/a.x;
		result.y = y/a.y;
		result.z = z/a.z;
		return result;
	}
	vec3 operator/(float a)
	{
		vec3 result = a;
		result.x = x/a;
		result.y = x/a;
		result.z = x/a;
		return result;
	}
	float Length()
	{
		float root = 0;
		float sqsr = x*x+y*y+z*z;
		_asm
		{
			sqrtss xmm0, sqsr
			movss root, xmm0
		}
		return root;
	}
	float Dot(vec3 a)
	{
		return x*a.x + y*a.y + z*a.z;
	}
	vec3 Normal()
	{
		return (*this)*(1/(Length()+1.192092896e-07F));
	}
	vec3 Angle()
	{
		if (!x && !y)
			return vec3();
		vec3 result;
		result.x = rad(atan2(-z,sqrt(x*x+y*y)));
		result.y = rad(atan2(y,x));
		if (result.x < 0)
			result.x += 360;
		if (result.y < 0)
			result.y += 360;
		return result;
	}
	vec3 Forward()
	{
		vec3 s = Sin();
		vec3 c = Cos();
		vec3 result;
		result.x = c.x*c.y;
		result.y = c.x*s.y;
		result.z = -s.x;
		return result;
	}
	vec3 Right()
	{
		vec3 s = Sin();
		vec3 c = Cos();
		vec3 result;
		result.x = -1*s.z*s.x*c.y+-1*c.z*-s.y;
		result.y = -1*s.z*s.x*s.y+-1*c.z*c.y;
		result.z = -1*s.z*c.z;
		return result;
	}
	vec3 Up()
	{
		vec3 s = Sin();
		vec3 c = Cos();
		vec3 result;
		result.x = c.z*s.x*c.y+-s.z*-s.y;
		result.y = c.z*s.x*s.y+-s.z*c.y;
		result.z = c.z*c.x;
		return result;
	}
	void Clamp()
	{
		if (x > 180)
			x -= 360;
		if (x < -180)
			x += 360;
		if (y > 180)
			y -= 360;
		if (y < -180)
			y += 360;
	}
private:
	vec3 Sin()
	{
		vec3 result;
		result.x = sin(deg(x));
		result.y = sin(deg(y));
		result.z = sin(deg(z));
		return result;
	}
	vec3 Cos()
	{
		vec3 result;
		result.x = cos(deg(x));
		result.y = cos(deg(y));
		result.z = cos(deg(z));
		return result;
	}
};
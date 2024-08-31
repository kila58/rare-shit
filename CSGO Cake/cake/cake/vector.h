class vector
{
public:
	float x, y, z;
	inline void Init(float ix, float iy, float iz)
	{
		x = ix; y = iy; z = iz;
	}
	vector()
	{
		this->x = 0, this->z = 0, this->z = 0;
	}
	vector(float ix, float iy, float iz)
	{
		this->x = ix, this->y = iy, this->z = iz;
	}

	bool operator==(vector vdst)
	{
		return(this->x == vdst.x && this->y == vdst.y && this->z == vdst.z);
	}

	bool operator!=(vector vdst)
	{
		return(this->x != vdst.x || this->y != vdst.y || this->z != vdst.z);
	}
	inline float Length()
	{
		return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
	}
	vector operator+(vector vdst)
	{
		return vector(this->x + vdst.x, this->y + vdst.y, this->z + vdst.z);
	}

	vector operator*(float fdst)
	{
		return vector(this->x * fdst, this->y * fdst, this->z * fdst);
	}

	vector operator+=(vector vdst)
	{
		this->x += vdst.x, this->y += vdst.y, this->z += vdst.z;
	}

	vector operator-(vector vdst)
	{
		return vector(this->x - vdst.x, this->y - vdst.y, this->z - vdst.z);
	}

	void clamp()
	{
		if (this->x > 89)
			this->x -= 178;

		if (this->x < -89)
			this->x += 178;

		if (this->y > 179)
			this->y -= 358;

		if (this->y < -179)
			this->y += 358;

		this->z = 0;
	}

	float fdistance(vector &vdst)
	{
		return sqrt(pow(vdst.x - this->x, 2) + pow(vdst.y - this->y, 2) + pow(vdst.z - this->z, 2));
	}

	float length_sqr()
	{
		return ((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
	}
};

typedef vector qangle;

class __declspec(align(16))vectoraligned : public vector
{
public:
	vectoraligned& operator=(const vector &vdst)
	{
		this->x = vdst.x;
		this->y = vdst.y;
		this->z = vdst.z;
		return *this;
	}
};
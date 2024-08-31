class color
{
public:
	char c[4];
	color()
	{
		c[0] = (unsigned char)0;
		c[1] = (unsigned char)0;
		c[2] = (unsigned char)0;
		c[3] = (unsigned char)0;
	}
	color(int r, int g, int b, int a)
	{
		c[0] = (unsigned char)r;
		c[1] = (unsigned char)g;
		c[2] = (unsigned char)b;
		c[3] = (unsigned char)a;
	}
	inline int r() const	{ return c[0]; }
	inline int g() const	{ return c[1]; }
	inline int b() const	{ return c[2]; }
	inline int a() const	{ return c[3]; }
};
class floatie
{
public:
	bool i = false;
	int x = 0;
	int y = 0;
	int alpha = 255;
	std::string sdata = "null";
	floatie(int ix, int iy, std::string scontains)
	{
		this->x = ix;
		this->y = iy;
		this->sdata = scontains;
	}
	void update()
	{
		if (this->y > -2)
		{
			utils::drawtxt(this->x, this->y, color(255, 0, 0, this->alpha), this->sdata, 7);

			this->y--;
			
			if (this->alpha >= 5)
			{
				this->alpha -= 5;
			}
		}
	}
};
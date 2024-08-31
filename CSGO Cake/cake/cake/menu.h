//notes
/*
	0x25 left
	0x27 right
*/
namespace data
{
	int iesp = 0;
	int ifloaties = 0;
	int itracers = 0;
	int ibhop = 0;
	int iflicker = 0;
	int ireverse = 0;
	int ijitter = 0;
	int ircs = 0;
	int iaimbot_fov = 0;
}

namespace ui
{
	void fr(int x1, int y1, int x2, int y2, char ccolor)
	{
		if (ccolor == 'w')
		{
			g::ivguisurface->set_color(color(255, 254, 255, 255));
		}
		else if (ccolor == 't')
		{
			g::ivguisurface->set_color(color(121, 210, 212, 255));
		}
		else if (ccolor == 'tt')
		{
			g::ivguisurface->set_color(color(121, 210, 212, 10));
		}
		else if (ccolor == 'b')
		{
			g::ivguisurface->set_color(color(1, 0, 1, 255));
		}
		else
		{
			g::ivguisurface->set_color(color(255, 254, 255, 255));
		}

		g::ivguisurface->fill_rect(x1, y1, x2, y2);
	}

	void ft_header1(int x1, int y1, std::string sdata)
	{
		utils::drawtxt(x1, y1, color(255, 254, 255, 255), sdata, 20);
	}

	void ft_header1a(int x1, int y1, std::string sdata)
	{
		utils::drawtxt(x1, y1, color(121, 210, 212, 255), sdata, 20);
	}
}

namespace selector
{
	float fdegrees = 0;
	int islot = 1;
	int ix = 2;
	void update()
	{
		if (GetAsyncKeyState(0x28) & 1 && islot < 9)
			islot++;
		if (GetAsyncKeyState(0x26) & 1 && islot > 1)
			islot--;

		if ((GetAsyncKeyState(0x27) & 1))
		{
			if (islot == 1)
			{
				if (data::iesp == 1)
				{
					data::iesp = 0;
				}
				else
				{
					data::iesp = 1;
				}
			}
			if (islot == 2)
			{
				if (data::ifloaties == 1)
				{
					data::ifloaties = 0;
				}
				else
				{
					data::ifloaties = 1;
				}
			}
			if (islot == 3)
			{
				if (data::itracers == 1)
				{
					data::itracers = 0;
				}
				else
				{
					data::itracers = 1;
				}
			}
			if (islot == 4)
			{
				if (data::ibhop == 1)
				{
					data::ibhop = 0;
				}
				else
				{
					data::ibhop = 1;
				}
			}
			if (islot == 5)
			{
				if (data::iflicker == 1)
				{
					data::iflicker = 0;
				}
				else
				{
					data::iflicker = 1;
				}
			}
			if (islot == 6)
			{
				if (data::ireverse == 1)
				{
					data::ireverse = 0;
				}
				else
				{
					data::ireverse = 1;
				}
			}
			if (islot == 7)
			{
				if (data::ijitter == 1)
				{
					data::ijitter = 0;
				}
				else
				{
					data::ijitter = 1;
				}
			}
			if (islot == 8)
			{
				if (data::ircs == 1)
				{
					data::ircs = 0;
				}
				else
				{
					data::ircs = 1;
				}
			}
		}


		ui::fr(ix, 200 + 98 + (30 * islot), ix + 2 + abs(10 * sin(fdegrees)), 200 + (98 + (30 * islot)) + 30, 'tt');

		if (fdegrees >= 360)
		{
			fdegrees = 0;
		}

		fdegrees += 0.1f;
	}
}

namespace ui
{
	bool bopen = false;
	void update()
	{
		if (GetAsyncKeyState(0x46) & 1)
		{
			bopen = !bopen;
		}

		if (bopen)
		{	
			fr(0, 200 + 96, 202, 200 + 402, 't');
			fr(2, 200 + 98, 200, 200 + 400, 'b');
			utils::drawtxt(2, 200 + 98, math::crandom_color(), std::string(/*.cake*/XorStr<0xA5, 6, 0xA803BB53>("\x8B\xC5\xC6\xC3\xCC" + 0xA803BB53).s), 8);
			fr(2, 200 + 98 + 30, 200, 200 + 98 + 30 + 2, 't');

			ft_header1a(15, 200 + 98 + 30 + 5, /*$*/XorStr<0xA1, 2, 0xB6222249>("\x85" + 0xB6222249).s);
			ft_header1(30, 200 + 98 + 30 + 5, /*esp*/XorStr<0x4A, 4, 0x355452B2>("\x2F\x38\x3C" + 0x355452B2).s);
			ft_header1a(100 + 13, 200 + 98 + 30 + 5 + 2, std::to_string(data::iesp));

			ft_header1a(15, 200 + 98 + 30 + 35, /*$*/XorStr<0xA1, 2, 0xB6222249>("\x85" + 0xB6222249).s);
			ft_header1(30, 200 + 98 + 30 + 35, /*floaties*/XorStr<0x9E, 9, 0x230EB3C6>("\xF8\xF3\xCF\xC0\xD6\xCA\xC1\xD6" + 0x230EB3C6).s);
			ft_header1a(100 + 13, 200 + 98 + 30 + 35 + 2, std::to_string(data::ifloaties));

			ft_header1a(15, 200 + 98 + 30 + 65, /*$*/XorStr<0xA1, 2, 0xB6222249>("\x85" + 0xB6222249).s);
			ft_header1(30, 200 + 98 + 30 + 65, /*tracers*/XorStr<0x26, 8, 0xD28778EB>("\x52\x55\x49\x4A\x4F\x59\x5F" + 0xD28778EB).s);
			ft_header1a(100 + 13, 200 + 98 + 30 + 65 + 2, std::to_string(data::itracers));

			ft_header1a(15, 200 + 98 + 30 + 95, /*$*/XorStr<0xA1, 2, 0xB6222249>("\x85" + 0xB6222249).s);
			ft_header1(30, 200 + 98 + 30 + 95, /*bhop*/XorStr<0x3B, 5, 0x6558EE97>("\x59\x54\x52\x4E" + 0x6558EE97).s);
			ft_header1a(100 + 13, 200 + 98 + 30 + 95 + 2, std::to_string(data::ibhop));

			ft_header1a(15, 200 + 98 + 30 + 95 + 30, /*$*/XorStr<0xA1, 2, 0xB6222249>("\x85" + 0xB6222249).s);
			ft_header1(30, 200 + 98 + 30 + 95 + 30, /*flicker aa*/XorStr<0x88, 11, 0x69B039FE>("\xEE\xE5\xE3\xE8\xE7\xE8\xFC\xAF\xF1\xF0" + 0x69B039FE).s);
			ft_header1a(100 + 13, 200 + 98 + 30 + 95 + 2 + 30, std::to_string(data::iflicker));

			ft_header1a(15, 200 + 98 + 30 + 95 + 30 + 30, /*$*/XorStr<0xA1, 2, 0xB6222249>("\x85" + 0xB6222249).s);
			ft_header1(30, 200 + 98 + 30 + 95 + 30 + 30, /*reverse aa*/XorStr<0x80, 11, 0x06FB0F1C>("\xF2\xE4\xF4\xE6\xF6\xF6\xE3\xA7\xE9\xE8" + 0x06FB0F1C).s);
			ft_header1a(100 + 13, 200 + 98 + 30 + 95 + 2 + 30 + 30, std::to_string(data::ireverse));

			ft_header1a(15, 200 + 98 + 30 + 95 + 30 + 30 + 30, /*$*/XorStr<0xA1, 2, 0xB6222249>("\x85" + 0xB6222249).s);
			ft_header1(30, 200 + 98 + 30 + 95 + 30 + 30 + 30, /*jitter aa*/XorStr<0xAA, 10, 0xFA43149D>("\xC0\xC2\xD8\xD9\xCB\xDD\x90\xD0\xD3" + 0xFA43149D).s);
			ft_header1a(100 + 13, 200 + 98 + 30 + 95 + 2 + 30 + 30 + 30, std::to_string(data::ijitter));

			ft_header1a(15, 200 + 98 + 30 + 95 + 30 + 30 + 30 + 30, /*$*/XorStr<0xA1, 2, 0xB6222249>("\x85" + 0xB6222249).s);
			ft_header1(30, 200 + 98 + 30 + 95 + 30 + 30 + 30 + 30, /*rcs*/XorStr<0x5B, 4, 0x66A705E4>("\x29\x3F\x2E" + 0x66A705E4).s);
			ft_header1a(100 + 13, 200 + 98 + 30 + 95 + 2 + 30 + 30 + 30 + 30, std::to_string(data::ircs));

			selector::update();
		}
	}
}
class isurface
{
public:
	virtual void filler0() = 0;
	virtual void filler1() = 0;
	virtual void filler2() = 0;
	virtual void filler3() = 0;
	virtual void filler4() = 0;
	virtual void filler5() = 0;
	virtual void filler6() = 0;
	virtual void filler7() = 0;
	virtual void filler8() = 0;
	virtual void filler9() = 0;
	virtual void filler10() = 0;
	virtual void filler11() = 0;
	virtual void filler12() = 0;
	virtual void filler13() = 0;
	virtual void set_color(color ccol) = 0;
	virtual void filler15() = 0;
	virtual void fill_rect(int ix1, int iy1, int ix2, int iy2) = 0;
	virtual void filler17() = 0;
	virtual void fill_orect(int ix1, int iy1, int ix2, int iy2) = 0;
	virtual void fill_line(int x0, int y0, int x1, int y1) = 0;
	virtual void filler20() = 0;
	virtual void filler21() = 0;
	virtual void filler22() = 0;
	virtual void text_set_font(int ifont) = 0;
	virtual void text_set_color(color ccol) = 0;
	virtual void filler25() = 0;
	virtual void text_set_pos(int ix1, int iy1) = 0;
	virtual void filler27() = 0;
	virtual void text_render(const wchar_t* ctext, int ilen) = 0;
};
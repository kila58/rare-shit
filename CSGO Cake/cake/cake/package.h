#pragma warning(disable: 4244)

#include <Windows.h>
#include <string>
#include <string.h>
#include <math.h>
#include <amp_math.h>

#include "str_scrambling.h"
#include "vector.h"
#include "utils.h"
#include "color.h"
#include "fishing.h"

#include "usercmd.h"
#include "ibaseinterface.h"
#include "ipanel.h"
#include "icliententity.h"
#include "ivengineclient.h"
#include "iappsystem.h"
#include "isurface.h"
#include "icliententitylist.h"
#include "trace.h"
#include "itracefilter.h"
#include "ienginetrace.h"

#define stdc __stdcall
#define fstc __fastcall

#include "igameevent.h"
#include "igameeventlistener.h"

namespace g
{
	interface_t iengine;
	interface_t iclient;
	interface_t ivgui2;
	interface_t imatsurface;
	interface_t ivstd;

	ipanel* ivguipanel;
	isurface* ivguisurface;
	icliententitylist* ientlist;
	ivengineclient* ivengine;
	ienginetrace* itrace;

	igameeventlistener* ilistener;

	fisherman* vclientmode;
	fisherman* vpanel;
}

#include "calculator.h"

#include "debug.h"

namespace utils
{
	void drawtxt(int ix, int iy, color ccolor, const std::string& stxt, unsigned int ifont)
	{
		g::ivguisurface->text_set_font(ifont);
		g::ivguisurface->text_set_color(ccolor);
		g::ivguisurface->text_set_pos(ix, iy);

		std::wstring stxt_wide;
		std::wstring wsTmp(stxt.begin(), stxt.end());
		stxt_wide = wsTmp;
		const wchar_t* ctxt = stxt_wide.c_str();
		g::ivguisurface->text_render(ctxt, wcslen(ctxt));
	}
	void dump_fonts(int ilast_font)
	{
		for (int ifont = 0; ifont < ilast_font; ifont++)
		{
			drawtxt(50, 20 + (20 * ifont), color(255, 255, 255, 255), std::to_string(ifont) + std::string("quick brown fox"), ifont);
		}
	}
}

#include "menu.h"

#include "rc.h"
#include "floatie.h"
#include "choppa.h"
#include "createmove.h"
#include "pt.h"
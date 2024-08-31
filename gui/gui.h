#pragma once

#include <vector>
#include <memory>

class Frame;

namespace render
{
	extern HWND handle;
}

namespace gui
{
	std::vector<Frame> frames;

	void AddFrame(const Frame& frame)
	{
		if (render::handle == NULL)
			MessageBoxA(NULL, "render never initialized", "render never initialized", NULL);
		else
			frames.emplace_back(frame);
	}
}

#include "../sdk.h"

#include "util.h"
#include "draw.h"
#include "external.h"

#include "elements/base.h"
#include "elements/child.h"
#include "elements/frame.h"
#include "elements/checkbox.h"

#include "logic.h"
#include "render.h"
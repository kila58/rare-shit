#pragma once

#include "gui.h"

template <typename T>
struct reversion_wrapper { T& iterable; };

template <typename T>
auto begin(reversion_wrapper<T> w) { return std::rbegin(w.iterable); }

template <typename T>
auto end(reversion_wrapper<T> w) { return std::rend(w.iterable); }

template <typename T>
reversion_wrapper<T> reverse(T&& iterable) { return{ iterable }; }

namespace logic
{
	void SetDragging(bool dragging)
	{
		std::vector<std::reference_wrapper<Frame>> frames;

		for (auto& frame : reverse(gui::frames))
		{
			if (util::IsMouseWithin(frame.x, frame.y, frame.w, DRAGBOUNDS_HEIGHT))
			{
				if (!dragging)
					frame.SetDragging(false);

				frames.emplace_back(frame);
			}
		}

		if (!frames.empty() && dragging)
		{
			Frame top = frames[0].get();
			top.SetDragging(dragging);

			auto it = std::find(gui::frames.begin(), gui::frames.end(), top);
			gui::frames.erase(it);

			gui::frames.push_back(top);
		}
	}

	void SetVisible(bool visible)
	{
		for (auto& frame : gui::frames)
		{
			frame.SetVisible(visible);
		}
	}

	void HandleClick()
	{
		Frame top = gui::frames[0];

		for (auto& pointer : top.GetChildren())
		{
			Child& child = pointer.get();

			if (util::IsMouseWithin(child.x, child.y, child.w, child.h))
				child.OnClick();
		}
	}
}
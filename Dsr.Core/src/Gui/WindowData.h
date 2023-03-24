#pragma once

#include "Viewport.h"

namespace dsr
{
	namespace gui
	{
		struct WindowData
		{
			std::string Title;
			int Width, Height;
			Viewport View;

			WindowData()
			{
				Title = "Window";
				Width = 1024;
				Height = 768;

				View.X = View.Y = 0;
				View.Width = 1024;
				View.Height = 768;
			}
		};
	}
}

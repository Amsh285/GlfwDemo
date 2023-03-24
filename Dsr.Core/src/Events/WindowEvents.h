#pragma once

#include "Event.h"
#include "Gui/WindowData.h"

namespace dsr
{
	namespace events
	{
		class WindowResizeEvent : public Event
		{
		public:
			inline int GetNewWidth() const { return m_newWidth; }
			inline int GetNewHeight() const { return m_newHeight; }

			WindowResizeEvent(int newWidth, int newHeight)
				: m_newWidth(newWidth), m_newHeight(newHeight)
			{}

		private:
			int m_newWidth, m_newHeight;
		};

		class WindowUpdateEvent : public Event
		{
		public:
			dsr::gui::WindowData GetWindowData() const { return m_data; }

			WindowUpdateEvent(const dsr::gui::WindowData& data)
				: m_data(data)
			{}
		private:
			dsr::gui::WindowData m_data;
		};
	}
}

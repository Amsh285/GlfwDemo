#pragma once

#include "Event.h"

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
	}
}

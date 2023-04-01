#pragma once

#include "Events/WindowEvents.h"
#include "Events/EventReceiver.h"
#include "LogManager.h"
#include "RenderContextRegister.h"
#include "Gui/Viewport.h"

namespace dsr
{
	namespace render
	{
		class Renderer : public dsr::events::EventReceiver
		{
		public:
			Renderer(const std::shared_ptr<RenderContextRegister>& renderContextRegister);

			void Update(dsr::events::WindowUpdateEvent& event);
		private:
			std::shared_ptr<RenderContextRegister> m_RenderContextRegister;
			std::shared_ptr<spdlog::logger> m_Logger = dsr::LogManager::GetLogger("dsr::render::Renderer");

			//Todo (next branch): Use Cameras...
			glm::mat4 m_ViewMatrix;
			glm::mat4 m_ProjectionMatrix;
		};
	}
}

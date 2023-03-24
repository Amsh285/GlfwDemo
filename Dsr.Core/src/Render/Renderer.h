#pragma once

#include "Events/WindowEvents.h"
#include "Events/EventReceiver.h"
#include "LogManager.h"
#include "RenderContext.h"
#include "Gui/Viewport.h"

namespace dsr
{
	namespace render
	{
		class Renderer : public dsr::events::EventReceiver
		{
		public:
			Renderer();

			void AddRenderContext(const RenderContext& renderContext);
			void Update(dsr::events::WindowUpdateEvent& event);
		private:
			std::vector<RenderContext> m_RenderContexts;
			std::shared_ptr<spdlog::logger> m_Logger = dsr::LogManager::GetLogger("dsr::render::Renderer");

			//Todo (next branch): Use Cameras...
			glm::mat4 m_ViewMatrix;
			glm::mat4 m_ProjectionMatrix;
		};
	}
}

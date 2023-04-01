#pragma once

#include "IdGenerator/IdGenerator.h"
#include "LogManager.h"
#include "RenderContext.h"

namespace dsr
{
	namespace render
	{
		class RenderContextRegister
		{
		public:
			const std::map<int, RenderContext>& GetContexts() const { return m_Contexts; }

			void Register(
				const std::shared_ptr<actors::Actor>& actor,
				const std::shared_ptr<VaoAggregate>& vao
			);

			void RegisterAt(
				const int& registerId,
				const std::shared_ptr<actors::Actor>& actor);

		private:
			static const std::string RegisterIdField;

			std::vector<int> m_RegisteredActors;
			std::map<int,RenderContext> m_Contexts;

			std::shared_ptr<spdlog::logger> m_Logger = LogManager::GetLogger("dsr::render::RenderContextRegister");

			bool IsRegistered(int actorId);
		};
	}
}

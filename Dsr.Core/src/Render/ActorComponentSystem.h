#pragma once

#include "Actors/Actor.h"
#include "RenderContext.h"

namespace dsr
{
	namespace render
	{
		class ActorComponentSystem
		{
		public:

		private:
			std::vector<render::RenderContext> m_RenderContexts;
		};
	}
}

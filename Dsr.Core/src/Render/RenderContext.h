#pragma once

#include "Actors/Actor.h"
#include "Shading/ShaderProgram.h"
#include "VaoAggregate.h"

namespace dsr
{
	namespace render
	{
		class RenderContext
		{
		public:
			std::vector<std::shared_ptr<actors::Actor>> GetData() const { return m_Data; }
			std::shared_ptr<VaoAggregate> GetVao() const { return m_Vao; }

			RenderContext() = default;

			RenderContext(
				std::shared_ptr<VaoAggregate> vao
			);

			RenderContext(
				std::shared_ptr<VaoAggregate> vao,
				std::vector<std::shared_ptr<actors::Actor>> data
			);

		private:
			std::vector<std::shared_ptr<actors::Actor>> m_Data;
			std::shared_ptr<VaoAggregate> m_Vao;
		};
	}
}

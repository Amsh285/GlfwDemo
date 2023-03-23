#pragma once

#include "Actors/Transform.h"
#include "ShaderProgram.h"
#include "VaoAggregate.h"

namespace dsr
{
	namespace render
	{
		class RenderContext
		{
		public:
			RenderContext(
				glm::mat4 modelMatrix,
				std::shared_ptr<VaoAggregate> vao,
				std::shared_ptr<ShaderProgram> shaderProgram
			);

			RenderContext(
				glm::mat4 modelMatrix,
				std::shared_ptr<VaoAggregate> vao,
				std::shared_ptr<ShaderProgram> shaderProgram,
				std::vector<dsr::actors::Transform> transforms
			);

		private:
			glm::mat4 m_ModelMatrix;
			std::vector<dsr::actors::Transform> m_Transforms;
			std::shared_ptr<VaoAggregate> m_Vao;
			std::shared_ptr<ShaderProgram> m_ShaderProgram;
		};
	}
}

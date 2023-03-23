#include "dsrpch.h"
#include "RenderContext.h"

namespace dsr
{
	namespace render
	{
		RenderContext::RenderContext(
			glm::mat4 modelMatrix,
			std::shared_ptr<VaoAggregate> vao,
			std::shared_ptr<ShaderProgram> shaderProgram
		)
			: m_ModelMatrix(modelMatrix)
			, m_Vao(vao)
			, m_ShaderProgram(shaderProgram)
		{
		}

		RenderContext::RenderContext(
			glm::mat4 modelMatrix,
			std::shared_ptr<VaoAggregate> vao,
			std::shared_ptr<ShaderProgram> shaderProgram,
			std::vector<dsr::actors::Transform> transforms
		)
			: m_ModelMatrix(modelMatrix)
			, m_Vao(vao)
			, m_ShaderProgram(shaderProgram)
			, m_Transforms(transforms)
		{
		}
	}
}

#include "dsrpch.h"
#include "RenderContext.h"

namespace dsr
{
	namespace render
	{
		RenderContext::RenderContext(
			const int& actorId,
			std::shared_ptr<VaoAggregate> vao,
			std::shared_ptr<dsr::shading::ShaderProgram> shaderProgram
		)
			: m_ActorId(actorId),
			m_Vao(vao),
			m_ShaderProgram(shaderProgram)
		{
		}

		RenderContext::RenderContext(
			const int& actorId,
			std::shared_ptr<VaoAggregate> vao,
			std::shared_ptr<dsr::shading::ShaderProgram> shaderProgram,
			std::vector<RenderData> data
		)
			: m_ActorId(actorId),
			m_Data(data),
			m_Vao(vao),
			m_ShaderProgram(shaderProgram)
		{
		}
	}
}

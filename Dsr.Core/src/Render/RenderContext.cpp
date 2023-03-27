#include "dsrpch.h"
#include "RenderContext.h"

namespace dsr
{
	namespace render
	{
		RenderContext::RenderContext(
			const int& actorId,
			const actors::ActorType& actorType,
			std::shared_ptr<VaoAggregate> vao,
			std::shared_ptr<dsr::shading::ShaderProgram> shaderProgram
		)
			: m_SourceActorId(actorId),
			m_ActorType(actorType),
			m_Vao(vao),
			m_ShaderProgram(shaderProgram)
		{
		}

		RenderContext::RenderContext(
			const int& actorId,
			const actors::ActorType& actorType,
			std::shared_ptr<VaoAggregate> vao,
			std::shared_ptr<dsr::shading::ShaderProgram> shaderProgram,
			std::vector<RenderData> data
		)
			: m_SourceActorId(actorId),
			m_ActorType(actorType),
			m_Data(data),
			m_Vao(vao),
			m_ShaderProgram(shaderProgram)
		{
		}
	}
}

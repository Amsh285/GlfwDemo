#pragma once

#include "Actors/Transform.h"
#include "Shading/ShaderProgram.h"
#include "VaoAggregate.h"

namespace dsr
{
	namespace render
	{
		struct RenderData
		{
			glm::mat4 ModelMatrix;
			int InstanceId;
		};

		class RenderContext
		{
		public:
			int GetActorId() const { return m_ActorId; }
			std::vector<RenderData> GetData() const { return m_Data; }
			std::shared_ptr<VaoAggregate> GetVao() const { return m_Vao; }
			std::shared_ptr<dsr::shading::ShaderProgram> GetShaderProgram() const { return m_ShaderProgram; }

			RenderContext(
				const int& actorId,
				std::shared_ptr<VaoAggregate> vao,
				std::shared_ptr<dsr::shading::ShaderProgram> shaderProgram
			);

			RenderContext(
				const int& actorId,
				std::shared_ptr<VaoAggregate> vao,
				std::shared_ptr<dsr::shading::ShaderProgram> shaderProgram,
				std::vector<RenderData> data
			);

		private:
			int m_ActorId;
			std::vector<RenderData> m_Data;
			std::shared_ptr<VaoAggregate> m_Vao;
			std::shared_ptr<dsr::shading::ShaderProgram> m_ShaderProgram;
		};
	}
}

#include "dsrpch.h"
#include "Renderer.h"

namespace dsr
{
	namespace render
	{
		Renderer::Renderer()
		{
			// Todo (next branch): Use Cameras...
			// Just a test
			glm::mat4 view = glm::mat4(1.0f);
			m_ViewMatrix = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

			m_ProjectionMatrix = glm::mat4(1.0f);
		}

		void Renderer::AddRenderContext(const RenderContext& renderContext)
		{
			m_RenderContexts.push_back(renderContext);
		}

		void Renderer::Update(dsr::events::WindowUpdateEvent& event)
		{
			dsr::gui::Viewport viewPort = event.GetWindowData().View;

			// Todo (next branch): Use Cameras...
			// Just a test
			// Check if Widthf and Heightf are right, because they are floats and viewport is setup with ints.
			m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), viewPort.Width_f / viewPort.Height_f, 0.1f, 100.0f);


			// maybe make this private const members
			const std::string uniformModelName = "model";
			const std::string uniformViewName = "view";
			const std::string uniformProjectionName = "projection";

			for (dsr::render::RenderContext& renderContext : m_RenderContexts)
			{
				std::shared_ptr<dsr::shading::ShaderProgram> shader = renderContext.GetShaderProgram();
				shader->Use();

				for (dsr::render::RenderData& data : renderContext.GetData())
				{
					if (!shader->SetUniform(uniformModelName, data.ModelMatrix))
					{
						m_Logger->error(
							"Failed to set uniform-matrix: {0} for (ActorId: {1}, InstanceId: {2})",
							uniformModelName,
							renderContext.GetActorId(),
							data.InstanceId
						);
						break;
					}

					if (!shader->SetUniform(uniformViewName, m_ViewMatrix))
					{
						m_Logger->error(
							"Failed to set uniform-matrix: {0} for (ActorId: {1}, InstanceId: {2})",
							uniformViewName,
							renderContext.GetActorId(),
							data.InstanceId
						);
						break;
					}

					if (!shader->SetUniform(uniformProjectionName, m_ProjectionMatrix))
					{
						m_Logger->error(
							"Failed to set uniform-matrix: {0} for (ActorId: {1}, InstanceId: {2})",
							uniformProjectionName,
							renderContext.GetActorId(),
							data.InstanceId
						);
						break;
					}

					std::shared_ptr<dsr::VaoAggregate> vao = renderContext.GetVao();
					vao->Bind();
					glDrawElements(GL_TRIANGLES, vao->GetIndexCount(), GL_UNSIGNED_INT, 0);
					vao->Unbind();
				}
			}
		}
	}
}

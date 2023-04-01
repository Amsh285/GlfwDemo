#include "dsrpch.h"
#include "Renderer.h"

namespace dsr
{
	namespace render
	{
		Renderer::Renderer(const std::shared_ptr<RenderContextRegister>& renderContextRegister)
			: m_RenderContextRegister(renderContextRegister)
		{
			// Todo (next branch): Use Cameras...
			// Just a test
			glm::mat4 view = glm::mat4(1.0f);
			m_ViewMatrix = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

			m_ProjectionMatrix = glm::mat4(1.0f);
		}

		void Renderer::Update(dsr::events::WindowUpdateEvent& event)
		{
			dsr::gui::Viewport viewPort = event.GetWindowData().View;

			// Todo (next branch): Use Cameras...
			// Just a test
			// Check if Widthf and Heightf are right, because they are floats and viewport is setup with ints.
			// should be updated on window resize
			m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), viewPort.Width_f / viewPort.Height_f, 0.1f, 100.0f);


			// maybe make this private const members
			const std::string uniformModelName = "model";
			const std::string uniformViewName = "view";
			const std::string uniformProjectionName = "projection";

			for (const std::pair<int, RenderContext>& contextEntry : m_RenderContextRegister->GetContexts())
			{
				const RenderContext& renderContext = contextEntry.second;

				std::shared_ptr<VaoAggregate> vao = renderContext.GetVao();

				if (vao)
				{
					for (std::shared_ptr<actors::Actor> actor : renderContext.GetData())
					{
						std::shared_ptr<shading::ShaderProgram> shader = actor->GetShader();
						shader->Use();

						// TODO: try to refactor this break statements. Maybe we can still try to draw the actor even
						// if one of the uniforms failed to set.
						if (!shader->SetUniform(uniformModelName, actor->GetModelMatrix()))
						{
							m_Logger->warn(
								"Failed to set uniform-matrix: {0} for (ActorId: {1})",
								uniformModelName,
								actor->GetActorId()
							);
							break;
						}

						if (!shader->SetUniform(uniformViewName, m_ViewMatrix))
						{
							m_Logger->warn(
								"Failed to set uniform-matrix: {0} for (ActorId: {1})",
								uniformViewName,
								actor->GetActorId()
							);
							break;
						}

						if (!shader->SetUniform(uniformProjectionName, m_ProjectionMatrix))
						{
							m_Logger->warn(
								"Failed to set uniform-matrix: {0} for (ActorId: {1})",
								uniformProjectionName,
								actor->GetActorId()
							);
							break;
						}

						vao->Bind();
						glDrawElements(GL_TRIANGLES, vao->GetIndexCount(), GL_UNSIGNED_INT, 0);
						vao->Unbind();
					}
				}
				else
					m_Logger->warn("No Vao found for (RenderContext: {0})", contextEntry.first);
			}
		}
	}
}

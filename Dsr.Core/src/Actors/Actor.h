#pragma once

#include "ActorIdConstants.h"
#include "ActorType.h"
#include "IdGenerator/IdGenerator.h"
#include "Shading/ShaderProgram.h"
#include "Transform.h"

namespace dsr
{
	namespace actors
	{
		class Actor
		{
		public:
			inline int GetActorId() const { return m_ActorId; }

			inline int GetRegisterId() const { return m_RegisterId; }
			void SetRegisterId(const int& registerId) { m_RegisterId = registerId; }

			inline const std::string& GetName() const { return m_Name; }

			inline std::shared_ptr<shading::ShaderProgram> GetShader() { return m_Shader; }
			void SetShader(const std::shared_ptr<shading::ShaderProgram>& shader) { m_Shader = shader; }

			inline Transform& GetTransform() { return m_Transform; }

			inline glm::mat4 GetModelMatrix() const { return m_ModelMatrix; }

			Actor();
			Actor(const std::string& name);
			virtual ~Actor();

			virtual void UpdateModelMatrix();
			virtual ActorType GetActorType() const = 0;
		protected:
			int m_ActorId;
			int m_RegisterId;
			std::string m_Name;
			std::shared_ptr<shading::ShaderProgram> m_Shader;
			Transform m_Transform;
			glm::mat4 m_ModelMatrix;
		};
	}
}

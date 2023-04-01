#include "dsrpch.h"
#include "Actor.h"

namespace dsr
{
	namespace actors
	{
		Actor::Actor()
			: m_ActorId(dsr::idgen::NextId(ActorIdConstants::ActorIdField)),
			m_RegisterId(-1),
			m_ModelMatrix(glm::mat4(1.0f))
		{
			m_Name = "Actor_" + std::to_string(m_ActorId);
		}

		Actor::Actor(const std::string& name)
			: m_ActorId(dsr::idgen::NextId(ActorIdConstants::ActorIdField)),
			m_Name(name),
			m_RegisterId(-1),
			m_ModelMatrix(glm::mat4(1.0f))
		{
		}

		Actor::~Actor()
		{
		}

		void Actor::UpdateModelMatrix()
		{
			glm::mat4 model = glm::mat4(1.0f);

			glm::quat rotationX = glm::angleAxis(glm::radians(m_Transform.GetRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
			glm::quat rotationY = glm::angleAxis(glm::radians(m_Transform.GetRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::quat rotationZ = glm::angleAxis(glm::radians(m_Transform.GetRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
			
			// TODO: Check if this order works well
			glm::quat inplaceRotation = rotationX * rotationY * rotationZ;

			m_ModelMatrix =
				glm::scale(model, m_Transform.GetScale()) *
				glm::translate(model, m_Transform.GetPosition()) *
				glm::toMat4(inplaceRotation);
		}
	}
}

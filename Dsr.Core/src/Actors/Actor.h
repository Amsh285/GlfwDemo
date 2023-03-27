#pragma once

#include "ActorIdConstants.h"
#include "ActorType.h"
#include "IdGenerator/IdGenerator.h"
#include "Transform.h"

namespace dsr
{
	namespace actors
	{
		class Actor
		{
		public:
			inline int GetActorId() const { return m_ActorId; }
			inline int GetCopyOf() const { return m_CopyOf; }
			inline const std::string& GetName() const { return m_Name; }
			inline Transform& GetTransform() { return m_Transform; }
			inline const std::vector<std::shared_ptr<Actor>>& GetChildren() const { return m_Children; }

			virtual ActorType GetActorType() const = 0;

			Actor(const std::string& name);
			virtual ~Actor();
		protected:
			int m_ActorId;
			int m_CopyOf;
			std::string m_Name;
			Transform m_Transform;
			std::vector<std::shared_ptr<Actor>> m_Children;
		};
	}
}

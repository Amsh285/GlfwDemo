#pragma once

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
			inline Transform& GetTransform() { return m_Transform; }

			virtual std::string GetActorType() const = 0;

			Actor();
			virtual ~Actor();
		protected:
			Transform m_Transform;
			int m_ActorId;
		};
	}
}

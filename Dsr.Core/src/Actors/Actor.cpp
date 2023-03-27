#include "dsrpch.h"
#include "Actor.h"

namespace dsr
{
	namespace actors
	{
		Actor::Actor(const std::string& name)
			: m_ActorId(dsr::idgen::NextId(ActorIdConstants::ActorIdField)),
			m_Name(name),
			m_CopyOf(-1)
		{
		}

		Actor::~Actor()
		{
		}
	}
}

#include "dsrpch.h"
#include "Actor.h"

namespace dsr
{
	namespace actors
	{
		Actor::Actor()
			: m_ActorId(dsr::idgen::NextId(GetActorType()))
		{
		}

		Actor::~Actor()
		{
		}
	}
}

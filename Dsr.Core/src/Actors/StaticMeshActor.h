#pragma once

#include "Actor.h"

namespace dsr
{
	namespace actors
	{
		class StaticMeshActor : public Actor
		{
		public:
			virtual ActorType GetActorType() const override { return ActorType::StaticMesh; }
		};
	}
}

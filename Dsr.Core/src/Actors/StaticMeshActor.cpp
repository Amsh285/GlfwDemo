#include "dsrpch.h"
#include "StaticMeshActor.h"

namespace dsr
{
	namespace actors
	{
		ActorType StaticMeshActor::GetActorType() const
		{
			return ActorType::StaticMesh;
		}
	}
}
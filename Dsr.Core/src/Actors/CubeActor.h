#pragma once

#include "StaticMeshActor.h"
#include "VaoAggregate.h"

namespace dsr
{
	namespace actors
	{
		class CubeActor : public StaticMeshActor
		{
		public:
			std::shared_ptr<VaoAggregate> BuildCubeVaoAggregate() const;
		};
	}
}

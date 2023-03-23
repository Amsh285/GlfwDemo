#pragma once

#include "Actor.h"

namespace dsr
{
	namespace actors
	{
		class Quad : public Actor
		{
		public:
			virtual std::string GetActorType() const override;
		private:
		};
	}
}

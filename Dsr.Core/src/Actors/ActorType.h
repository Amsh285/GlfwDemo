#pragma once

#include "ActorTypeConstants.h"
#include "IdGenerator/IdGenerator.h"

namespace dsr
{
	namespace actors
	{
		class ActorType
		{
		public:
			static const ActorType StaticMesh;

			inline int GetId() const { return m_Id; }
			inline const std::string& GetName() const { return m_Name; }

			ActorType(const std::string& name, const int& id)
				: m_Id(id), m_Name(name)
			{
			}

		private:
			int m_Id;
			std::string m_Name;
		};
	}
}

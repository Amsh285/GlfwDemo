#include "dsrpch.h"
#include "IdGenerator.h"

namespace dsr
{
	namespace idgen
	{
		static std::map<std::string, int> m_IdMap;
		static std::mutex m_IdMapMutex;
		
		int NextId(const std::string& name)
		{
			std::lock_guard<std::mutex> lock(m_IdMapMutex);

			if (m_IdMap.find(name) == m_IdMap.end())
				return m_IdMap[name] = 1;
			else
				return ++m_IdMap[name];
		}
	}
}

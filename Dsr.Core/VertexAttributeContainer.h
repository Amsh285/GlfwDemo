#pragma once

#include <vector>

#include "glad/glad.h"
#include "VertexAttribute.h"

namespace dsr
{
	class VertexAttributeContainer
	{
	public:
		std::size_t GetStrideElementCount() const { return m_strideElementCount; };

		void Append(const std::size_t& size, bool normalize = false);

		void BindAttributesf() const;
	private:
		std::vector<VertexAttribute> m_attributes;
		unsigned int m_nextLocation = 0;
		std::size_t m_strideElementCount = 0;
	};
}

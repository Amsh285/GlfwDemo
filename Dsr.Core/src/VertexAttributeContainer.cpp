
#include "dsrpch.h"
#include "VertexAttributeContainer.h"

namespace dsr
{
	void VertexAttributeContainer::Append(const std::size_t& size, bool normalize)
	{
		m_attributes.push_back(VertexAttribute(m_nextLocation++, size, normalize));
		m_strideElementCount += size;
	}

	void VertexAttributeContainer::BindAttributesf() const
	{
		std::size_t offset = 0;

		for (auto it = m_attributes.begin(); it != m_attributes.end(); ++it)
		{
			glVertexAttribPointer(
				it->Location,
				it->Size,
				GL_FLOAT,
				it->Normalize,
				m_strideElementCount * sizeof(float),
				(void*)(offset * sizeof(float))
			);

			glEnableVertexAttribArray(it->Location);

			offset += it->Size;
		}
	}
}

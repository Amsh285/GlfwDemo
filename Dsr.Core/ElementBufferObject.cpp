#include "ElementBufferObject.h"

namespace dsr
{
	std::shared_ptr<ElementBufferObject> ElementBufferObject::GenerateGL()
	{
		unsigned int ebo;
		glGenBuffers(1, &ebo);

		return std::shared_ptr<ElementBufferObject>(new ElementBufferObject(ebo));
	}

	void ElementBufferObject::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	}

	void ElementBufferObject::SetBufferData(const std::vector<unsigned int>& indices, bool staticDraw)
	{
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			sizeof(unsigned int) * indices.size(),
			indices.data(),
			staticDraw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
	}

	void ElementBufferObject::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	ElementBufferObject::~ElementBufferObject()
	{
		glDeleteBuffers(1, &m_ebo);
	}
}

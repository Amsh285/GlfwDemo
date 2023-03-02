#include "VertexArrayObject.h"

namespace dsr
{
	std::shared_ptr<VertexArrayObject> VertexArrayObject::GenerateGL()
	{
		unsigned int vao;
		glGenVertexArrays(1, &vao);

		return std::shared_ptr<VertexArrayObject>(new VertexArrayObject(vao));
	}

	void VertexArrayObject::Bind()
	{
		glBindVertexArray(m_vao);
	}

	void VertexArrayObject::Unbind()
	{
		glBindVertexArray(0);
	}
}

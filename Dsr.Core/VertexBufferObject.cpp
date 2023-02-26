#include "VertexBufferObject.h"

namespace dsr
{
	std::shared_ptr<VertexBufferObject> VertexBufferObject::GenrateGl()
	{
		unsigned int vbo;
		glGenBuffers(1, &vbo);

		return std::shared_ptr<VertexBufferObject>(new VertexBufferObject(vbo));
	}
	void VertexBufferObject::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	}

	void VertexBufferObject::SetStaticDraw(const std::vector<float>& data)
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);
	}

	void VertexBufferObject::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

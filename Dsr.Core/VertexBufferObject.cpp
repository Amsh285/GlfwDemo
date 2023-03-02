#include "VertexBufferObject.h"

namespace dsr
{
	std::shared_ptr<VertexBufferObject> VertexBufferObject::GenrateGl()
	{
		unsigned int vbo;
		glGenBuffers(1, &vbo);

		return std::shared_ptr<VertexBufferObject>(new VertexBufferObject(vbo));
	}
	void VertexBufferObject::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	}

	void VertexBufferObject::SetBufferData(const std::vector<float>& data, bool staticDraw) const
	{
		glBufferData(
			GL_ARRAY_BUFFER,
			sizeof(float) * data.size(),
			data.data(),
			staticDraw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

		//later: https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferSubData.xhtml
	}

	void VertexBufferObject::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

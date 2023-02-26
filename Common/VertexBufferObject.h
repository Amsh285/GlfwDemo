#pragma once

#include <memory>
#include <vector>

#include "glad/glad.h"

namespace dsr
{
	class VertexBufferObject
	{
	public:
		static std::shared_ptr<VertexBufferObject> GenrateGl();

		VertexBufferObject() = delete;
		

		void Bind();
		void SetStaticDraw(const std::vector<float>& data);
		void Unbind();
	private:
		VertexBufferObject(unsigned int vbo) : m_vbo(vbo) {};
		unsigned int m_vbo;
	};
}

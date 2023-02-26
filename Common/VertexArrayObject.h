#pragma once

#include <memory>

#include "glad/glad.h"

namespace dsr
{
	class VertexArrayObject
	{
	public:
		static std::shared_ptr<VertexArrayObject> GenerateGL();

		VertexArrayObject() = delete;

		void Bind();
		void Unbind();
	private:
		VertexArrayObject(const unsigned int& vao) : m_vao(vao) {};
		unsigned int m_vao;
	};
}

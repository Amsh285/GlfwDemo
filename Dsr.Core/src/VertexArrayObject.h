#pragma once

#include <memory>

#include "glad/glad.h"

namespace dsr
{
	class VertexArrayObject
	{
	public:
		static std::shared_ptr<VertexArrayObject> GenerateGL();

		void Bind();
		void Unbind();

		VertexArrayObject() = delete;
		VertexArrayObject(const VertexArrayObject& other) = delete;
		VertexArrayObject& operator=(const VertexArrayObject& other) = delete;

		~VertexArrayObject();
	private:
		VertexArrayObject(const unsigned int& vao) : m_vao(vao) {};
		unsigned int m_vao;
	};
}

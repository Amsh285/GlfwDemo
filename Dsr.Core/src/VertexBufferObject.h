#pragma once

#include "glad/glad.h"

namespace dsr
{
	class VertexBufferObject
	{
	public:
		static std::shared_ptr<VertexBufferObject> GenrateGl();

		void Bind() const;
		void SetBufferData(const std::vector<float>& data, bool staticDraw = true) const;
		void Unbind() const;

		VertexBufferObject() = delete;
		VertexBufferObject(const VertexBufferObject& other) = delete;
		VertexBufferObject& operator=(const VertexBufferObject& other) = delete;

		~VertexBufferObject();
	private:
		VertexBufferObject(const unsigned int& vbo) : m_vbo(vbo) {};
		unsigned int m_vbo;
	};
}

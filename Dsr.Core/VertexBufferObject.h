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
		

		void Bind() const;
		void SetBufferData(const std::vector<float>& data, bool staticDraw = true) const;
		void Unbind() const;
	private:
		VertexBufferObject(const unsigned int& vbo) : m_vbo(vbo) {};
		unsigned int m_vbo;
	};
}

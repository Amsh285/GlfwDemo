#pragma once

#include <memory>
#include <vector>

#include "glad/glad.h"

namespace dsr
{
	class ElementBufferObject
	{
	public:
		static std::shared_ptr<ElementBufferObject> GenerateGL();

		ElementBufferObject() = delete;

		void Bind();
		void SetBufferData(const std::vector<unsigned int>& indices, bool staticDraw = false);
		void Unbind();
	private:
		ElementBufferObject(const unsigned int& ebo) : m_ebo(ebo) {};
		unsigned int m_ebo;
	};
}

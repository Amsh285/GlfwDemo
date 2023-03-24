#pragma once

#include "glad/glad.h"

namespace dsr
{
	class ElementBufferObject
	{
	public:
		static std::shared_ptr<ElementBufferObject> GenerateGL();

		std::size_t GetIndexCount() const { return m_indexCount; }

		void Bind();
		void SetBufferData(const std::vector<unsigned int>& indices, bool staticDraw = false);
		void Unbind();

		ElementBufferObject() = delete;
		ElementBufferObject(const ElementBufferObject& other) = delete;
		ElementBufferObject& operator=(const ElementBufferObject& other) = delete;

		~ElementBufferObject();
	private:
		ElementBufferObject(const unsigned int& ebo) : m_ebo(ebo) {};
		std::size_t m_indexCount;
		unsigned int m_ebo;
	};
}

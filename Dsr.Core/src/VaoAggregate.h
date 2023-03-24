#pragma once

#include "ElementBufferObject.h"
#include "VertexArrayObject.h"
#include "VertexAttribute.h"
#include "VertexAttributeContainer.h"
#include "VertexBufferObject.h"

namespace dsr
{
	class VaoAggregate
	{
	public:
		static VaoAggregate Build(
			const std::vector<float>& buffer,
			const std::vector<unsigned int>& indices,
			const VertexAttributeContainer& attributes);

		std::size_t GetIndexCount() const { return m_ebo->GetIndexCount(); };

		void Bind() const { m_vao->Bind(); };
		void Unbind() const { m_vao->Unbind(); };

		VaoAggregate() = delete;
	private:
		VaoAggregate(
			const std::shared_ptr<VertexArrayObject>& vao,
			const std::shared_ptr< VertexBufferObject>& vbo,
			const std::shared_ptr<ElementBufferObject>& ebo)
			: m_vao(vao), m_vbo(vbo), m_ebo(ebo) {};

		std::shared_ptr<VertexArrayObject> m_vao;
		std::shared_ptr<VertexBufferObject> m_vbo;
		std::shared_ptr<ElementBufferObject> m_ebo;
	};
}

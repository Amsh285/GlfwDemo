#include "VaoAggregate.h"

namespace dsr
{
	VaoAggregate VaoAggregate::Build(const std::vector<float>& buffer, const std::vector<unsigned int>& indices, const VertexAttributeContainer& attributes)
	{
		std::shared_ptr<VertexArrayObject> vao = VertexArrayObject::GenerateGL();
		vao->Bind();

		std::shared_ptr<VertexBufferObject> vbo = VertexBufferObject::GenrateGl();
		vbo->Bind();
		vbo->SetBufferData(buffer);

		std::shared_ptr<ElementBufferObject> ebo = ElementBufferObject::GenerateGL();
		ebo->Bind();
		ebo->SetBufferData(indices);

		attributes.BindAttributesf();

		vao->Unbind();
		vbo->Unbind();
		ebo->Unbind();

		//Todo:: implement deleters
		return VaoAggregate(vao, vbo, ebo);
	}
}

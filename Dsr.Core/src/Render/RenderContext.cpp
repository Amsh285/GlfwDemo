#include "dsrpch.h"
#include "RenderContext.h"

namespace dsr
{
	namespace render
	{
		RenderContext::RenderContext(std::shared_ptr<VaoAggregate> vao)
			: m_Vao(vao)
		{
		}

		RenderContext::RenderContext(
			std::shared_ptr<VaoAggregate> vao,
			std::vector<std::shared_ptr<actors::Actor>> data
		)
			: m_Data(data),
			m_Vao(vao)
		{
		}
	}
}

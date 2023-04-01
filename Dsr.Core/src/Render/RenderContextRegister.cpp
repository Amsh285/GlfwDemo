#include "dsrpch.h"
#include "RenderContextRegister.h"

namespace dsr
{
	namespace render
	{
		const std::string RegisterIdField = "RenderContextRegisterId";

		void RenderContextRegister::Register(
			const std::shared_ptr<actors::Actor>& actor,
			const std::shared_ptr<VaoAggregate>& vao)
		{
			if (IsRegistered(actor->GetActorId()))
			{
				m_Logger->warn("Actor with id {0} is already registered", actor->GetActorId());
				return;
			}

			m_RegisteredActors.push_back(actor->GetActorId());
			int registerId = dsr::idgen::NextId(RegisterIdField);

			m_Contexts[registerId] = RenderContext(vao, { actor });
			actor->SetRegisterId(registerId);
		}

		void RenderContextRegister::RegisterAt(
			const int& registerId,
			const std::shared_ptr<actors::Actor>& actor)
		{
			if (IsRegistered(actor->GetActorId()))
			{
				m_Logger->warn("Actor with id {0} is already registered", actor->GetActorId());
				return;
			}

			if (m_Contexts.find(registerId) == m_Contexts.end())
			{
				m_Logger->warn("registerId {0} does not exist", registerId);
				return;
			}

			m_Contexts[registerId].GetData().push_back(actor);
			actor->SetRegisterId(registerId);
		}

		bool RenderContextRegister::IsRegistered(int actorId)
		{
			return std::find(
				m_RegisteredActors.begin(),
				m_RegisteredActors.end(),
				actorId) != m_RegisteredActors.end();
		}
	}
}
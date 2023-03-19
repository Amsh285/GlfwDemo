#pragma once

#include <assert.h>
#include <memory>
#include <vector>

#include "Event.h"
#include "EventReceiver.h"

namespace dsr
{
	namespace events
	{
		template<class TObject, class TEvent>
		class EventHandler
		{
		public:
			using EventDelegate = void(TObject::*)(TEvent&);

			inline std::size_t GetSize() const { return m_callbacks.size(); }

			template<class TSubType>
			void Hook(const std::shared_ptr<TObject>& instance, void((TSubType::* func)(TEvent&)))
			{
				assert(instance);
				assert(func);

				auto del = static_cast<EventDelegate>(func);
				m_callbacks.push_back(std::make_pair(std::weak_ptr<TObject>(instance), del));
			}

			void Hook(const std::shared_ptr<TObject>& instance, EventDelegate func)
			{
				assert(instance);
				assert(func);

				m_callbacks.push_back(std::make_pair(std::weak_ptr<TObject>(instance), func));
			}

			template<class TSubType>
			void UnHook(const std::shared_ptr<TObject>& instance, void((TSubType::* func)(TEvent&)))
			{
				assert(instance);
				assert(func);

				auto del = static_cast<EventDelegate>(func);
				auto pred = [&](const std::pair<std::weak_ptr<TObject>, EventDelegate>& p) {
					return p.first.lock() == instance && p.second == del;
				};

				auto it = std::find_if(m_callbacks.begin(), m_callbacks.end(), pred);

				if (it != m_callbacks.end())
					m_callbacks.erase(it);
			}

			void UnHook(const std::shared_ptr<TObject>& instance, EventDelegate func)
			{
				assert(instance);
				assert(func);

				auto pred = [&](const std::pair<std::weak_ptr<TObject>, EventDelegate>& p) {
					return p.first.lock() == instance && p.second == func;
				};

				auto it = std::find_if(m_callbacks.begin(), m_callbacks.end(), pred);

				if (it != m_callbacks.end())
					m_callbacks.erase(it);
			}

			void UnHookAll(const std::shared_ptr<TObject>& instance)
			{
				assert(instance);

				auto pred = [&](const std::pair<std::weak_ptr<TObject>, EventDelegate>& p) {
					return p.first.lock() == instance;
				};

				m_callbacks.erase(
					std::remove_if(
						m_callbacks.begin(),
						m_callbacks.end(),
						pred),
					m_callbacks.end()
				);
			}

			void Cleanup()
			{
				auto pred = [&](const std::pair<std::weak_ptr<TObject>, EventDelegate>& p) {
					return p.first.expired();
				};

				m_callbacks.erase(
					std::remove_if(
						m_callbacks.begin(),
						m_callbacks.end(),
						pred),
					m_callbacks.end()
				);
			}

			void ClearCallbacks()
			{
				m_callbacks.clear();
			}

			void operator()(TEvent& e) const
			{
				for (const std::pair<std::weak_ptr<TObject>, EventDelegate>& callback : m_callbacks)
				{
					std::shared_ptr<TObject> ptr = callback.first.lock();

					if (ptr)
						(ptr.get()->*(callback.second))(e);
				}
			}

		private:
			std::vector<std::pair<std::weak_ptr<TObject>, EventDelegate>> m_callbacks;
		};
	}
}

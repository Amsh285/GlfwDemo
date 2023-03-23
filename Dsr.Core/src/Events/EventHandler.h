#pragma once

#include "Event.h"
#include "EventReceiver.h"

namespace dsr
{
	namespace events
	{
		/// <summary>
		/// Allows registration of multiple member function that will be raised when the event is fired.
		/// Functions can be registered with a shared pointer or a raw pointer.
		/// For each normally hooked function a weak pointer to the object is stored. If the object is destroyed the function will not be executed.
		/// For each unsafe hooked function a raw pointer to the object is stored. Beware that unsafed hooked pointers, cannot keep track of their
		/// Lifetime, therefore raising the EventHandler when the referenced object is deleted, leads to undefined behaviour.
		/// This can be prevented by either using the normal hooking mechanism or by manually unhooking the function before the object is destroyed.
		/// Unsafe hooking was added for convenience purposes, when the object cannot be managed by a shared pointer.
		/// </summary>
		/// <typeparam name="TEvent">The type of the Event that will be used as Argument for the member functions calls.</typeparam>
		/// <typeparam name="TObject">The Type of the class or struct implementing the registered member functions.</typeparam>
		template<class TObject, class TEvent>
		class EventHandler
		{
		public:
			using EventDelegate = void(TObject::*)(TEvent&);

			inline std::size_t GetSize() const { return m_callbacks.size() + m_unsafe_callbacks.size(); }

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
			void HookUnsafe(TObject* ptr, void((TSubType::* func)(TEvent&)))
			{
				assert(ptr);
				assert(func);
				auto del = static_cast<EventDelegate>(func);
				m_unsafe_callbacks.push_back(std::make_pair(ptr, del));
			}

			void HookUnsafe(TObject* ptr, EventDelegate func)
			{
				assert(ptr);
				assert(func);

				m_unsafe_callbacks.push_back(std::make_pair(ptr, func));
			}

			template<class TSubType>
			void UnHook(const std::shared_ptr<TObject>& instance, void((TSubType::* func)(TEvent&)))
			{
				assert(instance);
				assert(func);

				auto del = static_cast<EventDelegate>(func);
				UnHook(instance, del);
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

			template<class TSubType>
			void UnhookUnsafe(TObject* ptr, void((TSubType::* func)(TEvent&)))
			{
				assert(ptr);
				assert(func);

				auto del = static_cast<EventDelegate>(func);
				UnhookUnsafe(ptr, del);
			}

			void UnhookUnsafe(TObject* ptr, EventDelegate func)
			{
				assert(ptr);
				assert(func);

				auto pred = [&](const std::pair<TObject*, EventDelegate>& p) {
					return p.first == ptr && p.second == func;
				};

				auto it = std::find_if(m_unsafe_callbacks.begin(), m_unsafe_callbacks.end(), pred);
				if (it != m_unsafe_callbacks.end())
					m_unsafe_callbacks.erase(it);
			}

			void UnhookAllUnsafe(TObject* ptr)
			{
				assert(ptr);

				auto pred = [&](const std::pair<TObject*, EventDelegate>& p) {
					return p.first == ptr;
				};

				m_unsafe_callbacks.erase(
					std::remove_if(
						m_unsafe_callbacks.begin(),
						m_unsafe_callbacks.end(),
						pred),
					m_unsafe_callbacks.end()
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
				m_unsafe_callbacks.clear();
			}

			void operator()(TEvent& e) const
			{
				for (const std::pair<std::weak_ptr<TObject>, EventDelegate>& callback : m_callbacks)
				{
					std::shared_ptr<TObject> ptr = callback.first.lock();

					if (ptr)
						(ptr.get()->*(callback.second))(e);
				}

				for (const std::pair<TObject*, EventDelegate>& callback : m_unsafe_callbacks)
				{
					(callback.first->*(callback.second))(e);
				}
			}

		private:
			std::vector<std::pair<std::weak_ptr<TObject>, EventDelegate>> m_callbacks;
			std::vector<std::pair<TObject*, EventDelegate>> m_unsafe_callbacks;
		};
	}
}

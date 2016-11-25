#pragma once

#ifndef EVENT_HPP_
#define EVENT_HPP_

#include <string>
#include <functional>
#include <map>
#include "SaltyEngine/Debug.hpp"

namespace SaltyEngine
{
	namespace GUI
	{
		typedef std::function<void()> EventDelegate;
		typedef std::map<std::string, EventDelegate> EventList;
		class Event
		{
		public:
			void Invoke(const std::string &name);
			void AddListener(const std::string &name, EventDelegate func); //	Add a non persistent listener to the UnityEvent.
			void InvokeAll() const; //	Invoke all registered callbacks(runtime and persistent).
			void RemoveListener(const std::string &name); // Remove a listener from the Event.
			size_t GetEventCount() const; //	Get the number of registered listeners.
			const std::string  GetMethodName(size_t index) const;//	Get the target method name of the listener at index index.
			void RemoveAllListeners(); //	Remove all listeners from the event.
			void SetListener(const std::string &name, EventDelegate func); // Modify the execution state of a persistent listener.

		private:
			EventList m_events;
		};
	}
}

#endif // !EVENT_HPP_
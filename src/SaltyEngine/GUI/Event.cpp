#include "SaltyEngine/GUI/Event.hpp"


namespace SaltyEngine
{
	namespace GUI
	{
		static const std::string none = "None";
		void Event::Invoke(const std::string & name)
		{
#if DEBUG
			Debug::PrintInfo("Call " + name + " function.")
#endif
			m_events[name]();
#if DEBUG
			Debug::PrintSuccess("Function " + name + " has been called successfully.")
#endif
		}
		void Event::AddListener(const std::string & name, EventDelegate func)
		{
			if (m_events.find(name) != m_events.end())
				m_events[name] = func;
			else
				Debug::PrintWarning(name + " is already set, use SetListener instead.");
		}
		void Event::InvokeAll() const
		{
			for (EventList::const_iterator it = m_events.begin(); it != m_events.end(); ++it)
			{
#if DEBUG
				Debug::PrintInfo("Call " + (*it).first + " function.")
#endif
					(*it).second();
#if DEBUG
				Debug::PrintSuccess("Function " + (*it).first() + " has been called successfully.")
#endif
			}
		}

		void Event::RemoveListener(const std::string & name)
		{
			m_events.erase(name);
		}

		size_t Event::GetEventCount(void) const
		{
			return m_events.size();
		}

		const std::string &Event::GetMethodName(size_t index) const
		{
			size_t i = 0;
			for (EventList::const_iterator it = m_events.begin(); it != m_events.end(); ++it)
			{
				if (i == index)
					return ((*it).first);
				++i;
			}
			return (none);
		}

		void Event::RemoveAllListeners()
		{
			m_events.clear();
		}

		void Event::SetListener(const std::string & name, EventDelegate func)
		{
			m_events[name] = func;
		}
	}
}
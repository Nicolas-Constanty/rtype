#include "SaltyEngine/SaltyBehavior.hpp"

namespace SaltyEngine
{
	SaltyBehavior::SaltyBehavior(const std::string &name)
	{
		m_status = false;
		m_name = name;
		transform = new Transform();
	}


	SaltyBehavior::~SaltyBehavior()
	{
		delete transform;
	}

	const std::string & SaltyBehavior::GetName() const
	{
		return (m_name);
	}

	size_t SaltyBehavior::GetUID() const
	{
		return (m_uid);
	}
	bool SaltyBehavior::IsInit() const
	{
		return (m_status);
	}

	void SaltyBehavior::Init()
	{
		m_mutex.lock();
		m_status = true;
		m_mutex.unlock();
	}

	void SaltyBehavior::__Wait_For_Seconds(size_t time) const
	{
		std::this_thread::sleep_for(std::chrono::seconds(time));
	}

	void SaltyBehavior::__Wait_For_Milliseconds(size_t time) const
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(time));
	}

	void SaltyBehavior::__Wait_For_Microseconds(size_t time) const
	{
		std::this_thread::sleep_for(std::chrono::microseconds(time));
	}

	void SaltyBehavior::CallCoroutines() const
	{
		for (std::vector<coroutine::routine_t>::const_iterator it = m_coroutines.begin(); it != m_coroutines.end(); it++)
			coroutine::resume((*it));
	}
}

std::ostream & operator<<(std::ostream &os, SaltyEngine::SaltyBehavior &object)
{
	os << object.GetName() << "(" << object.GetUID() << ")" << std::endl;
	return (os);
}


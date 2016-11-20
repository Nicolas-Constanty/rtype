#include "SaltyEngine/SaltyBehaviour.hpp"

namespace SaltyEngine
{
	SaltyBehaviour::SaltyBehaviour(const std::string &name)
	{
		m_status = false;
		m_name = name;
		transform = new Transform();
	}


	SaltyBehaviour::~SaltyBehaviour()
	{
		delete transform;
	}

	const std::string & SaltyBehaviour::GetName() const
	{
		return (m_name);
	}

	size_t SaltyBehaviour::GetUID() const
	{
		return (m_uid);
	}
	bool SaltyBehaviour::IsInit() const
	{
		return (m_status);
	}

	void SaltyBehaviour::Init()
	{
		m_mutex.lock();
		m_status = true;
		m_mutex.unlock();
	}

	void SaltyBehaviour::__Wait_For_Seconds(size_t time) const
	{
		std::this_thread::sleep_for(std::chrono::seconds(time));
	}

	void SaltyBehaviour::__Wait_For_Milliseconds(size_t time) const
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(time));
	}

	void SaltyBehaviour::__Wait_For_Microseconds(size_t time) const
	{
		std::this_thread::sleep_for(std::chrono::microseconds(time));
	}

	void SaltyBehaviour::CallCoroutines() const
	{
		for (std::vector<coroutine::routine_t>::const_iterator it = m_coroutines.begin(); it != m_coroutines.end(); it++)
			coroutine::resume((*it));
	}
}

std::ostream & operator<<(std::ostream &os, SaltyEngine::SaltyBehaviour &object)
{
	os << object.GetName() << "(" << object.GetUID() << ")" << std::endl;
	return (os);
}


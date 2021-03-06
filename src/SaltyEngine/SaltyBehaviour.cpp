#include "SaltyEngine/SaltyBehaviour.hpp"

namespace SaltyEngine
{
	/**
	 * @fn	SaltyBehaviour::~SaltyBehaviour()
	 *
	 * @brief	Destructor.
	 *
	 */

	SaltyBehaviour::SaltyBehaviour(GameObject * const gameObj) : Behaviour("SaltyBehaviour", gameObj), m_status(false) {};

	SaltyBehaviour::SaltyBehaviour(const std::string & name, GameObject * const gameObj) : Behaviour(name, gameObj), m_status(false) {};

	SaltyBehaviour::~SaltyBehaviour()
	{
	}

	/**
	 * @fn	bool SaltyBehaviour::IsInit() const
	 *
	 * @brief	Query if this object is init.
	 *
	 * @return	True if init, false if not.
	 */

	bool SaltyBehaviour::IsInit() const
	{
		return (m_status);
	}

	/**
	 * @fn	void SaltyBehaviour::Init()
	 *
	 * @brief	Init this object.
	 */

	void SaltyBehaviour::Init()
	{
		m_mutex.lock();
		m_status = true;
		m_mutex.unlock();
	}

	/**
	 * @fn	void SaltyBehaviour::__Wait_For_Seconds(size_t time) const
	 *
	 * @brief	Wait for seconds.
	 *
	 * @param	time	The time.
	 */

	void SaltyBehaviour::__Wait_For_Seconds(size_t time)
	{
		std::this_thread::sleep_for(std::chrono::seconds(time));
	}

	/**
	 * @fn	void SaltyBehaviour::__Wait_For_Milliseconds(size_t time) const
	 *
	 * @brief	Wait for milliseconds.
	 *
	 * @param	time	The time.
	 */

	void SaltyBehaviour::__Wait_For_Milliseconds(size_t time)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(time));
	}

	/**
	 * @fn	void SaltyBehaviour::__Wait_For_Microseconds(size_t time) const
	 *
	 * @brief	Wait for microseconds.
	 *
	 * @param	time	The time.
	 */

	void SaltyBehaviour::__Wait_For_Microseconds(size_t time)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(time));
	}

	/**
	 * @fn	void SaltyBehaviour::CallCoroutines() const
	 *
	 * @brief	Call coroutines.
	 */

	void SaltyBehaviour::CallCoroutines() const
	{
		for (std::vector<coroutine::routine_t>::const_iterator it = m_coroutines.begin(); it != m_coroutines.end(); ++it)
			coroutine::resume((*it));
	}
}


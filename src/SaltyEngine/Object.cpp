#include "SaltyEngine/Object.hpp"
#include "SaltyEngine/Factory.hpp"
#include "Common/Debug.hpp"

namespace SaltyEngine
{
	/** @brief	Identifier for the object s. */
	 //int Object::s_id;

	/**
	* @fn	uid Object::GetInstanceID() const
	*
	* @brief	Gets instance identifier.
	*
	* @return	The instance identifier.
	*/

	std::atomic<uid> Object::s_id(0);

	uid Object::GetInstanceID(void) const
	{
		return m_uid;
	}

	/**
	* @fn	const std::string & Object::GetName() const
	*
	* @brief	Gets the name.
	*
	* @return	The name.
	*/

	const std::string & Object::GetName(void) const
	{
		return m_name;
	}

	void Object::SetName(std::string const &name)
	{
		m_name = name;
	}

	/**
	* @fn	void Object::Destroy(Object * original)
	*
	* @brief	Destroys the given original.
	*
	* @param [in,out]	original	If non-null, the original to destroy.
	*/

	void Object::Destroy(Object *original)
	{
		if (original)
			original->Destroy();
		else
			Debug::PrintWarning("Cannot destroy null Object");
	}

	void Object::Destroy() {

	}

    Object::Object(const std::string &name) : m_name(name) {
		m_uid = s_id;
		++s_id;
    }

    void Object::DontDestroyOnLoad(Object *target)
    {
		if (target)
			target->m_shouldBeDestroyedOnLoad = false;
    }
}

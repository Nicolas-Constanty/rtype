#include <SaltyEngine/Debug.hpp>
#include "SaltyEngine/Object.hpp"
#include "SaltyEngine/Factory.hpp"

namespace SaltyEngine
{
	/** @brief	Identifier for the object s. */
	std::atomic<int> Object::s_id;

	/**
	 * @fn	uid Object::GetInstanceID() const
	 *
	 * @brief	Gets instance identifier.
	 *
	 * @return	The instance identifier.
	 */

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
			Debug::PrintWarning("Cannot destrol null Object");
	}

	void Object::Destroy() {

	}
}

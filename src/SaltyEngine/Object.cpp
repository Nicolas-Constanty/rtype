#include "SaltyEngine/Object.hpp"

namespace SaltyEngine
{
	std::atomic<int> Object::s_id;


	uid Object::GetInstanceID() const
	{
		return m_uid;
	}

	const std::string & Object::GetName() const
	{
		return m_name;
	}

	void Object::Destroy(Object * original)
	{
		delete original;
	}

}
#include "SaltyEngine/Component.hpp"
#include "SaltyEngine/GameObject.hpp"

namespace SaltyEngine
{
	Component::Component(GameObject * const gameObj) : Object("Component"), tag(Tag[0]), gameObject(gameObj) {};

	Component::Component(const std::string & name, GameObject * const gameObj) : Object(name), tag(Tag[0]), gameObject(gameObj) {};

	bool Component::CompareTag(const std::string & tag) const
	{
		return gameObject->CompareTag(tag);
	}
}


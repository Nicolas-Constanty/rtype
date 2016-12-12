#include "SaltyEngine/Constants.hpp"
#include "SaltyEngine/Component.hpp"
#include "SaltyEngine/GameObject.hpp"

namespace SaltyEngine
{
	Component::Component(GameObject * const gameObj) : Object("Component"), tag(Layer::Tag::Untagged), gameObject(gameObj) {};

	Component::Component(const std::string & name, GameObject * const gameObj) : Object(name), tag(Layer::Tag::Untagged), gameObject(gameObj) {};

	bool Component::CompareTag(Layer::Tag tag) const
	{
		return gameObject->CompareTag(tag);
	}
}


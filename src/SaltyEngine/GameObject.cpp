#include "SaltyEngine/GameObject.hpp"

namespace SaltyEngine
{
	GameObject::GameObject(const std::string & name) : Object(name), transform(this) {};

	bool GameObject::CompareTag(const std::string & tag)
	{
		return (tag == m_tag);
	}
	void GameObject::SetActive(bool value)
	{
		m_activeSelf = value;
	}
}

std::ostream & operator<<(std::ostream & os, SaltyEngine::GameObject & object)
{
	os << object.GetName() << "(" << object.GetInstanceID() << ")" << std::endl;
	return (os);
}

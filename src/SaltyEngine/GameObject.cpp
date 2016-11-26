#include "SaltyEngine/GameObject.hpp"

namespace SaltyEngine
{
	GameObject::GameObject(const std::string & name) : Object(name), transform(this) {}

	bool GameObject::GetActiveSelf() const
	{
		return (m_activeSelf);
	}

	bool GameObject::CompareTag(const std::string & tag)
	{
		return (tag == m_tag);
	}
	void GameObject::SetActive(bool value)
	{
		m_activeSelf = value;
	}
}
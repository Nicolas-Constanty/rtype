#include "SaltyEngine/GameObject.hpp"

namespace SaltyEngine
{
	GameObject::GameObject(const std::string & name) : Object(name), transform(this), m_activeSelf(true), layer(0), scene(nullptr)
	{
		m_bcount = 0;
	}

	bool GameObject::GetActiveSelf() const
	{
		return (m_activeSelf);
	}

	bool GameObject::CompareTag(const std::string & tag) const
	{
		return (tag == m_tag);
	}
	void GameObject::SetActive(bool value)
	{
		m_activeSelf = value;
	}
}
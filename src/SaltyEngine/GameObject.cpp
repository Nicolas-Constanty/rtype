#include "SaltyEngine/Constants.hpp"
#include "SaltyEngine/GameObject.hpp"

namespace SaltyEngine
{
	GameObject::GameObject(const std::string & name, Layer::Tag tag) : Object(name), transform(this), m_activeSelf(true), layer(0), scene(nullptr), m_tag(tag)
	{
		m_bcount = 0;
	}

	bool GameObject::GetActiveSelf(void) const
	{
		return (m_activeSelf);
	}

	bool GameObject::CompareTag(Layer::Tag tag) const
	{
		return (tag == m_tag);
	}
	void GameObject::SetActive(bool value)
	{
		m_activeSelf = value;
	}

	Layer::Tag GameObject::GetTag(void) const
	{
		return m_tag;
	}
}
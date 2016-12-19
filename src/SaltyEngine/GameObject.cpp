#include "SaltyEngine/Constants.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/SaltyEngine.hpp"
#include "Common/Debug.hpp"

namespace SaltyEngine
{
	GameObject::GameObject(const std::string & name, Layer::Tag tag) : Object(name), transform(this), m_activeSelf(true), layer(0), scene(nullptr), m_tag(tag)
	{
		m_bcount = 0;
		scene = nullptr;
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

    void GameObject::Destroy() {
        Engine::Instance().GetCurrentScene()->Destroy(this);
    }

    void GameObject::__Destroy()
    {
        Engine::Instance().GetRenderer()->RemoveSpriteRenderer(this);
        m_behaviour.clear();
        m_components.clear();
    }

	std::unique_ptr<Object> GameObject::Clone() {
		return std::unique_ptr<Object>(new GameObject(GetName() + "(Clone)"));
	}

	std::unique_ptr<Object> GameObject::CloneMemberwise() {
		GameObject	*obj = new GameObject(GetName() + "(Clone)");

		obj->layer = layer;
		obj->m_tag = m_tag;
		obj->m_activeSelf = m_activeSelf;
		for (std::list<std::unique_ptr<Component>>::const_iterator it = m_components.begin(); it != m_components.end(); ++it) {
			obj->AddComponent((*it)->CloneComponent(obj));
		}
		return std::unique_ptr<Object>(obj);
	}

	std::list<GameObject *> GameObject::FindGameObjectsWithTag(Layer::Tag tag) {
		return Factory::Instance().FindAllByTag(tag);
	}

	GameObject *GameObject::FindGameObjectWithTag(Layer::Tag tag) {
		return Factory::Instance().FindByTag(tag);
	}

	GameObject *GameObject::Find(std::string const &name) {
		return Factory::Instance().Find(name);
	}

	const std::list<SaltyBehaviour *> &GameObject::GetSaltyBehaviour(void) const {
		return (m_behaviour);
	}

	Component *GameObject::AddComponent(Component *component) {
		m_components.push_back(std::unique_ptr<Component>(component));
		SaltyBehaviour *tmp = dynamic_cast<SaltyBehaviour *>(m_components.back().get());
		if (tmp)
		{
			++m_bcount;
			m_behaviour.push_back(tmp);
		}
        Engine::Instance().GetCurrentScene()->InitScene(m_components.back().get());
		return (dynamic_cast<Component *>(m_components.back().get()));
	}

	void GameObject::SetScene(AScene *sc) {
		scene = sc;
	}

	AScene *GameObject::GetScene() const {
		return scene;
	}
}
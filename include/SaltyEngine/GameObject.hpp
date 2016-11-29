#pragma once

#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include <list>
#include <vector>
#include <typeinfo>
#include "SaltyEngine/Transform.hpp"
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "Common/MakeUnique.hpp"

namespace SaltyEngine
{
	class Scene;
	class GameObject : public Object
	{
	public:
		// delete copy and move constructors and assign operators
		GameObject(GameObject const&) = delete;             // Copy construct
		GameObject(GameObject&&) = delete;                  // Move construct
		GameObject& operator=(GameObject const&) = delete;  // Copy assign
		GameObject& operator=(GameObject &&) = delete;      // Move assign
		explicit GameObject(const std::string &name);
		virtual ~GameObject() {};
	public:
		Transform transform;

	private:
		bool m_activeSelf;
		size_t layer;
		Scene *scene;
		std::string m_tag;
		std::list<std::unique_ptr<Component>> m_components;
		std::list<SaltyBehaviour *> m_behaviour;
		size_t						m_bcount;

	public:
		bool GetActiveSelf() const;

	public:
		template<class T>
		T *AddComponent()
		{
			m_components.push_back(Make_unique<T>(this));
			SaltyBehaviour *tmp = dynamic_cast<SaltyBehaviour *>(m_components.back().get());
			if (tmp)
			{
				++m_bcount;
				m_behaviour.push_back(tmp);
			}
			return (dynamic_cast<T *>(m_components.back().get()));
		}
		template<class T>
		T *AddComponent(const std::string &name)
		{
			m_components.push_back(Make_unique<T>(this));
			SaltyBehaviour *tmp = dynamic_cast<SaltyBehaviour *>(m_components.back().get());
			if (tmp)
			{
				++m_bcount;
				m_behaviour.push_back(tmp);
			}
			return (dynamic_cast<T *>(m_components.back().get()));
		}

		template<class T, class ... Args>
		T *AddComponent(Args &&... args)
		{
			m_components.push_back(Make_unique<T>(this, args...));
			SaltyBehaviour *tmp = dynamic_cast<SaltyBehaviour *>(m_components.back().get());
			if (tmp)
			{
				++m_bcount;
				m_behaviour.push_back(tmp);
			}
			return (dynamic_cast<T *>(m_components.back().get()));
		}
		bool CompareTag(const std::string &tag) const;
		template<class T>
		T GetComponent()
		{
			for (std::list<std::unique_ptr<Component>>::const_iterator it = m_components.begin(); it != m_components.end(); ++it)
			{
				if (typeid(*(*it).get()) == typeid(T))
				{
					return (*it);
				}
			}
			return (nullptr);
		}
		template<class T>
		T GetComponentInChildren()
		{
			std::vector<Transform *> children = transform.GetChildren();
			for (std::vector<Transform *>::const_iterator child = children.begin(); child != children.end(); ++child)
			{
				T comp = (*child)->gameObject->GetComponent<T>();
				if (comp != nullptr)
					return (comp);
			}
			return (nullptr);
		}

		template<class T>
		T GetComponentInParent()
		{
			return (transform.GetParent()->gameObject->GetComponent<T>());
		}

		template<class T>
		std::list<T> GetComponentsExactType()
		{
			std::list<T> list;
			for (std::list<std::unique_ptr<Component>>::const_iterator it = m_components.begin(); it != m_components.end(); ++it)
			{
				if (typeid(*(*it).get()) == typeid(T))
				{
					list.push_back(dynamic_cast<T>((*it).get()));
				}
			}
			return (list);
		}

		template<class T>
		std::list<T> GetComponents()
		{
			std::list<T> list;
			for (std::list<std::unique_ptr<Component>>::const_iterator it = m_components.begin(); it != m_components.end(); ++it)
			{
				SaltyBehaviour *tmp = dynamic_cast<T>((*it).get());
				if (tmp)
				{
					list.push_back(tmp);
				}
			}
			return (list);
		}

		const std::list<SaltyBehaviour *> &GetSaltyBehaviour() const
		{
			return (m_behaviour);
		}

		template<class T>
		std::list<T> GetComponentsInChildren()
		{
			std::list<T> list;
			std::vector<Transform *> children = transform.GetChildren();
			for (std::vector<Transform *>::const_iterator child = children.begin(); child != children.end(); ++child)
			{
                (*child)->gameObject->GetComponents<T>();
			}
			return (list);
		}

		template<class T>
		std::list<T> GetComponentsInParent()
		{
			return (transform.GetParent()->gameObject->GetComponents<T>());
		}
		void SetActive(bool value);
		friend std::ostream &operator<<(std::ostream &os, GameObject const &object) {
			os << object.GetName() << "(" << object.GetInstanceID() << ")" << std::endl;
			return (os);
		}

		public:
			virtual std::unique_ptr<Object> Clone() {
				return std::unique_ptr<Object>(new GameObject(GetName() + "(Clone)"));
			}
			virtual std::unique_ptr<Object> CloneMemberwise() {
				GameObject	*obj = new GameObject(GetName() + "(Clone)");

//				obj->transform = transform;
				obj->layer = layer;
				obj->m_activeSelf = m_activeSelf;
				obj->m_behaviour = m_behaviour;
				for (std::list<std::unique_ptr<Component>>::const_iterator it = m_components.begin(); it != m_components.end(); ++it) {
					obj->m_components.push_back(std::unique_ptr<Component>(it->get()));
				}
//				obj->scene = scene;
//				obj->m_bcount = m_bcount;
				obj->m_tag = m_tag;
				return std::unique_ptr<Object>(obj);
			}
	};
}

#endif // !GAMEOBJECT_HPP_

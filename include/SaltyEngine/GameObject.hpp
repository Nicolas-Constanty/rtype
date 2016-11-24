#pragma once

#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include <list>
#include <vector>
#include <typeinfo>
#include "SaltyEngine/Transform.hpp"
#include "SaltyEngine/SaltyBehaviour.hpp"

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
		GameObject(const std::string &name);
		virtual ~GameObject() {};
	public:
		Transform transform;

	private:
		bool m_activeSelf;
		size_t layer;
		Scene *scene;
		std::string m_tag;
		std::list<Component *> m_components;

	public:
		template<class T>
		T *AddComponent()
		{
			T *component = new T(this);
			m_components.push_back(component);
			return (component);
		}
		template<class T>
		T *AddComponent(const std::string &name)
		{
			T *component = new T(name, this);
			m_components.push_back(component);
			return (component);
		}
		bool CompareTag(const std::string &tag);
		template<class T>
		T GetComponent()
		{
			for (std::list<Component *>::const_iterator it = m_components.begin(); it != m_components.end(); it++)
			{
				if (typeid(**it) == typeid(T))
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
			for (std::vector<Transform *>::const_iterator child = children.begin(); child != children.end(); child++)
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
			for (std::list<Component *>::const_iterator it = m_components.begin(); it != m_components.end(); it++)
			{
				if (typeid(**it) == typeid(T))
				{
					list.push_back(dynamic_cast<T>(*it));
				}
			}
			return (list);
		}

		template<class T>
		std::list<T> GetComponents()
		{
			std::list<T> list;
			for (std::list<Component *>::const_iterator it = m_components.begin(); it != m_components.end(); it++)
			{
				SaltyBehaviour *tmp = dynamic_cast<T>(*it);
				if (tmp)
				{
					list.push_back(tmp);
				}
			}
			return (list);
		}

		template<class T>
		std::list<T> GetComponentsInChildren()
		{
			std::list<T> list;
			std::vector<Transform *> children = transform.GetChildren();
			for (std::vector<Transform *>::const_iterator child = children.begin(); child != children.end(); child++)
			{
                (*child)->gameObject->GetComponents<T>();
			}
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
				return std::unique_ptr<Object>(new GameObject(GetName() + "(Clone)"));
			}
	};
}

#endif // !GAMEOBJECT_HPP_

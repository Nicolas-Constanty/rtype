#pragma once

#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include <list>
#include <vector>
#include <typeinfo>
#include "SaltyEngine/Transform.hpp"
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "Common/Utils.hpp"
#include "SaltyEngine/Constants.hpp"
#include "SaltyEngine/AScene.hpp"
#include "SaltyEngine/SaltyEngine.hpp"

namespace SaltyEngine
{

	//class Scene;
	class GameObject : public Object
	{
		friend class AScene;
	public:
		// delete copy and move constructors and assign operators
		GameObject(GameObject const&) = delete;             // Copy construct
		GameObject(GameObject&&) = delete;                  // Move construct
		GameObject& operator=(GameObject const&) = delete;  // Copy assign
		GameObject& operator=(GameObject &&) = delete;      // Move assign
		explicit GameObject(const std::string &name, Layer::Tag tag = Layer::Tag::Untagged);
		virtual ~GameObject() {};
	public:
		Transform transform;

	private:
		bool 											m_activeSelf;
		size_t 											layer;
		AScene 											*scene;
		Layer::Tag 										m_tag;
		std::list<std::unique_ptr<Component>> 			m_components;
		std::list<SaltyBehaviour *>						m_behaviour;
		size_t											m_bcount;

	public:
		bool GetActiveSelf(void) const;
		void SetScene(AScene *);
		AScene *GetScene() const;

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
            if (::SaltyEngine::Engine::Instance().GetStatus() == EngineStatus::start)
                ::SaltyEngine::Engine::Instance().GetCurrentScene()->InitScene(m_components.back().get());
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
			if (::SaltyEngine::Engine::Instance().GetStatus() == EngineStatus::start)
				Engine::Instance().GetCurrentScene()->InitScene(m_components.back().get());
			return (dynamic_cast<T *>(m_components.back().get()));
		}

		Component *AddComponent(Component *component);

		bool CompareTag(Layer::Tag tag) const;
		template<class T>
		T *GetComponent()
		{
			for (std::list<std::unique_ptr<Component>>::const_iterator it = m_components.begin(); it != m_components.end(); ++it)
			{
				if (dynamic_cast<T*>((*it).get()))
				{
					return (T*)((*it).get());
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
		std::list<T*> GetComponents()
		{
			std::list<T*> list;
			for (std::list<std::unique_ptr<Component>>::const_iterator it = m_components.begin(); it != m_components.end(); ++it)
			{
				T *tmp = dynamic_cast<T*>((*it).get());
				if (tmp)
				{
					list.push_back(tmp);
				}
			}
			return (list);
		}

		const std::list<SaltyBehaviour *> &GetSaltyBehaviour(void) const;

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

        Layer::Tag GetTag(void) const;

		void SetActive(bool value);
		friend std::ostream &operator<<(std::ostream &os, GameObject const &object) {
			os << object.GetName() << "(" << object.GetInstanceID() << ")" << std::endl;
			return (os);
		}

		static GameObject *Find(std::string const& name);

		static GameObject *FindGameObjectWithTag(Layer::Tag tag);

        static std::vector<GameObject *> FindGameObjectsWithTag(Layer::Tag tag);

		public:
			virtual std::unique_ptr<Object> Clone();

			virtual std::unique_ptr<Object> CloneMemberwise();

		public:
            void Destroy() override;

		private:
			void __Destroy();
	};
}

#endif // !GAMEOBJECT_HPP_

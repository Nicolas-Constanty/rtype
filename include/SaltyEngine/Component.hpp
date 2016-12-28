#pragma once

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <list>
#include "SaltyEngine/Object.hpp"
#include "SaltyEngine/Constants.hpp"

namespace SaltyEngine
{
    class GameObject;
	class PREF_EXPORT Component : public Object
	{
	public:
		// delete copy and move constructors and assign operators
		Component(Component const&) = delete;             // Copy construct
		Component(Component&&) = delete;                  // Move construct
		Component& operator=(Component const&) = delete;  // Copy assign
		Component& operator=(Component &&) = delete;      // Move assign
		explicit Component(GameObject* const gameObj);
		Component(const std::string &name, GameObject* const gameObj);
		bool CompareTag(Layer::Tag tag) const;
		virtual ~Component() {};

	public:
		Layer::Tag tag;
		GameObject* const gameObject;

		virtual Component *CloneComponent(GameObject* const obj) {
			return new Component("Component", obj);
		}

//		template<class T>
//		T GetComponent()
//		{
//			return (gameObject->GetComponent<T>());
//		}
//
//		template<class T>
//		T GetComponentInChildren()
//		{
//			return (gameObject->GetComponentInChildren<T>());
//		}
//
//		template<class T>
//		T GetComponentInParent()
//		{
//			return (gameObject->GetComponentInParent<T>());
//		}
//
//		template<class T>
//		std::list<T> GetComponents()
//		{
//			return (gameObject->GetComponents<T>());
//		}
//
//		template<class T>
//		std::list<T> GetComponentsInChildren()
//		{
//			return (gameObject->GetComponentsInChildren<T>());
//		}
//
//		template<class T>
//		std::list<T> GetComponentsInParent()
//		{
//			return (gameObject->GetComponentsInParent<T>());
//		}
	};
}

//#include "SaltyEngine/GameObject.hpp"

#endif // !COMPONENT_HPP_

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
	};
}

#endif // !COMPONENT_HPP_

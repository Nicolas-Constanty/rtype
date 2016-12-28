#pragma once

#ifndef BEHAVIOUR_HPP_
#define BEHAVIOUR_HPP_


#include "SaltyEngine/Component.hpp"

namespace SaltyEngine
{
	class GameObject;
	class PREF_EXPORT Behaviour : public Component
	{
	protected:
		// delete copy and move constructors and assign operators
		Behaviour(Behaviour const&) = delete;             // Copy construct
		Behaviour(Behaviour&&) = delete;                  // Move construct
		Behaviour& operator=(Behaviour const&) = delete;  // Copy assign
		Behaviour& operator=(Behaviour &&) = delete;      // Move assign
		explicit Behaviour(GameObject* const gameObj);
		Behaviour(const std::string name, GameObject* const gameObj);
		virtual ~Behaviour() {};
	public:
		bool		enabled;

	public:
		virtual Component * CloneComponent(GameObject* const obj) {
			return new Behaviour(obj);
		}
	};
}

#endif // !BEHAVIOUR_HPP_

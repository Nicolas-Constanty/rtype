#pragma once

#ifndef BEHAVIOUR_HPP_
#define BEHAVIOUR_HPP_


#include "SaltyEngine/Component.hpp"

namespace SaltyEngine
{
	class GameObject;
	class Behaviour : public Component
	{
	protected:
		// delete copy and move constructors and assign operators
		Behaviour(Behaviour const&) = delete;             // Copy construct
		Behaviour(Behaviour&&) = delete;                  // Move construct
		Behaviour& operator=(Behaviour const&) = delete;  // Copy assign
		Behaviour& operator=(Behaviour &&) = delete;      // Move assign
		Behaviour(GameObject* const gameObj);
		Behaviour(const std::string name, GameObject* const gameObj);
		virtual ~Behaviour() {};
	public:
		bool		enabled;
	};
}

#endif // !BEHAVIOUR_HPP_

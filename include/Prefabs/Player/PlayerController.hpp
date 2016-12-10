#pragma once

#ifndef PLAYER_CONTROLLER_HPP_
#define PLAYER_CONTROLLER_HPP_

#include "SaltyEngine/SaltyBehaviour.hpp"


namespace SaltyEngine {
	class PlayerController : public SaltyBehaviour
	{
	public:
		explicit PlayerController(GameObject* const gamObj);
		PlayerController(const std::string &name, GameObject* const gamObj);
		void Start();
		void FixedUpdate();
		void DisplayCoroutine();
		double speed;

	public:
		virtual Component *CloneComponent(GameObject* const obj) {
			return new PlayerController(obj);
		}
	};
}

#include "SaltyEngine/SaltyEngine.hpp"

#endif // !PLAYER_CONTROLLER_HPP_

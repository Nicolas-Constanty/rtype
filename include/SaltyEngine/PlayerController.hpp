#pragma once

#ifndef PLAYER_CONTROLLER_HPP_
#define PLAYER_CONTROLLER_HPP_

#include "SaltyBehaviour.hpp"


namespace SaltyEngine {
	class PlayerController : public SaltyBehaviour
	{
	public:
		explicit PlayerController(GameObject* const gamObj);
		PlayerController(const std::string &name, GameObject* const gamObj);
		void Start();
//		void FixedUpdate();
		void DisplayCoroutine();
		double speed;
	};
}

#include "SaltyEngine.hpp"

#endif // !PLAYER_CONTROLLER_HPP_

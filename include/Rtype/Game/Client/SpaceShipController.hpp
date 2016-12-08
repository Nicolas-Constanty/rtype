#pragma once

#ifndef SPACE_SHIP_CONTROLLER_HPP_
#define SPACE_SHIP_CONTROLLER_HPP_

#include "SaltyEngine/SaltyBehaviour.hpp"


namespace SaltyEngine {
	class SpaceShipController : public SaltyBehaviour
	{
	public:
		explicit SpaceShipController(GameObject* const gamObj);
		SpaceShipController(const std::string &name, GameObject* const gamObj);
		void Start();
		void FixedUpdate();
		void DisplayCoroutine();
		double speed;
	};
}

#include "SaltyEngine/SaltyEngine.hpp"

#endif // !SPACE_SHIP_CONTROLLER_HPP_

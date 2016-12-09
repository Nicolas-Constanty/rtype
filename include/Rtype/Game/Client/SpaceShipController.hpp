#pragma once

#ifndef SPACE_SHIP_CONTROLLER_HPP_
#define SPACE_SHIP_CONTROLLER_HPP_

#include "SaltyEngine/SaltyBehaviour.hpp"
#include "GameManager.hpp"

namespace SaltyEngine {
	class SpaceShipController : public SaltyBehaviour
	{
	public:
		explicit SpaceShipController(GameObject* const gamObj);
		SpaceShipController(const std::string &name, GameObject* const gamObj);
		void Start();
		void FixedUpdate();
		void DisplayCoroutine();

	private:
		double speed;
		GameManager    *manager;
	};
}

#include "SaltyEngine/SaltyEngine.hpp"

#endif // !SPACE_SHIP_CONTROLLER_HPP_

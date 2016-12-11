#pragma once

#ifndef SPACE_SHIP_CONTROLLER_HPP_
#define SPACE_SHIP_CONTROLLER_HPP_

#include "SaltyEngine/SaltyBehaviour.hpp"
#include "GameManager.hpp"

namespace SaltyEngine {
	class SpaceShipController : public SaltyBehaviour
	{
	public:
		explicit SpaceShipController(GameObject* const gamObj, bool playable = true);
		SpaceShipController(const std::string &name, GameObject* const gamObj, bool playable = true);
		void Start();
		void FixedUpdate();
		void DisplayCoroutine();

		//Actions
	public:
		void Move(int x, int y) const;

	private:
		double speed;
		GameManager    *manager;
		bool playable;
	};
}

#include "SaltyEngine/SaltyEngine.hpp"

#endif // !SPACE_SHIP_CONTROLLER_HPP_

#pragma once

#ifndef AA_HPP_
#define AA_HPP_

#include "SaltyBehaviour.hpp"


namespace SaltyEngine {
	class PlayerController : public SaltyBehaviour
	{
	public:
		PlayerController(GameObject* const gamObj);
		PlayerController(const std::string &name, GameObject* const gamObj);
		void Start();
		void FixedUpdate();
		void DisplayCoroutine();
		double speed;
	};
}

#include "SaltyEngine.hpp"

#endif // !AA_HPP_

#pragma once

#include "SaltyEngine/SaltyBehaviour.hpp"

namespace SaltyEngine {
	class TestSprite : public SaltyBehaviour
	{
	public:
		explicit TestSprite(GameObject* const gamObj);
		TestSprite(const std::string &name, GameObject* const gamObj);
		void Start();
		void FixedUpdate();
	};
}

#pragma once

#ifndef AA_HPP_
#define AA_HPP_

#include "SaltyBehaviour.hpp"


namespace SaltyEngine {
	class AA : public SaltyBehaviour
	{
	public:
		AA();
		AA(const std::string &name);
		void Start();
		void FixedUpdate();
		void DisplayCoroutine();
		float speed;
	};
}

#include "SaltyGame.hpp"

#endif // !AA_HPP_

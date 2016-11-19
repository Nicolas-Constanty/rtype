#pragma once

#ifndef AA_HPP_
#define AA_HPP_

#include "SaltyBehavior.hpp"


namespace SaltyEngine {
	class AA : public SaltyBehavior
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

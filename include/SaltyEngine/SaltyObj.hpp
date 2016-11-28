#pragma once

#ifndef SALTYOBJ_HPP_
#define SALTYOBJ_HPP_

#include "SaltyBehaviour.hpp"
#include "PlayerController.hpp"
#include "Monster/MonsterController.hpp"

namespace SaltyEngine
{
	template<typename T, typename ... Ts>
	struct typelist {};

	// ADD OBJECT HERE FOR GENERATION TEMPLATE
	using GameObjects = typelist<PlayerController, MonsterController>;
}

#endif // !SALTYOBJ_HPP_

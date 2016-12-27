#pragma once

#ifndef LASER_HPP_
#define LASER_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C" {
	class LIB_EXPORT Laser : public SaltyEngine::GameObject {
	public:
		Laser();
		virtual ~Laser();
	};
LIB_EXPORT	SaltyEngine::Object const *GetObjectPrefab();
}

#endif
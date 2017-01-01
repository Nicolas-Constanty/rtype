#pragma once

#ifndef LASER_HPP_
#define LASER_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C" {
	class PREF_EXPORT Laser : public SaltyEngine::GameObject {
	public:
		Laser();
		virtual ~Laser();
	};
	PREF_EXPORT	SaltyEngine::Object const *GetObjectPrefab();
}

#endif
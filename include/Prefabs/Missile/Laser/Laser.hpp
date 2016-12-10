#pragma once

#ifdef _WIN32
#ifdef LASER_EXPORTS
        #define LASER_API __declspec(dllexport)
    #else
        #define LASER_API __declspec(dllimport)
    #endif
#else
#define LASER_API
#endif

#ifndef LASER_HPP_
#define LASER_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C" {
	class Laser : public SaltyEngine::GameObject {
	public:
		Laser();
		virtual ~Laser();
	};
	LASER_API SaltyEngine::Object const *GetObjectPrefab();
}

#endif
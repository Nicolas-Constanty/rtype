#pragma once

#ifdef _WIN32
#ifdef LaserSpiral_EXPORTS
        #define LaserSpiralSPIRAL_API __declspec(dllexport)
    #else
        #define LaserSpiralSPIRAL_API __declspec(dllimport)
    #endif
#else
#define LaserSpiralSPIRAL_API
#endif

#ifndef LaserSpiralSPIRAL_HPP_
#define LaserSpiralSPIRAL_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C" {
	class LaserSpiral : public SaltyEngine::GameObject {
	public:
		LaserSpiral();
		virtual ~LaserSpiral();
	};
	SaltyEngine::Object const *GetObjectPrefab();
}

#endif
#pragma once

#ifdef _WIN32
#ifdef ENEMYBULLET_EXPORTS
        #define ENEMYBULLET_API __declspec(dllexport)
    #else
        #define ENEMYBULLET_API __declspec(dllimport)
    #endif
#else
#define ENEMYBULLET_API
#endif

#ifndef ENEMYBULLET_HPP_
#define ENEMYBULLET_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C" {
	class EnemyBullet : public SaltyEngine::GameObject {
	public:
		EnemyBullet();
		virtual ~EnemyBullet();
	};
	SaltyEngine::Object const *GetObjectPrefab();
}

#endif
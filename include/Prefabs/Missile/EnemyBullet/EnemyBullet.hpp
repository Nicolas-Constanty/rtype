#pragma once

#ifndef ENEMYBULLET_HPP_
#define ENEMYBULLET_HPP_

#include "SaltyEngine/GameObject.hpp"
#include "Common/DLLexport.hpp"

extern "C" {
	class LIB_EXPORT EnemyBullet : public SaltyEngine::GameObject {
	public:
		EnemyBullet();
		virtual ~EnemyBullet();
	};
LIB_EXPORT	SaltyEngine::Object const *GetObjectPrefab();
}

#endif
#pragma once

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/GameObject.hpp"

extern "C"
{
	class LIB_EXPORT Player : public SaltyEngine::GameObject
	{
	public:
		Player();
		virtual ~Player();
	};

	//extern PLAYER_API int nPlayer;

	LIB_EXPORT SaltyEngine::Object const *GetObjectPrefab();
}

#endif
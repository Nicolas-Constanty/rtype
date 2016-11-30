#pragma once
#include "SaltyEngine/SaltyEngine.hpp"

#ifdef _WIN32
#ifdef PLAYER_EXPORTS
#define PLAYER_API __declspec(dllexport)
#else
#define PLAYER_API __declspec(dllimport)
#endif
#else
#define PLAYER_API
#endif

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
	class Player : public SaltyEngine::GameObject
	{
	public:
		Player();
		virtual ~Player();
	};

	//extern MONSTER_API int nMonster;

	PLAYER_API SaltyEngine::Object const *GetObjectPrefab();
}

#endif
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "Common/Singleton.hpp"

template <>
SaltyEngine::SFML::AssetManager &Singleton<SaltyEngine::SFML::AssetManager>::Instance()
{
	static SaltyEngine::SFML::AssetManager _inst;

	return _inst;
}
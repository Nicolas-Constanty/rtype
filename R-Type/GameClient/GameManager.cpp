#include "GameManager.hpp"


GameManager::GameManager(SaltyEngine::GameObject * const gamObj) : SaltyBehaviour("GameManager", gamObj)
{
}

GameManager::GameManager(const std::string & name, SaltyEngine::GameObject * const gamObj) : SaltyBehaviour("GameManager", gamObj)
{
}

GameManager::~GameManager()
{
}

void GameManager::Start()
{
	m_network = gameObject->GetComponent<Rtype::Game::Client::GameClientObject>();
}

void GameManager::Send()
{
}

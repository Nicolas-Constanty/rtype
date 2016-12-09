#include <SaltyEngine/GameObject.hpp>
#include <SaltyEngine/SaltyBehaviour.hpp>
#include <Rtype/Game/Client/GameManager.hpp>


GameManager::GameManager(SaltyEngine::GameObject * const gamObj) : SaltyBehaviour("GameManager", gamObj)
{
}

GameManager::GameManager(const std::string & name, SaltyEngine::GameObject * const gamObj) : SaltyBehaviour(name, gamObj)
{
}

GameManager::~GameManager()
{

}

void GameManager::Start()
{
	m_network = gameObject->GetComponent<Rtype::Game::Client::GameClientObject>();
}

void GameManager::SendInput(std::string const &axisName, const float value)
{
    m_network->SendInput(axisName, value);
}

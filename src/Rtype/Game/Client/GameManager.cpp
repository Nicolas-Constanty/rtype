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
    m_client = gameObject->GetComponent<Rtype::Game::Client::GameClientObject>();
    m_server = gameObject->GetComponent<Rtype::Game::Server::GameServerObject>();
}

void GameManager::SendInput(std::string const &axisName, const float value)
{

}

bool GameManager::isServerSide() const
{
    return m_server != NULL;
}

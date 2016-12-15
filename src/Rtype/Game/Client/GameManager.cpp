#include <SaltyEngine/GameObject.hpp>
#include <SaltyEngine/SaltyBehaviour.hpp>
#include <Rtype/Game/Client/GameManager.hpp>
#include <SaltyEngine/SFML/BoxCollider2D.hpp>

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

void GameManager::OnCollisionExit(SaltyEngine::ICollider *collider)
{
    SaltyEngine::SFML::BoxCollider2D *c = dynamic_cast<SaltyEngine::SFML::BoxCollider2D*>(collider);

//    if (c->gameObject->GetTag() != SaltyEngine::Layer::Tag::Player)
//    {
        std::cout << "Object destroyed" << std::endl;
        Destroy(c->gameObject);
//    }
}

void GameManager::OnCollisionEnter(SaltyEngine::ICollider *collider)
{
    std::cout << "\e[32m======ENTER=======\e[0m" << std::endl;
}

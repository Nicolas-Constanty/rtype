#include <SaltyEngine/GameObject.hpp>
#include <SaltyEngine/SaltyBehaviour.hpp>
#include <Rtype/Game/Client/GameManager.hpp>
#include <SaltyEngine/SFML/BoxCollider2D.hpp>
#include <Prefabs/Player/PlayerController.hpp>

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

void GameManager::OnCollisionEnter(SaltyEngine::ICollider *)
{
    std::cout << "\e[32m======ENTER=======\e[0m" << std::endl;
}

void GameManager::addPlayer(SaltyEngine::GameObject *player)
{
    m_players.push_back(player);
}

std::list<SaltyEngine::GameObject *> const &GameManager::getPlayers() const
{
    return m_players;
}

void GameManager::OnPlayerDeath()
{
    for (SaltyEngine::GameObject *curr : m_players)
    {
        SaltyEngine::PlayerController *player = curr->GetComponent<SaltyEngine::PlayerController>();

        if (player && player->GetHealth() > 0)
        {
            return;
        }
    }
    //todo handle end of the game
}

void GameManager::addPod(SaltyEngine::GameObject *pod)
{
    m_pods.push_back(pod);
}

std::list<SaltyEngine::GameObject *> const &GameManager::getPods() const
{
    return m_pods;
}

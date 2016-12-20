#include <string>
#include <iostream>
#include <SaltyEngine/GameObject.hpp>
#include <SaltyEngine/SaltyBehaviour.hpp>
#include <Rtype/Game/Client/GameManager.hpp>
#include <SaltyEngine/SFML.hpp>
#include <Prefabs/Player/PlayerController.hpp>
#include <Rtype/Game/Client/BackgroundController.hpp>
#include <Rtype/Game/Common/GameObjectID.hpp>
#include <Rtype/Game/Client/GameGUIBeam.hpp>
#include "Common/Debug.hpp"

GameManager::GameManager(SaltyEngine::GameObject * const gamObj) : SaltyBehaviour("GameManager", gamObj)
{
//    gameObject->AddComponent<BackgroundController>();
    gameOver = new GameOver(this);
}

GameManager::GameManager(const std::string & name, SaltyEngine::GameObject * const gamObj) : SaltyBehaviour(name, gamObj)
{
    gameOver = new GameOver(this);
}

GameManager::~GameManager()
{

}

void GameManager::Start()
{
    m_client = gameObject->GetComponent<Rtype::Game::Client::GameClientObject>();
    m_server = gameObject->GetComponent<Rtype::Game::Server::GameServerObject>();

    if (m_client) {
        gameObject->AddComponent<BackgroundController>();
    }
    if (m_server) {
    monsterMap = SaltyEngine::SFML::AssetManager::Instance().LoadScene("scene" + std::to_string(m_server->GetLevel()));

    monsterMap->objects.sort([](std::pair<std::string, SaltyEngine::Vector2f> obj1, std::pair<std::string, SaltyEngine::Vector2f> obj2) {
        return (obj1.second.x < obj2.second.x);
    });
    }
}

bool GameManager::isServerSide() const
{
    return m_server != NULL;
}

void GameManager::OnCollisionExit(SaltyEngine::ICollider *collider)
{
    SaltyEngine::SFML::BoxCollider2D *c = dynamic_cast<SaltyEngine::SFML::BoxCollider2D*>(collider);

    if (c && c->gameObject->GetTag() != SaltyEngine::Layer::Tag::Player)
    {
        std::cout << "Object destroyed" << std::endl;
        Destroy(c->gameObject);
    }
}

void GameManager::OnCollisionEnter(SaltyEngine::ICollider *)
{
	Debug::PrintSuccess("======ENTER=======");
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
//    for (SaltyEngine::GameObject *curr : m_players)
//    {
//        SaltyEngine::PlayerController *player = curr->GetComponent<SaltyEngine::PlayerController>();
//
//        if (player && player->GetHealth() > 0)
//        {
//            return;
//        }
//    }
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

void GameManager::StartTheGame() {
    if (m_server) {
        m_server->Server()->SetLaunch(true);
//        for (std::pair<std::string, SaltyEngine::Vector2f> &obj : monsterMap->objects) {
//            std::cout << obj.first << std::endl;
//            if (obj.first != "Player") {
//                SaltyEngine::GameObject *object = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate(
//                        obj.first, obj.second, 0));
//                gameObjectContainer.Add(GameObjectID::NewID(), object);
//            }
//        }
    }
}

void GameManager::FixedUpdate() {
//    if (canSend % 120 == 0) {
        OnSendHighScore();
//        canSend = 0;
//    }
//    ++canSend;

    if (m_server && m_server->Server()->IsLaunch() && !endOfGame) {
        this->currentPosition = this->currentPosition + velocity * SaltyEngine::Engine::Instance().GetFixedDeltaTime();

        std::list<std::pair<std::string, SaltyEngine::Vector2f> >::iterator it = monsterMap->objects.begin();

        while (it != monsterMap->objects.end()) {
            if ((*it).second.x < this->currentPosition) {
                if ((*it).first != "Player") {
                    std::cout << "create " << (*it).first << std::endl;

                    SaltyEngine::Vector2f pos = (*it).second;
                    pos.x = SCREEN_X + 100;

                    SaltyEngine::GameObject *object = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate((*it).first, pos, 0));
                    gameObjectContainer.Add(GameObjectID::NewID(), object);
                }
                it = monsterMap->objects.erase(it);
            } else {
                return ;
            }
        }
        if (monsterMap->objects.empty()) {
            endOfGame = true;
        }
    } else if (endOfGame && m_server && gameOver && !gameOver->IsOver()) { // TODO Il manque le check si y'a plus de monstre coté serveur mais pour ça il faut le destroyer.
        gameOver->OverAction(GAMEOVER::VICTORY);
    }
}

void GameManager::OnSendHighScore() {
    if (m_server) {
        for (SaltyEngine::GameObject *gameObject1 : m_players) {
            SaltyEngine::PlayerController *playerController;

            if ((playerController = gameObject1->GetComponent<SaltyEngine::PlayerController>())) {
                if (playerController->IsUpdateHighScore()) {
                    BroadCastPackage<STATUSPackageGame>(&Network::Core::BasicConnection::SendData<STATUSPackageGame>,
                                                        playerController->GetHighScore(),
                                                        playerController->GetPlayerID());
                    playerController->SetUpdateHighScore(false);
                }
            }
        }
    }
}

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
    gameOver.reset(new GameOver(this));
}

GameManager::GameManager(const std::string & name, SaltyEngine::GameObject * const gamObj) : SaltyBehaviour(name, gamObj)
{
    gameOver.reset(new GameOver(this));
}

GameManager::~GameManager()
{

}

void GameManager::Start()
{
    gameObject->SetName("GameManager");
    m_client = gameObject->GetComponent<Rtype::Game::Client::GameClientObject>();
    m_server = gameObject->GetComponent<Rtype::Game::Server::GameServerObject>();

    if (m_client) {
        gameObject->AddComponent<BackgroundController>();
        PlaySound("rtype-ost");
    }
    if (m_server) {
		SaltyEngine::SFML::Sound::SetEnable(false);
        monsterMap = SaltyEngine::SFML::AssetManager::Instance().LoadScene(m_server->GetLevel());
        if (monsterMap)
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
        Destroy(c->gameObject);
    }
}

void GameManager::OnCollisionEnter(SaltyEngine::ICollider *)
{
	Debug::PrintSuccess("======ENTER=======");
}

void GameManager::addPlayer(SaltyEngine::GameObject *player, unsigned char playerID)
{
//    std::cout << "PLAYER ADDED" << std::endl;
    m_players[playerID] = player;
}

std::map<unsigned char, SaltyEngine::GameObject *> const &GameManager::getPlayers() const
{
    return m_players;
}

bool GameManager::IsAllPlayerDeath() const
{
    for (std::pair<unsigned char, SaltyEngine::GameObject *> const &curr : m_players)
    {
        CommonPlayerController *player = curr.second->GetComponent<CommonPlayerController>();

        if (player && player->GetGlobalLives() >= 0)
        {
            return (false);
        }
    }
    return (true);
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
    }
}

void GameManager::FixedUpdate() {
    OnSendHighScore();

    if (m_server && m_server->Server()->IsLaunch()) {
        if (IsAllPlayerDeath()) {
            gameOver->OverAction(GAMEOVER::DEFEAT);
            SaltyEngine::Engine::Instance().Stop();
        }
    }
    if (m_server && m_server->Server()->IsLaunch() && !endOfGame) {
        this->currentPosition = this->currentPosition + velocity * SaltyEngine::Engine::Instance().GetFixedDeltaTime();

        std::list<std::pair<std::string, SaltyEngine::Vector2f> >::iterator it = monsterMap->objects.begin();

        while (it != monsterMap->objects.end()) {
            if ((*it).second.x < this->currentPosition) {
                if ((*it).first != "Player") {

                    SaltyEngine::Vector2f pos = (*it).second;

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
    } else if (endOfGame && m_server && gameOver && !gameOver->IsOver() && IsSceneEmpty()) {
        std::cout << "Victory" << std::endl;
        gameOver->OverAction(GAMEOVER::VICTORY);
        SaltyEngine::Engine::Instance().Stop();
    }
}

void GameManager::OnSendHighScore() {
    if (m_server) {
        for (std::pair<const unsigned char, SaltyEngine::GameObject *> &curr : m_players) {
            SaltyEngine::PlayerController *playerController;

            if ((playerController = curr.second->GetComponent<SaltyEngine::PlayerController>())) {
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

SaltyEngine::GameObject *GameManager::GetPlayer(unsigned char playerID) const
{
    std::map<unsigned char, SaltyEngine::GameObject *>::const_iterator  it = m_players.find(playerID);

    if (it == m_players.end())
        return nullptr;
    return it->second;
}

unsigned char GameManager::GetPlayerID(SaltyEngine::GameObject *player) const
{
    for (std::pair<unsigned char, SaltyEngine::GameObject *> const &curr : m_players)
    {
        if (curr.second == player)
            return curr.first;
    }
    return (unsigned char)~0;
}

bool GameManager::IsSceneEmpty() const {
    std::vector<SaltyEngine::GameObject *> const &list = SaltyEngine::Engine::Instance().GetCurrentScene()->GetAllGameObject();
    for (SaltyEngine::GameObject *gameObject : list) {
        if (gameObject->GetTag() != SaltyEngine::Layer::Tag::Player
            && gameObject->GetTag() != SaltyEngine::Layer::Tag::BulletPlayer
            && gameObject->GetTag() != SaltyEngine::Layer::Tag::Destroy
            && gameObject->GetTag() != SaltyEngine::Layer::Tag::Untagged
            && gameObject->GetTag() != SaltyEngine::Layer::Tag::BulletEnemy) {
            return false;
        }
    }
    return true;
}

void GameManager::PlaySound(std::string const &sound, bool loop) {
    if (m_backgroudnSound) {
        m_backgroudnSound->Stop();
        m_backgroudnSound = NULL;
    }

    m_backgroudnSound = SaltyEngine::SFML::AssetManager::Instance().GetSound(sound); // rtype-ost
    if (m_backgroudnSound) {
        m_backgroudnSound->SetLoop(loop);
        m_backgroudnSound->Play();
    }
}

SaltyEngine::Component *GameManager::CloneComponent(SaltyEngine::GameObject *const obj)
{
    return new GameManager(obj);
}

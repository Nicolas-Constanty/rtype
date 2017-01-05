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
#include <SaltyEngine/SFML/SFMLSceneLoader.hpp>
#include "Common/Debug.hpp"

GameManager::GameManager(SaltyEngine::GameObject * const gamObj) :
        SaltyBehaviour("GameManager", gamObj),
        m_server(nullptr),
        m_client(nullptr)
{
//    gameObject->AddComponent<BackgroundController>();
    gameOver.reset(new GameOver(this));
}

GameManager::GameManager(const std::string & name, SaltyEngine::GameObject * const gamObj) :
        SaltyBehaviour(name, gamObj),
        m_server(nullptr),
        m_client(nullptr)
{
    gameOver.reset(new GameOver(this));
}

GameManager::~GameManager()
{

}

void GameManager::Start()
{
    Debug::PrintInfo("Je suis dans le game manager");
    gameObject->SetName("GameManager");
    m_client = gameObject->GetComponent<Rtype::Game::Client::GameClientObject>();
    m_server = gameObject->GetComponent<Rtype::Game::Server::GameServerObject>();

    if (m_client) {
        Debug::PrintInfo("Je suis un client");
        gameObject->AddComponent<BackgroundController>();
        PlaySound("rtype-ost");
        CreateGUI();
        if (m_client->GetClient()) {
            Debug::PrintSuccess("Set GUI on client");
            m_client->GetClient()->OnSetGUI();
        } else {
            Debug::PrintError("Can't set GUI on client");
        }
    }
    if (m_server) {
        Debug::PrintInfo("Je suis un server");
		SaltyEngine::SFML::Sound::SetEnable(false);
        //	SaltyEngine::Engine::Instance().SetFrameRate(30);

        SaltyEngine::SFML::SFMLSceneLoader *sl = dynamic_cast<SaltyEngine::SFML::SFMLSceneLoader *>(SaltyEngine::Engine::Instance().GetSceneLoader());
        if (sl)
        {
            monsterMap = sl->GetScene();
            if (monsterMap)
                monsterMap->objects.sort([](std::pair<std::string, SaltyEngine::PrefabDefault> obj1, std::pair<std::string, SaltyEngine::PrefabDefault> obj2) {
                    return (obj1.second.pos.x < obj2.second.pos.x);
                });
        } else {
            Debug::PrintError("Need to load map before run scene");
        }
    }
//    if (m_client) {
//        if (m_client->GetClient()) {
//            std::cout << "setting GUI" << std::endl;
//            m_client->GetClient()->OnSetGUI();
//        }
//    }
}

bool GameManager::isServerSide() const
{
    return m_server != NULL;
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

        std::list<std::pair<std::string, SaltyEngine::PrefabDefault> >::iterator it = monsterMap->objects.begin();

        while (it != monsterMap->objects.end()) {
            if ((*it).second.pos.x < this->currentPosition) {
                if ((*it).first != "Player" && (*it).first != "GameManagerServer") {

                    SaltyEngine::Vector2f pos = (*it).second.pos;

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
        if (gameObject->GetTag() == SaltyEngine::Layer::Tag::Enemy) {
            return false;
        }
//        if (gameObject->GetTag() != SaltyEngine::Layer::Tag::Player
//            && gameObject->GetTag() != SaltyEngine::Layer::Tag::BulletPlayer
//            && gameObject->GetTag() != SaltyEngine::Layer::Tag::Destroy
//            && gameObject->GetTag() != SaltyEngine::Layer::Tag::Untagged
//            && gameObject->GetTag() != SaltyEngine::Layer::Tag::BulletEnemy
//            && gameObject->GetTag() != SaltyEngine::Layer::Tag::Pod) {
//            return false;
//        }
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

void GameManager::CreateGUI()
{
    const SaltyEngine::Engine &engine = SaltyEngine::Engine::Instance();
    const SaltyEngine::Vector2ui size = engine.GetSize();

    SaltyEngine::GameObject     *guiGameBeam = (SaltyEngine::GameObject*)SaltyEngine::Instantiate();
    guiGameBeam->SetName("GUIBeam");
    guiGameBeam->AddComponent<GameGUIBeam>();
    SaltyEngine::SFML::SpriteRenderer *sprr = guiGameBeam->GetComponent<SaltyEngine::SFML::SpriteRenderer>();
    guiGameBeam->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));
    guiGameBeam->transform.SetPosition(size.x / 2,
                                       size.y - ((sprr) ? (sprr->GetSprite()->GetRect()->_height / 1.5f) : 0));

    SaltyEngine::GameObject     *guiGameHighscore = (SaltyEngine::GameObject*)SaltyEngine::Instantiate();
    guiGameHighscore->SetName("GUIHighscore");
    guiGameHighscore->AddComponent<GameGUIHighscore>();
    guiGameHighscore->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));
    guiGameHighscore->transform.SetPosition(static_cast<float>(size.x / 1.2), guiGameBeam->transform.GetPosition().y);

    SaltyEngine::GameObject     *victoryScreen = (SaltyEngine::GameObject*)SaltyEngine::Instantiate();
    victoryScreen->SetName("EndScreen");
    victoryScreen->AddComponent<EndScreen>();
    victoryScreen->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));
    victoryScreen->transform.SetPosition(size.x / 2, static_cast<float>(size.y / 2.3));
    gameObject->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));

    SaltyEngine::GameObject     *guiLives = (SaltyEngine::GameObject*)SaltyEngine::Instantiate();
    guiLives->SetName("GUILives");
    guiLives->AddComponent<GameGUILives>();
    guiLives->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));
    guiLives->transform.SetPosition(static_cast<float>(100), guiGameBeam->transform.GetPosition().y);

    // on set le button de fin
    SaltyEngine::GameObject *launch_button = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    launch_button->SetName("QUITGameButton");
    SaltyEngine::GUI::SFML::Button *b = launch_button->AddComponent<SaltyEngine::GUI::SFML::Button>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button"),
                                                                                                    SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button_over"));

    launch_button->transform.SetParent(&gameObject->transform);
    launch_button->transform.SetPosition(size.x / 2, victoryScreen->transform.GetPosition().y + 100);
    launch_button->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));
    b->onClick.AddListener("LoadRoom", [](){
        SaltyEngine::Engine::Instance().LoadScene("sceneRoom");
    });
}
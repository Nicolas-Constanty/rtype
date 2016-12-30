//
// Created by gaspar_q on 12/6/16.
//

#include <Rtype/Game/Client/RtypeClientGameClient.hpp>
#include <SaltyEngine/SaltyEngine.hpp>
#include <SaltyEngine/SFML.hpp>
#include <SaltyEngine/Vector2.hpp>
#include <Rtype/Game/Client/SpaceShipController.hpp>
#include <Rtype/Game/Common/RtypeNetworkFactory.hpp>
#include <Prefabs/GenericController.hpp>
#include <Prefabs/Missile/Laser/LaserController.hpp>
#include <Prefabs/Player/PlayerController.hpp>
#include <Prefabs/Pod/PodController.hpp>
#include <Prefabs/Mate/MateComponent.hpp>
#include <Rtype/Game/Client/EndScreen.hpp>

Rtype::Game::Client::RtypeClientGameClient::RtypeClientGameClient(
        Network::Core::NativeSocketIOOperationDispatcher &dispatcher, const uint32_t secret) :
        Rtype::Game::Common::RtypeGameClient(dispatcher),
        gameOver(nullptr),
        gameGUIHighscore(nullptr),
        secret(secret)
{

}

Rtype::Game::Client::RtypeClientGameClient::RtypeClientGameClient(const Rtype::Game::Client::RtypeClientGameClient &ref) :
    Rtype::Game::Common::RtypeGameClient(ref),
    gameOver(nullptr),
    gameGUIHighscore(nullptr),
    secret(ref.secret)
{

}

Rtype::Game::Client::RtypeClientGameClient::~RtypeClientGameClient()
{

}

bool Rtype::Game::Client::RtypeClientGameClient::OnStart()
{
    SendPackage<AUTHENTICATEPackageGame>(&Network::UDP::AUDPConnection::SendReliable<AUTHENTICATEPackageGame>, secret);
    connected = true;

    SaltyEngine::GameObject *goHighscore = SaltyEngine::GameObject::Find("GUIHighscore");

    if (goHighscore)
        this->gameGUIHighscore = goHighscore->GetComponent<GameGUIHighscore>();

    SaltyEngine::GameObject *gameman = SaltyEngine::GameObject::FindGameObjectWithTag(SaltyEngine::Layer::Tag::GameManager);

    if (gameman)
        gameManager = gameman->GetComponent<GameManager>();

    SaltyEngine::GameObject *endS = SaltyEngine::GameObject::Find("EndScreen");

    if (endS)
        this->endScreen = endS->GetComponent<EndScreen>();

    gameOver = new GameOver(gameManager);
    return true;
}

void Rtype::Game::Client::RtypeClientGameClient::onGetSTATUSPackage(STATUSPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    if (this->gameGUIHighscore && pack.playerID == this->playerID) {
        this->gameGUIHighscore->DisplayHighScore(pack.highScore);
    }
}

void Rtype::Game::Client::RtypeClientGameClient::onGetPINGPackage(PINGPackageGame const &pack)
{
    reply = false;
    OnDiscoveringPackage(pack);
    SendPackage<PINGPackageGame>(&Network::UDP::AUDPConnection::SendReliable<PINGPackageGame>, pack.secret);
//    std::cout << "Receive ping => ok" << std::endl;
//    SendReliable(*factory.create<PINGPackageGame>(pack.secret));
}

void Rtype::Game::Client::RtypeClientGameClient::onGetAUTHENTICATEPackage(AUTHENTICATEPackageGame const &pack)
{
    Debug::PrintSuccess("Authenticated");
    reply = false;
    OnDiscoveringPackage(pack);
    playerID = pack.playerId;
}

void Rtype::Game::Client::RtypeClientGameClient::onGetCREATEPackage(CREATEPackageGame const &pack)
{
    OnDiscoveringPackage(pack);

    try
    {
        SaltyEngine::GameObject *object = RtypeNetworkFactory::Create(pack.ID, SaltyEngine::Vector((float)pack.posX, (float)pack.posY), pack.rotation);

        gameManager->gameObjectContainer.Add(pack.objectID, object);
        SaltyEngine::PlayerController *playerController = object->GetComponent<SaltyEngine::PlayerController>();
        if (playerController) {
            playerController->SetColor(playerID);
            objectIDPlayerController = pack.objectID;
        }
    }
    catch (std::runtime_error const &error)
    {
		Debug::PrintError(error.what());
    }

}

void Rtype::Game::Client::RtypeClientGameClient::onGetBEAMPackage(BEAMPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    SaltyEngine::GameObject *gameObject;
    if ((gameObject = gameManager->gameObjectContainer[pack.objectID])) {
        MateComponent *playerController = gameObject->GetComponent<MateComponent>();
        if (playerController) {
            playerController->m_beamSFX->SetActive(true);
        }
    }

    //todo resolve beam on game. Check if it's <this> player that send the beam.
}

void Rtype::Game::Client::RtypeClientGameClient::onGetSHOTPackage(SHOTPackageGame const &pack)
{
    OnDiscoveringPackage(pack);

    SaltyEngine::GameObject *laser = dynamic_cast<SaltyEngine::GameObject *>(::SaltyEngine::Instantiate("Laser", SaltyEngine::Vector2f(pack.x, pack.y)));
    laser->GetComponent<LaserController>()->Power(pack.power);
    SaltyEngine::GameObject *gameObject;
    if ((gameObject = gameManager->gameObjectContainer[pack.objectID])) {
        PodHandler  *podHandler = gameObject->GetComponent<PodHandler>();
        MateComponent *playerController = gameObject->GetComponent<MateComponent>();
        if (playerController) {
            playerController->m_beamSFX->SetActive(false);
        }
        if (podHandler)
        {
            podHandler->Shot();
        }
    }

    //todo resolve shot package with power of shot
}

void Rtype::Game::Client::RtypeClientGameClient::onGetDIEPackage(DIEPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    SaltyEngine::GameObject *obj = gameManager->gameObjectContainer[pack.objectID];
    if (obj) {
        AGenericController *aGenericController = obj->GetComponent<AGenericController>();
        if (aGenericController) {
            aGenericController->Die();
        } else {
            SaltyEngine::Object::Destroy(obj);
			Debug::PrintWarning("No AGenericController set");
        }
    }
    //todo resolve die in the game
}

void Rtype::Game::Client::RtypeClientGameClient::onGetTAKEPackage(TAKEPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    SaltyEngine::GameObject *object = gameManager->gameObjectContainer[pack.objectID];
    SaltyEngine::GameObject *play = gameManager->gameObjectContainer[pack.playerObjectID];

    if (object && play)
    {
        PodController   *podController = object->GetComponent<PodController>();
        PodHandler      *podHandler = play->GetComponent<PodHandler>();

        if (podHandler && podController)
        {
            podController->Attach(podHandler, static_cast<bool>(pack.front));
        }
    }
}

void Rtype::Game::Client::RtypeClientGameClient::onGetCALLPackage(CALLPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    SaltyEngine::GameObject *object = gameManager->gameObjectContainer[pack.objectID];
    SaltyEngine::GameObject *player = gameManager->gameObjectContainer[pack.playerObjectID];

    if (object)
    {
        PodController   *podController = object->GetComponent<PodController>();
        PodHandler      *handler = player->GetComponent<PodHandler>();

        if (podController && handler)
        {
            handler->Call(podController);
        }
    }
}

void Rtype::Game::Client::RtypeClientGameClient::onGetMOVEPackage(MOVEPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    SaltyEngine::GameObject *obj = gameManager->gameObjectContainer[pack.objectID];
    if (obj) {
        obj->transform.SetPosition(SaltyEngine::Vector(pack.posX, pack.posY));
        obj->transform.SetRotation(pack.rotation);
    }
}

void Rtype::Game::Client::RtypeClientGameClient::onGetLAUNCHPackage(LAUNCHPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    SaltyEngine::GameObject *object = gameManager->gameObjectContainer[pack.objectID];

    if (object)
    {
        PodController   *podController = object->GetComponent<PodController>();

        if (podController && podController->isAttached())
        {
            podController->gameObject->transform.SetPosition(SaltyEngine::Vector(pack.fromX, pack.fromY));
            podController->getAttachedPlayer()->Launch();
        }
    }
}

void Rtype::Game::Client::RtypeClientGameClient::onGetREBORNPackage(REBORNPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    SaltyEngine::GameObject *object = gameManager->gameObjectContainer[pack.objectID];

    if (object)
    {
        CommonPlayerController   *controller = object->GetComponent<CommonPlayerController>();

        if (controller)
        {
            controller->Reborn();
        }
    }
}

void Rtype::Game::Client::RtypeClientGameClient::onGetFAILUREPackage(FAILUREPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo resolve failure package
}

void Rtype::Game::Client::RtypeClientGameClient::onGetUPGRADEPackage(UPGRADEPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    SaltyEngine::GameObject *object = gameManager->gameObjectContainer[pack.objectID];

    if (object)
    {
        PodController   *podController = object->GetComponent<PodController>();

        if (podController)
        {
            try
            {
                podController->Upgrade(RtypeNetworkFactory::GetStringFromID(pack.rocket));
            }
            catch (std::runtime_error const &err)
            {
                Debug::PrintError(err.what());
            }
        }
    }
}

void Rtype::Game::Client::RtypeClientGameClient::OnDisconnect()
{
    Common::RtypeGameClient::OnDisconnect();
    SaltyEngine::Engine::Instance().Stop();
}

void Rtype::Game::Client::RtypeClientGameClient::onGetENEMYSHOTPackage(ENEMYSHOTPackageGame const &pack) {
    OnDiscoveringPackage(pack);
    SaltyEngine::GameObject *obj = gameManager->gameObjectContainer[pack.objectID];
    if (obj) {
        AGenericController *aGenericController = obj->GetComponent<AGenericController>();

        if (aGenericController) {
            aGenericController->Shot();
        }
    }
}

void Rtype::Game::Client::RtypeClientGameClient::onGetMATEPackage(MATEPackageGame const &matePackageGame) {
    OnDiscoveringPackage(matePackageGame);
    try {
        SaltyEngine::GameObject *object = RtypeNetworkFactory::Create(1, SaltyEngine::Vector((float) matePackageGame.x,
                                                                                             (float) matePackageGame.y),
                                                                      0);

        gameManager->gameObjectContainer.Add(matePackageGame.objectID, object);
        gameManager->gameObjectContainer.AddMate(matePackageGame.playerID, object);
        MateComponent *component = object->GetComponent<MateComponent>();
        if (component) {
            component->SetColor(matePackageGame.playerID);
        }
    } catch (...) {
        Debug::PrintError("Unknown object");
    }
}

void Rtype::Game::Client::RtypeClientGameClient::onGetGAMEOVERPackage(GAMEOVERPackageGame const &game) {
    OnDiscoveringPackage(game);
    if (gameOver && !gameOver->IsOver()) {
        GAMEOVER over = static_cast<GAMEOVER>(game.status);
        if (over == GAMEOVER::VICTORY) {
            this->endScreen->VictoryScreen();
            gameManager->PlaySound("r-type_stage_clear", false);
        } else {
            this->endScreen->DefeatScreen();
            gameManager->PlaySound("r-type-game_over", false);
        }
        SaltyEngine::GameObject *obj = gameManager->gameObjectContainer[this->objectIDPlayerController];

        if (obj) {
            CommonPlayerController *playerController = obj->GetComponent<CommonPlayerController>();
            if (playerController)
                playerController->setInvincible();
        }
    }
}

void Rtype::Game::Client::RtypeClientGameClient::onGetDEATHPackage(DEATHPackage const &pack)
{
    OnDiscoveringPackage(pack);
    SaltyEngine::GameObject *obj = gameManager->gameObjectContainer[pack.objectID];

    if (obj)
    {
        CommonPlayerController   *playerController = obj->GetComponent<CommonPlayerController>();

        if (playerController)
        {
            playerController->Die();
        }
    }
}

void Rtype::Game::Client::RtypeClientGameClient::onGetDISCONNECTPackage(DISCONNECTPackageGame const &pack)
{
    Rtype::Game::Common::RtypeGameClient::onGetDISCONNECTPackage(pack);
    SaltyEngine::GameObject *obj = gameManager->gameObjectContainer.GetMateObjectID(pack.playerID);

    if (obj) {
        SaltyEngine::SFML::SpriteRenderer *mateComponent = obj->GetComponent<SaltyEngine::SFML::SpriteRenderer>();
        if (mateComponent) {
            mateComponent->SetColor(SaltyEngine::Color::Red());
        }
    }
}

void Rtype::Game::Client::RtypeClientGameClient::onGetRECONNECTPackage(RECONNECTPackageGame const &pack) {
//    Rtype::Game::Common::RtypeGameClient::onGetDISCONNECTPackage(pack);
    OnDiscoveringPackage(pack);
    SaltyEngine::GameObject *obj = gameManager->gameObjectContainer.GetMateObjectID(pack.playerID);

    if (obj) {
        SaltyEngine::SFML::SpriteRenderer *mateComponent = obj->GetComponent<SaltyEngine::SFML::SpriteRenderer>();
        if (mateComponent) {
            mateComponent->SetColor(SaltyEngine::Color::White());
        }
    }
}

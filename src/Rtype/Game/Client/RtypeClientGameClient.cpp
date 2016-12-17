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

Rtype::Game::Client::RtypeClientGameClient::RtypeClientGameClient(
        Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
        Rtype::Game::Common::RtypeGameClient(dispatcher)
{

}

Rtype::Game::Client::RtypeClientGameClient::RtypeClientGameClient(const Rtype::Game::Client::RtypeClientGameClient &ref) :
    Rtype::Game::Common::RtypeGameClient(ref)
{

}

Rtype::Game::Client::RtypeClientGameClient::~RtypeClientGameClient()
{

}

bool Rtype::Game::Client::RtypeClientGameClient::OnStart()
{
//    SendReliable(*factory.create<PINGPackageGame>(32, 0));
    SendPackage<AUTHENTICATEPackageGame>(&Network::UDP::AUDPConnection::SendReliable<AUTHENTICATEPackageGame>, 42);
//    SendReliable(*factory.create<AUTHENTICATEPackageGame>(42));
    connected = true;

    SaltyEngine::GameObject *gameman = SaltyEngine::Engine::Instance().GetCurrentScene()->FindByName("Rtype");

    if (gameman)
        gameManager = gameman->GetComponent<GameManager>();

    return true;
}

void Rtype::Game::Client::RtypeClientGameClient::onGetSTATUSPackage(STATUSPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
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
    std::cout << "\e[32mAuthenticated\e[0m: " << pack << std::endl;
    reply = false;
    OnDiscoveringPackage(pack);
    playerID = pack.playerId;
}

void Rtype::Game::Client::RtypeClientGameClient::onGetCREATEPackage(CREATEPackageGame const &pack)
{
    std::cout << pack << std::endl;
    OnDiscoveringPackage(pack);

    try
    {
        SaltyEngine::GameObject *object = RtypeNetworkFactory::Create(pack.ID, SaltyEngine::Vector((float)pack.posX, (float)pack.posY), pack.rotation);

        gameManager->gameObjectContainer.Add(pack.objectID, object);
        SaltyEngine::PlayerController *playerController = object->GetComponent<SaltyEngine::PlayerController>();
        if (playerController) {
            playerController->SetColor(playerID);
        }
    }
    catch (std::runtime_error const &error)
    {
        std::cerr << "\e[31mCreate Package\e[0m: " << error.what() << std::endl;
    }

}

void Rtype::Game::Client::RtypeClientGameClient::onGetBEAMPackage(BEAMPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    std::cout << pack << std::endl;
    SaltyEngine::GameObject *gameObject;
    if ((gameObject = gameManager->gameObjectContainer[pack.objectID])) {
        SaltyEngine::PlayerController *playerController = gameObject->GetComponent<SaltyEngine::PlayerController>();
        if (playerController) {
            std::cout << "BEAM BADIBIM" << std::endl;
            playerController->Beam();
        }
    }
    std::cout << pack << std::endl;

    //todo resolve beam on game. Check if it's <this> player that send the beam.
}

void Rtype::Game::Client::RtypeClientGameClient::onGetSHOTPackage(SHOTPackageGame const &pack)
{
    std::cout << pack << std::endl;
    OnDiscoveringPackage(pack);

    SaltyEngine::GameObject *obj = gameManager->gameObjectContainer[pack.id];
    if (obj) {
        SaltyEngine::GameObject *laser = dynamic_cast<SaltyEngine::GameObject *>(::SaltyEngine::Instantiate("Laser", obj->transform.position));
        gameManager->gameObjectContainer.Add(pack.objectID, laser);
        laser->GetComponent<LaserController>()->Power(pack.power);
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
            std::cout << pack << std::endl;
            aGenericController->Die();
        } else {
            SaltyEngine::Object::Destroy(obj);
            std::cout << "\e[43m Warning: No AGenericController set \e[0m" << std::endl;
        }
    }
    //todo resolve die in the game
}

void Rtype::Game::Client::RtypeClientGameClient::onGetTAKEPackage(TAKEPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo resolve take in the game
    SaltyEngine::GameObject *object = gameManager->gameObjectContainer[pack.objectID];

    if (object)
    {
        PodController   *podController = object->GetComponent<PodController>();

        if (podController && !podController->isAttached())
        {
            podController->getAttachedPlayer()->Attach(podController);
        }
    }
}

void Rtype::Game::Client::RtypeClientGameClient::onGetCALLPackage(CALLPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    SaltyEngine::GameObject *object = gameManager->gameObjectContainer[pack.objectID];

    if (object)
    {
        PodController   *podController = object->GetComponent<PodController>();

        if (podController && podController->isAttached())
        {
            podController->getAttachedPlayer()->Call();
        }
    }
    //todo resolve drop package
}

void Rtype::Game::Client::RtypeClientGameClient::onGetMOVEPackage(MOVEPackageGame const &pack)
{
//    std::cout << "void Rtype::Game::Client::RtypeClientGameClient::onGetMOVEPackage(MOVEPackageGame const &pack) objectID IS == " << pack.objectID << std::endl;
    std::cout << pack << std::endl;
    OnDiscoveringPackage(pack);
    SaltyEngine::GameObject *obj = gameManager->gameObjectContainer[pack.objectID];
    if (obj) {
        std::cout << "obj found !" << std::endl;
        obj->transform.position = SaltyEngine::Vector(pack.posX, pack.posY);
    } else {
        std::cout << "obj not found !!" << std::endl;
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
            podController->getAttachedPlayer()->Launch();
        }
    }
}

void Rtype::Game::Client::RtypeClientGameClient::onGetREBORNPackage(REBORNPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo resolve reborn package
}

void Rtype::Game::Client::RtypeClientGameClient::onGetFAILUREPackage(FAILUREPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo resolve failure package
}

void Rtype::Game::Client::RtypeClientGameClient::onGetINPUTPackage(INPUTPackageGame const &pack)
{
//    std::cout << pack << std::endl;
    OnDiscoveringPackage(pack);
    //SaltyEngine::Input::VirtualInputManager::SetAxis(pack.axes, pack.value);
    //todo resolve failure package
//    InputKey::SetAxis(pack.axes, pack.);
}

void Rtype::Game::Client::RtypeClientGameClient::onGetUPGRADEPackage(UPGRADEPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
}

void Rtype::Game::Client::RtypeClientGameClient::SendInput(std::string const &axisName, float const value)
{
    SendPackage<INPUTPackageGame>(&Network::Core::BasicConnection::SendData<INPUTPackageGame>, axisName, value);
//    SendData(*factory.create<INPUTPackageGame>(axisName, value));
}

void Rtype::Game::Client::RtypeClientGameClient::OnDisconnect()
{
    Common::RtypeGameClient::OnDisconnect();
    SaltyEngine::Engine::Instance().Stop();

}

void Rtype::Game::Client::RtypeClientGameClient::onGetENEMYSHOTPackage(ENEMYSHOTPackageGame const &pack) {
    std::cout << pack << std::endl;
    SaltyEngine::GameObject *obj = gameManager->gameObjectContainer[pack.objectID];
    if (obj) {
        AGenericController *aGenericController = obj->GetComponent<AGenericController>();
        if (aGenericController) {
            aGenericController->Shot();
        }
    }
}

void Rtype::Game::Client::RtypeClientGameClient::onGetMATEPackage(MATEPackageGame const &matePackageGame) {
    std::cout << matePackageGame << std::endl;
    try {
        SaltyEngine::GameObject *object = RtypeNetworkFactory::Create(1, SaltyEngine::Vector((float) matePackageGame.x,
                                                                                             (float) matePackageGame.y),
                                                                      0);

        gameManager->gameObjectContainer.Add(matePackageGame.objectID, object);
        MateComponent *component = object->GetComponent<MateComponent>();
        if (component) {
            component->SetColor(matePackageGame.playerID);
        }
    } catch (...) {
        std::cout << "unkown obj" << std::endl;
    }
}

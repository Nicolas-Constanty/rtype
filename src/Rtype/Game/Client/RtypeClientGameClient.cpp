//
// Created by gaspar_q on 12/6/16.
//

#include <Rtype/Game/Client/RtypeClientGameClient.hpp>
#include <SaltyEngine/SaltyEngine.hpp>
#include <SaltyEngine/SFML.hpp>
#include <SaltyEngine/Input/VirtualInutManager.hpp>
#include <SaltyEngine/Vector2.hpp>
#include <Rtype/Game/Client/SpaceShipController.hpp>
#include <Rtype/Game/Common/RtypeNetworkFactory.hpp>
#include <Prefabs/GenericController.hpp>

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

    SaltyEngine::GameObject *gameman = SaltyEngine::Engine::Instance().GetCurrentScene()->FindByName("GameManager");

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

    //TODO URGENT
    // FACTORY CORRESPONDANCE AVEC L'ID PLEASE
    try
    {
        SaltyEngine::GameObject *object = RtypeNetworkFactory::Create(pack.ID, SaltyEngine::Vector((float)pack.posX, (float)pack.posY), pack.rotation);

        gameManager->gameObjectContainer.Add(pack.objectID, object);

  //      std::cout << object->GetName() << std::endl;
//        SaltyEngine::GameObject *obj = gameManager->gameObjectContainer[pack.objectID];
        //if (obj) {
          //  std::cout << "CREATE TROLOL :: " << obj->GetName() << std::endl;
       // }
        //std::cout << "ENDD" << std::endl;
      //  *SaltyEngine::SaltyEngine::Instance().GetCurrentScene() << object;
    }
    catch (std::runtime_error const &error)
    {
        std::cerr << "\e[31mCreate Package\e[0m: " << error.what() << std::endl;
    }

//    if (pack.ID == 0)  { // Ajout du player qu'on va jouer
//        SaltyEngine::GameObject	*player;
//        player = dynamic_cast<SaltyEngine::GameObject*>(SaltyEngine::Object::Instantiate());
//        player->AddComponent<SaltyEngine::SpaceShipController>();
//        *SaltyEngine::SaltyEngine::Instance().GetCurrentScene() << player;
//
//        gameManager->gameObjectContainer.Add(pack.objectID, player);
//    }
//    if (pack.ID == 1)  { // Ajout du player qu'on va jouer
//        SaltyEngine::GameObject	*player;
//        player = dynamic_cast<SaltyEngine::GameObject*>(SaltyEngine::Object::Instantiate());
//        player->AddComponent<SaltyEngine::SpaceShipController>(false);
//        *SaltyEngine::SaltyEngine::Instance().GetCurrentScene() << player;
//
//        gameManager->gameObjectContainer.Add(pack.objectID, player);
//    }
}

void Rtype::Game::Client::RtypeClientGameClient::onGetBEAMPackage(BEAMPackageGame const &pack)
{
    std::cout << pack << std::endl;
    OnDiscoveringPackage(pack);
    //todo resolve beam on game. Check if it's <this> player that send the beam.
}

void Rtype::Game::Client::RtypeClientGameClient::onGetSHOTPackage(SHOTPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo resolve shot package with power of shot
}

void Rtype::Game::Client::RtypeClientGameClient::onGetDIEPackage(DIEPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo resolve die in the game
}

void Rtype::Game::Client::RtypeClientGameClient::onGetTAKEPackage(TAKEPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo resolve take in the game
}

void Rtype::Game::Client::RtypeClientGameClient::onGetDROPPackage(DROPPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo resolve drop package
}

void Rtype::Game::Client::RtypeClientGameClient::onGetMOVEPackage(MOVEPackageGame const &pack)
{
    std::cout << pack << std::endl;
    OnDiscoveringPackage(pack);
    SaltyEngine::GameObject *obj = gameManager->gameObjectContainer[pack.objectID];
    if (obj) {
        obj->transform.position = SaltyEngine::Vector(pack.posX, pack.posY);
    }
 //   SaltyEngine::GameObject *obj = SaltyEngine::SaltyEngine::Instance().GetCurrentScene()->FindById(static_cast<size_t>(pack.objectID));
 //   if (obj)
 //   {
 //       SaltyEngine::SpaceShipController *ship = obj->GetComponent<SaltyEngine::SpaceShipController>();
    //       if (ship)
    //       {
    //           ship->Move(pack.posX, pack.posY);
    //       }
 //   }
}

void Rtype::Game::Client::RtypeClientGameClient::onGetLAUNCHPackage(LAUNCHPackageGame const &pack)
{
    OnDiscoveringPackage(pack);
    //todo resolve launch package
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
    SaltyEngine::Input::VirtualInputManager::SetAxis(pack.axes, pack.value);
    //todo resolve failure package
//    InputKey::SetAxis(pack.axes, pack.);
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

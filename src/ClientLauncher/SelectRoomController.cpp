#include <Rtype/Game/Client/GameClientObject.hpp>
#include "RoomNetworkSaltyEngine/RoomNetworkManager.hpp"
#include "ClientLauncher/SelectRoomController.hpp"
#include "SaltyEngine/SFML.hpp"

SelectRoomController::SelectRoomController(SaltyEngine::GameObject *obj) : SaltyEngine::SaltyBehaviour("SelectRoomController", obj)
{

}

SelectRoomController::~SelectRoomController()
{
}

void SelectRoomController::Start() {

    SaltyEngine::GameObject *obj = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    SaltyEngine::GUI::SFML::LabelList *ll = obj->AddComponent<SaltyEngine::GUI::SFML::LabelList>();
    sf::Font *font = SaltyEngine::SFML::AssetManager::Instance().GetFont("SFSquareHead");
    obj->transform.SetPosition(SaltyEngine::Vector2(360, 200));

//    ll->AddLabel(obj->AddComponent<SaltyEngine::GUI::SFML::Label>("Item 1", 30, font));
//    ll->AddLabel(obj->AddComponent<SaltyEngine::GUI::SFML::Label>("Item 2", 30, font));
//    ll->AddLabel(obj->AddComponent<SaltyEngine::GUI::SFML::Label>("Item 3", 30, font));
//    ll->AddLabel(obj->AddComponent<SaltyEngine::GUI::SFML::Label>("Item 4", 30, font));
//    ll->AddLabel(obj->AddComponent<SaltyEngine::GUI::SFML::Label>("Item 5", 30, font));

    m_create_button = gameObject->transform.GetChild(3)->gameObject;
    gameObject->GetComponent<SaltyEngine::GUI::SFML::Button>()->onClick.AddListener(
            "create",
            std::bind(&SelectRoomController::Create, this)
    );
    m_select_sprite = SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/menu_room");
    m_create_sprite = SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/menu_create");

    std::cout << "start ?" << this << std::endl;

    m_roomNetworkManager = SaltyEngine::GameObject::Find("RoomNetworkManager");

    if (m_roomNetworkManager) {
        std::cout << "on set le network transition" << std::endl;
        m_roomNetworkManager->GetComponent<RoomNetworkManager>()->GetNetworkManager()->SetTransitionNetworkManager(
                this);
        std::list<GETPackageRoom *> const &list = m_roomNetworkManager->GetComponent<RoomNetworkManager>()->GetNetworkManager()->GetPackages();
        for (GETPackageRoom *getPackageRoom : list) {
            ListRoomGestion(*getPackageRoom);
        }
        m_roomNetworkManager->GetComponent<RoomNetworkManager>()->GetNetworkManager()->canAddGETPackage = false;

        //TODO A ENLEVER
        m_roomNetworkManager->GetComponent<RoomNetworkManager>()->SendJoin(1);
    }
}

void SelectRoomController::Create() {
    SaltyEngine::SFML::SpriteRenderer *sprr = gameObject->GetComponent<SaltyEngine::SFML::SpriteRenderer>();
    sprr->SetSprite(m_select_sprite);
}

void SelectRoomController::ListRoomGestion(GETPackageRoom const &pack) {
    std::cout << "listRoomGestion" << std::endl;
    std::cout << pack << std::endl;
    bool check = false;

    for (GETPackageRoom *getPackageRoom : listActualRoom) {
        if (getPackageRoom->roomID == pack.roomID) {
            getPackageRoom->roomPlayer = pack.roomPlayer;
            getPackageRoom->launch = pack.launch;
            check = true;
        }
    }
    if (!check) {
        GETPackageRoom *getPackageRoom = new GETPackageRoom(pack.roomPlayer, pack.roomPlayerMax, std::string(pack.name),
                                                            pack.roomID, pack.mapID, pack.launch);
        listActualRoom.push_back(getPackageRoom);
    }

    std::cout << "ON DISPLAY LA ROOM" << std::endl;
    for (GETPackageRoom *getPackageRoom : listActualRoom) {
        std::cout << *getPackageRoom << std::endl;
    }
}

SaltyEngine::Component *SelectRoomController::CloneComponent(SaltyEngine::GameObject *const obj)
{
    return new SelectRoomController(obj);
}

void SelectRoomController::OnMouseEnter() {
//    Debug::PrintSuccess("Mouse Enter");
}

void SelectRoomController::OnMouseOver() {
    //Debug::PrintInfo("Mouse Over");
}

void SelectRoomController::OnMouseExit() {
//    Debug::PrintSuccess("Mouse Exit");
}

void SelectRoomController::onGetAUTHENTICATE(AUTHENTICATEPackageRoom const& ) {

}

void SelectRoomController::onGetCREATE(CREATEPackageRoom const& ) {

}

void SelectRoomController::onGetJOIN(JOINPackageRoom const& ) {

}

void SelectRoomController::onGetQUIT(QUITPackageRoom const& ) {

}

void SelectRoomController::onGetPLUGGED(PLUGGEDPackageRoom const& ) {

}

void SelectRoomController::onGetSWAP(SWAPPackageRoom const &swapPackageRoom) {
    std::string ip = Network::Socket::ASocket::getIPFromUInt(swapPackageRoom.addrIP);
    unsigned int port = swapPackageRoom.port;
    unsigned int secret = swapPackageRoom.secret;

    m_roomNetworkManager->GetComponent<RoomNetworkManager>()->SetUDPIP(ip);
    m_roomNetworkManager->GetComponent<RoomNetworkManager>()->SetUDPPort(port);
    m_roomNetworkManager->GetComponent<RoomNetworkManager>()->SetUDPSecret(secret);

    std::cout << "lancement sur le port " << port << " avec ip " << ip << " avec secret " << secret << std::endl;

    m_roomNetworkManager->GetComponent<RoomNetworkManager>()->GetNetworkManager()->SetTransitionNetworkManager(
            NULL);
    m_roomNetworkManager->GetComponent<RoomNetworkManager>()->GetNetworkManager()->canAddGETPackage = true;
    SaltyEngine::Engine::Instance().LoadScene("scene2");

    SaltyEngine::GameObject *gameManager = SaltyEngine::GameObject::Find("GameManager");

    if (gameManager) {
        gameManager->AddComponent<Rtype::Game::Client::GameClientObject>(ip, port, secret);
    }

}

void SelectRoomController::onGetGET(GETPackageRoom const& room) {
//    std::cout << "toto" << std::endl;
//    std::cout << room << std::endl;
    ListRoomGestion(room);
}

void SelectRoomController::onGetFAILURE(FAILUREPackageRoom const& ) {

}

void SelectRoomController::onGetLAUNCH(LAUNCHPackageRoom const& ) {

}

void SelectRoomController::onGetDELETE(DELETEPackageRoom const &deletePackageRoom) {
    std::list<GETPackageRoom *>::iterator it = listActualRoom.begin();
    while (it != listActualRoom.end()) {
        if ((*it)->roomID == deletePackageRoom.roomID) {
            delete (*it);
            listActualRoom.erase(it);
            return ;
        }
        ++it;
    }
}

void SelectRoomController::onGetCHAT(CHATPackageRoom const& ) {

}

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
    SaltyEngine::GUI::SFML::LabelList *ll = gameObject->AddComponent<SaltyEngine::GUI::SFML::LabelList>();
    sf::Font *font = SaltyEngine::SFML::AssetManager::Instance().GetFont("SFSquareHead");

    ll->AddLabel(gameObject->AddComponent<SaltyEngine::GUI::SFML::Label>("Item 1", 30, font));
    ll->AddLabel(gameObject->AddComponent<SaltyEngine::GUI::SFML::Label>("Item 2", 30, font));
    ll->AddLabel(gameObject->AddComponent<SaltyEngine::GUI::SFML::Label>("Item 3", 30, font));
    ll->AddLabel(gameObject->AddComponent<SaltyEngine::GUI::SFML::Label>("Item 4", 30, font));
    ll->AddLabel(gameObject->AddComponent<SaltyEngine::GUI::SFML::Label>("Item 5", 30, font));

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
    }
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

void SelectRoomController::onGetSWAP(SWAPPackageRoom const& ) {

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

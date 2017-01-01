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
    obj->SetName("GameObjectLabelList");
    obj->AddComponent<SaltyEngine::GUI::SFML::LabelList>();

    labelListObj = obj;
    obj->transform.SetPosition(SaltyEngine::Vector2(360, 200));

    m_create_button = gameObject->transform.GetChild(3)->gameObject;
    m_create_button->GetComponent<SaltyEngine::GUI::SFML::Button>()->onClick.AddListener(
            "create",
            std::bind(&SelectRoomController::Create, this)
    );
    gameObject->transform.GetChild(1)->gameObject->GetComponent<SaltyEngine::GUI::SFML::Button>()->onClick.AddListener(
            "join",
            std::bind(&SelectRoomController::Join, this)
    );
    gameObject->transform.GetChild(2)->gameObject->GetComponent<SaltyEngine::GUI::SFML::Button>()->onClick.AddListener(
            "quit",
            std::bind(&SelectRoomController::Quit, this)
    );

    m_select_sprite = SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/menu_room");
    m_create_sprite = SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/menu_create");

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
//        m_roomNetworkManager->GetComponent<RoomNetworkManager>()->SendJoin(1);
    }
}

void SelectRoomController::Join() {
    std::cout << "JOIN" << std::endl;
    SaltyEngine::GameObject *obj = labelListObj;
    SaltyEngine::GUI::SFML::LabelList *ll = NULL;
    if (obj)
        ll = obj->GetComponent<SaltyEngine::GUI::SFML::LabelList>();
    if (ll) {
        size_t index = ll->GetIndex();
        size_t it = 0;

        for (GETPackageRoom *getPackageRoom :  listActualRoom) {
            if (it == index) {
                _getPackageRoom = getPackageRoom;
                m_roomNetworkManager->GetComponent<RoomNetworkManager>()->SendJoin(getPackageRoom->roomID);
                if (getPackageRoom->roomPlayer + 1 == getPackageRoom->roomPlayerMax) {
                    launch = true;
                }
            }
            ++it;
        }
    }
}

void SelectRoomController::Quit() {
    SaltyEngine::Engine::Instance().Stop();
}

void SelectRoomController::Create() {
    SaltyEngine::SFML::SpriteRenderer *sprr = gameObject->transform.GetChild(0)->gameObject->GetComponent<SaltyEngine::SFML::SpriteRenderer>();
    if (sprr)
    {
        SaltyEngine::GameObject *gm = SaltyEngine::GameObject::FindHide("CreateMenu");
        if (gm)
            gm->SetActive(true);
        else
            std::cout << "NULL" << std::endl;
    }
}

void SelectRoomController::ListRoomGestion(GETPackageRoom const &pack) {
    SaltyEngine::GameObject *obj = labelListObj;
    sf::Font *font = SaltyEngine::SFML::AssetManager::Instance().GetFont("SFSquareHead");
    SaltyEngine::GUI::SFML::LabelList *ll = NULL;
    if (obj) {
        ll = obj->GetComponent<SaltyEngine::GUI::SFML::LabelList>();
    }

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
        std::cout << "enter check false" << std::endl;
        GETPackageRoom *getPackageRoom = new GETPackageRoom(pack.roomPlayer, pack.roomPlayerMax, std::string(pack.name),
                                                            pack.roomID, pack.mapID, pack.launch);
        listActualRoom.push_back(getPackageRoom);
        if (ll) {
            std::cout << "ajout d'un label" << std::endl;
            ll->AddLabel(obj->AddComponent<SaltyEngine::GUI::SFML::Label>(std::string(pack.name), 30, font));
        }
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
//    m_roomNetworkManager->GetComponent<RoomNetworkManager>()->SendLaunch(1);
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

void SelectRoomController::onGetJOIN(JOINPackageRoom const &join) {
    if (launch)
        m_roomNetworkManager->GetComponent<RoomNetworkManager>()->SendLaunch(join.roomID);
}

void SelectRoomController::onGetQUIT(QUITPackageRoom const& ) {

}

void SelectRoomController::onGetPLUGGED(PLUGGEDPackageRoom const& ) {

}

void SelectRoomController::onGetSWAP(SWAPPackageRoom const &swapPackageRoom) {
    SaltyEngine::GameObject *obj = labelListObj;
    SaltyEngine::GUI::SFML::LabelList *ll = NULL;
    if (obj)
        ll = obj->GetComponent<SaltyEngine::GUI::SFML::LabelList>();

    if (ll)
        ll->RemoveAllLabel();


    std::string ip = Network::Socket::ASocket::getIPFromUInt(swapPackageRoom.addrIP);
    unsigned int port = swapPackageRoom.port;
    unsigned int secret = swapPackageRoom.secret;

    m_roomNetworkManager->GetComponent<RoomNetworkManager>()->SetUDPIP(ip);
    m_roomNetworkManager->GetComponent<RoomNetworkManager>()->SetUDPPort(port);
    m_roomNetworkManager->GetComponent<RoomNetworkManager>()->SetUDPSecret(secret);

    std::cout << "lancement sur le port " << port << " avec ip " << ip << " avec secret " << secret << std::endl;

    m_roomNetworkManager->GetComponent<RoomNetworkManager>()->GetNetworkManager()->SetTransitionNetworkManager(NULL);
    m_roomNetworkManager->GetComponent<RoomNetworkManager>()->GetNetworkManager()->canAddGETPackage = true;

        SaltyEngine::Engine::Instance().LoadScene("scene2");

    SaltyEngine::GameObject *gameManager = SaltyEngine::GameObject::FindGameObjectWithTag(SaltyEngine::Layer::Tag::GameManager);

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
    size_t i = 0;

    std::cout << deletePackageRoom << std::endl;
    SaltyEngine::GameObject *obj = labelListObj;
    SaltyEngine::GUI::SFML::LabelList *ll = NULL;
    if (obj)
        ll = obj->GetComponent<SaltyEngine::GUI::SFML::LabelList>();

    std::list<GETPackageRoom *>::iterator it = listActualRoom.begin();
    while (it != listActualRoom.end()) {
        if ((*it)->roomID == deletePackageRoom.roomID) {
            delete (*it);
            listActualRoom.erase(it);
            if (ll)
                ll->RemoveLabel(i);
            return ;
        }
        ++i;
        ++it;
    }
}

void SelectRoomController::onGetCHAT(CHATPackageRoom const& ) {

}

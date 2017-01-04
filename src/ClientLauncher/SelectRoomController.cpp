#include <Rtype/Game/Client/GameClientObject.hpp>
#include <Rtype/Game/Server/GameServerObject.hpp>
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

    Debug::PrintError("Je suis là");
    sf::Font *font = SaltyEngine::SFML::AssetManager::Instance().GetFont("SFSquareHead");
    const SaltyEngine::Engine &engine = SaltyEngine::Engine::Instance();

    SaltyEngine::GameObject *select_menu = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    select_menu->SetName("SelectMenu");

    SaltyEngine::GameObject *background = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    background->AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/menu_room"), SaltyEngine::Layout::background);
    background->transform.SetParent(&select_menu->transform);

    SaltyEngine::GameObject *join_button = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    join_button->AddComponent<SaltyEngine::GUI::SFML::Label>("Join Game", 54, font);
    join_button->SetName("Join Button");
    SaltyEngine::SFML::Sprite *normal = SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button");
    SaltyEngine::SFML::Sprite *over = SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button_over");
    normal->setScale(1.5f, 1.7f);
    over->setScale(1.5f, 1.7f);
    join_button->AddComponent<SaltyEngine::GUI::SFML::Button>(normal, over);
    join_button->transform.SetParent(&select_menu->transform);
    join_button->transform.SetPosition(-102.0f, 70.0f);


    SaltyEngine::GameObject *quit_button = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    quit_button->AddComponent<SaltyEngine::GUI::SFML::Label>("Quit Game", 54, font);
    quit_button->SetName("Quit Button");
    normal = SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button");
    over = SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button_over");
    normal->setScale(2.0f, 2.0f);
    over->setScale(2.0f, 2.0f);
    quit_button->AddComponent<SaltyEngine::GUI::SFML::Button>(normal, over);
    quit_button->transform.SetParent(&select_menu->transform);
    quit_button->transform.SetPosition(570.0f, 290.0f);

    SaltyEngine::GameObject *create_button = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    create_button->AddComponent<SaltyEngine::GUI::SFML::Label>("Create Game", 54, font);
    create_button->SetName("Create Button");
    normal = SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button");
    over = SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button_over");
    normal->setScale(2.0f, 2.0f);
    over->setScale(2.0f, 2.0f);
    create_button->AddComponent<SaltyEngine::GUI::SFML::Button>(normal, over);
    create_button->transform.SetParent(&select_menu->transform);
    create_button->transform.SetPosition(-260.0f, 385.0f);

    SaltyEngine::GameObject *display_selected = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    display_selected->AddComponent<SaltyEngine::GUI::SFML::Label>("Please select a map...", 25, font);
    display_selected->transform.SetParent(&select_menu->transform);
    display_selected->transform.SetPosition(-540.0f, 70.0f);

    SaltyEngine::GameObject *create_menu = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    create_menu->SetName("CreateMenu");

    SaltyEngine::GameObject *background_create = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    background_create->AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/menu_create"), SaltyEngine::Layout::backgroundColor);
    background_create->transform.SetParent(&create_menu->transform);

    SaltyEngine::GameObject *create_game_button = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    create_game_button->AddComponent<SaltyEngine::GUI::SFML::Label>("Create !", 54, font);
    create_game_button->SetName("Create menu");
    normal = SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button");
    over = SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button_over");
    normal->setScale(1.5f, 1.7f);
    over->setScale(1.5f, 1.7f);
    create_game_button->AddComponent<SaltyEngine::GUI::SFML::Button>(normal, over);
    create_game_button->transform.SetParent(&create_menu->transform);
    create_game_button->transform.SetPosition(670.0f, 250.0f);

    SaltyEngine::GameObject *cancel_button = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    cancel_button->AddComponent<SaltyEngine::GUI::SFML::Label>("Cancel", 54, font);
    cancel_button->SetName("Cancel Button");
    normal = SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button");
    over = SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button_over");
    normal->setScale(1.5f, 1.7f);
    over->setScale(1.5f, 1.7f);
    cancel_button->AddComponent<SaltyEngine::GUI::SFML::Button>(normal, over);
    cancel_button->transform.SetParent(&create_menu->transform);
    cancel_button->transform.SetPosition(670.0f, 410.0f);

    SaltyEngine::GameObject *text_box = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    SaltyEngine::GUI::SFML::Label *l = text_box->AddComponent<SaltyEngine::GUI::SFML::Label>("Number player 1-4: ", 40, font);
    text_box->AddComponent<SaltyEngine::GUI::SFML::TextBox>(l, sf::Vector2f(308.0f, 50.0f), 50, font, sf::Color::White, sf::Color(0x246b9cff), sf::Color(0xbcdbe9ff), 4, 1);
    text_box->SetName("NumberPlayer");
    text_box->transform.SetPosition(-695.0f, -475.0f);
    text_box->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));
    text_box->transform.SetParent(&create_menu->transform);

    SaltyEngine::GameObject *label_list = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    label_list->SetName("ListScene");
    SaltyEngine::GUI::SFML::LabelList *ll = label_list->AddComponent<SaltyEngine::GUI::SFML::LabelList>();
    ll->AddLabel(text_box->AddComponent<SaltyEngine::GUI::SFML::Label>("scene2-2", 30, font));
    ll->AddLabel(text_box->AddComponent<SaltyEngine::GUI::SFML::Label>("scene4-4", 30, font));
    label_list->transform.SetPosition(SaltyEngine::Vector2(-660, -170));
    label_list->transform.SetParent(&create_menu->transform);

    create_menu->SetActive(false);

    create_menu->transform.SetPosition(engine.GetSize().x, engine.GetSize().y);
    select_menu->transform.SetPosition(engine.GetSize().x, engine.GetSize().y);

    m_create_menu = create_menu;
    m_select_menu = select_menu;

    SaltyEngine::GameObject *obj = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    obj->SetName("GameObjectLabelList");
    obj->AddComponent<SaltyEngine::GUI::SFML::LabelList>();

    obj->transform.SetParent(&m_select_menu->transform);

    labelListObj = obj;
    obj->transform.SetPosition(SaltyEngine::Vector2(360, 200));

    m_create_button = m_select_menu->transform.GetChild(3)->gameObject;
    m_create_button->GetComponent<SaltyEngine::GUI::SFML::Button>()->onClick.AddListener(
            "create menu",
            std::bind(&SelectRoomController::DisplayCreateMenu, this)
    );
    m_select_menu->transform.GetChild(1)->gameObject->GetComponent<SaltyEngine::GUI::SFML::Button>()->onClick.AddListener(
            "join",
            std::bind(&SelectRoomController::Join, this)
    );
    m_select_menu->transform.GetChild(2)->gameObject->GetComponent<SaltyEngine::GUI::SFML::Button>()->onClick.AddListener(
            "quit",
            std::bind(&SelectRoomController::Quit, this)
    );

    m_create_menu->transform.GetChild(1)->gameObject->GetComponent<SaltyEngine::GUI::SFML::Button>()->onClick.AddListener(
            "create game",
            std::bind(&SelectRoomController::Create, this)
    );
    m_create_menu->transform.GetChild(2)->gameObject->GetComponent<SaltyEngine::GUI::SFML::Button>()->onClick.AddListener(
            "cancel",
            std::bind(&SelectRoomController::DisplaySelectMenu, this)
    );
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

//    sleep(5);
    SaltyEngine::Engine::Instance().LoadScene("scene2");
//    char const**av;
//    av = (const char **) new char*[7];
////    av[0] = strdup("r");
//    av[0] = strdup("i");
//    av[1] = strdup(ip.c_str());
//    av[2] = strdup("p");
//    av[3] = strdup(std::to_string(port).c_str());
//    av[4] = strdup("s");
//    av[5] = strdup(std::to_string(secret).c_str());
//    av[0] = strdup("-h");
////    av[1] = strdup("i");
//    av[1] = strdup(ip.c_str());
//    av[2] = strdup("-p");
//    av[3] = strdup(std::to_string(port).c_str());
//    av[4] = strdup("-s");
//    av[5] = strdup(std::to_string(secret).c_str());

//    SaltyEngine::Engine::Instance().SetArguments(6, av);
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

void SelectRoomController::DisplayCreateMenu() {
    m_select_menu->SetActive(false);
    m_create_menu->SetActive(true);
}

void SelectRoomController::DisplaySelectMenu() {
    m_select_menu->SetActive(true);
    m_create_menu->SetActive(false);
}

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void SelectRoomController::Create() {
    SaltyEngine::GameObject *gm = SaltyEngine::GameObject::Find("NumberPlayer");
    if (gm)
    {
        unsigned short players = (unsigned short) std::atoi(gm->GetComponent<SaltyEngine::GUI::SFML::TextBox>()->GetText().c_str());
        if (players <= 0)
            players = 1;
        else if (players > 4)
            players = 4;
        gm = SaltyEngine::GameObject::Find("ListScene");
        if (gm)
        {
            SaltyEngine::GUI::SFML::LabelList *ll = gm->GetComponent<SaltyEngine::GUI::SFML::LabelList>();
            std::vector<std::string> scene = split(ll->GetSelected(), '-');
            if (players == 1) {
                launch = true;
            }
            m_roomNetworkManager->GetComponent<RoomNetworkManager>()->SendCreate(
                    players, scene[0], (unsigned short) std::atoi(scene[1].c_str()));
        }
        DisplaySelectMenu();
    }
}
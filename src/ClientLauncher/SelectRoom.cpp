//
// Created by veyrie_f on 29/12/16.
//

#include "ClientLauncher/SelectRoom.hpp"
#include "ClientLauncher/SelectRoomController.hpp"
#include "RoomNetworkSaltyEngine/RoomNetworkManager.hpp"
#include "SaltyEngine/SFML.hpp"

SelectRoom::SelectRoom() : GameObject("SelectRoom")
{
    sf::Font *font = SaltyEngine::SFML::AssetManager::Instance().GetFont("SFSquareHead");
    const SaltyEngine::Engine &engine = SaltyEngine::Engine::Instance();

    SaltyEngine::GameObject *background = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    background->AddComponent<SaltyEngine::SFML::GUI::Image>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/menu_room"));
    background->transform.SetParent(&transform);
    SaltyEngine::GameObject *join_button = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    join_button->AddComponent<SelectRoomController>();
//    launch_button->AddComponent<RoomNetworkManager>("127.0.0.1", 4242);
    join_button->AddComponent<SaltyEngine::GUI::SFML::Label>("Join Game", 54, font);
    join_button->SetName("Join Button");
    SaltyEngine::SFML::Sprite *normal = SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button");
    SaltyEngine::SFML::Sprite *over = SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button_over");
    normal->setScale(1.5f, 1.7f);
    over->setScale(1.5f, 1.7f);
    join_button->AddComponent<SaltyEngine::GUI::SFML::Button>(normal, over);
    join_button->transform.SetParent(&transform);
    join_button->transform.SetPosition(-102.0f, 70.0f);


    SaltyEngine::GameObject *quit_button = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    quit_button->AddComponent<SelectRoomController>();
//    launch_button->AddComponent<RoomNetworkManager>("127.0.0.1", 4242);
    quit_button->AddComponent<SaltyEngine::GUI::SFML::Label>("Quit Game", 54, font);
    quit_button->SetName("Quit Button");
    normal = SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button");
    over = SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button_over");
    normal->setScale(2.0f, 2.0f);
    over->setScale(2.0f, 2.0f);
    quit_button->AddComponent<SaltyEngine::GUI::SFML::Button>(normal, over);
    quit_button->transform.SetParent(&transform);
    quit_button->transform.SetPosition(570.0f, 290.0f);

    SaltyEngine::GameObject *create_button = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    create_button->AddComponent<SelectRoomController>();
//    launch_button->AddComponent<RoomNetworkManager>("127.0.0.1", 4242);
    create_button->AddComponent<SaltyEngine::GUI::SFML::Label>("Create Game", 54, font);
    create_button->SetName("Create Button");
    normal = SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button");
    over = SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button_over");
    normal->setScale(2.0f, 2.0f);
    over->setScale(2.0f, 2.0f);
    create_button->AddComponent<SaltyEngine::GUI::SFML::Button>(normal, over);
    create_button->transform.SetParent(&transform);
    create_button->transform.SetPosition(-260.0f, 385.0f);

    SaltyEngine::GameObject *display_selected = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    display_selected->AddComponent<SaltyEngine::GUI::SFML::Label>("Please select a map...", 25, font);
    display_selected->transform.SetParent(&transform);
    display_selected->transform.SetPosition(-540.0f, 70.0f);

    transform.SetPosition(engine.GetSize().x, engine.GetSize().y);
}

SelectRoom::~SelectRoom()
{
}

LIB_EXPORT SaltyEngine::Object const*GetObjectPrefab()
{
    return new SelectRoom();
}
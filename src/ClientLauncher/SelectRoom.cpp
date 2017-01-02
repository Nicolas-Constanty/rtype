//
// Created by veyrie_f on 29/12/16.
//

#include "ClientLauncher/SelectRoom.hpp"
#include "ClientLauncher/SelectRoomController.hpp"
#include "RoomNetworkSaltyEngine/RoomNetworkManager.hpp"
#include "SaltyEngine/SFML.hpp"

SelectRoom::SelectRoom() : GameObject("SelectRoom")
{
    const SaltyEngine::Engine &engine = SaltyEngine::Engine::Instance();

    AddComponent<SelectRoomController>();
    transform.SetPosition(engine.GetSize().x, engine.GetSize().y);
}

SelectRoom::~SelectRoom()
{
}

LIB_EXPORT SaltyEngine::Object const*GetObjectPrefab()
{
    return new SelectRoom();
}
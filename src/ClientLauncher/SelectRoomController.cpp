//
// Created by veyrie_f on 29/12/16.
//

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

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
    std::cout << "start ?" << this << std::endl;
    m_roomNetworkManager = SaltyEngine::GameObject::Find("RoomNetworkManager");

    m_roomNetworkManager->GetComponent<RoomNetworkManager>()->GetNetworkManager()->SetTransitionNetworkManager(this);
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
    std::cout << room << std::endl;
}

void SelectRoomController::onGetFAILURE(FAILUREPackageRoom const& ) {

}

void SelectRoomController::onGetLAUNCH(LAUNCHPackageRoom const& ) {

}

void SelectRoomController::onGetDELETE(DELETEPackageRoom const& ) {

}

void SelectRoomController::onGetCHAT(CHATPackageRoom const& ) {

}

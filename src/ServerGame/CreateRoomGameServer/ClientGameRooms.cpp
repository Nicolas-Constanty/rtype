//
// Created by victor on 06/12/16.
//

#include "ServerGame/CreateRoomGameServer/ClientGameRooms.hpp"

ClientGameRooms::ClientGameRooms(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) : Network::TCP::ATCPClient(dispatcher), protocolServerManager(*this)
{

}

ClientGameRooms::ClientGameRooms(Network::Core::BasicConnection &ref) : Network::TCP::ATCPClient(ref.Dispatcher()), protocolServerManager(*this)
{

}

ClientGameRooms::~ClientGameRooms()
{
    std::cout << "\e[31mDestructor called\e[0m" << std::endl;
}

void ClientGameRooms::OnDataReceived(unsigned int len)
{
    std::cout << "Receiving " << buff << std::endl;
    while (protocolServerManager.handleProtocol(buff.buff(), buff.getLength())) {
        std::cout << "unknown cmd" << std::endl;
    }
}

void ClientGameRooms::onGetAUTHENTICATEPackage(AUTHENTICATEPackageServer const &obj) {
    std::cout << obj << std::endl;
}

void ClientGameRooms::onGetLAUNCHPackage(LAUNCHPackageServer const &obj) {
    std::cout << obj << std::endl;

    // CREATION de la room
    this->SendData<LAUNCHPackageServer>(*factory.create<LAUNCHPackageServer>(obj.roomPlayer, obj.mapID, obj.secret, 353121, 6565));
}

void ClientGameRooms::onGetSTATUSPackage(STATUSPackageServer const &obj) {
    std::cout << obj << std::endl;
}

void ClientGameRooms::OnDataSent(unsigned int len)
{
    std::cout << "Number of bytes sent: " << len << std::endl;
}

void ClientGameRooms::OnStart() {
    std::cout << "connected" << std::endl;
    this->SendData(*(factory.create<AUTHENTICATEPackageServer>(0, 3)));
}
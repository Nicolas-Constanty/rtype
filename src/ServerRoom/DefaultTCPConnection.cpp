//
// Created by victor on 29/11/16.
//

#include "ServerRoom/DefaultTCPConnection.hpp"
#include "Protocol/Room/ProtocolPrintRoomPackage.hpp"
#include "Protocol/Server/ProtocolPrintServerPackage.hpp"
#include "Protocol/Room/RoomPackageFactory.hpp"
#include "ServerRoom/RtypeRoomTCPConnection.hpp"
#include "ServerRoom/RtypeGameServerTCPConnection.hpp"
#include "Protocol/Server/ServerPackageFactory.hpp"

DefaultTCPConnection::DefaultTCPConnection(Network::Core::NativeSocketIOOperationDispatcher &dispatcher)
        : Network::TCP::ATCPClient(dispatcher), protocolRoomManager(*this), protocolServerManager(*this)
{
    std::cout << "CALLED DefaultTCPCOnnection constructor" << std::endl;
}

DefaultTCPConnection::DefaultTCPConnection(Network::Core::BasicConnection &ref)
        : Network::TCP::ATCPClient(ref.Dispatcher()), protocolRoomManager(*this), protocolServerManager(*this)
{
    std::cout << "CALLED DefaultTCPCOnnection constructor copy" << std::endl;
}

DefaultTCPConnection::~DefaultTCPConnection()
{
    std::cout << "\e[31mDestructor called\e[0m" << std::endl;
}

bool DefaultTCPConnection::OnDataReceived(unsigned int)
{
    std::cout << "Receiving " << buff << std::endl;
    if ((!protocolServerManager.handleProtocol(buff.buff(), buff.getLength()))) {
        if ((!protocolRoomManager.handleProtocol(buff.buff(), buff.getLength()))) {
            std::cout << "unknown command" << std::endl;
            Disconnect();
        }
    }
    return (true);
}

bool DefaultTCPConnection::OnDataSent(unsigned int len)
{
    std::cout << "Number of bytes sent: " << len << std::endl;
    return (true);
}

void DefaultTCPConnection::onGetAUTHENTICATEPackage(AUTHENTICATEPackageRoom const &authenticatePackageRoom) {
    std::cout << authenticatePackageRoom << std::endl;

    static unsigned int userID = 1;

    RtypeRoomTCPConnection *newc = new RtypeRoomTCPConnection(*this, authenticatePackageRoom.name, userID);
    clients->Move(this, newc);
    newc->WantReceive();
    newc->OnStart();
    ++userID;
}

void DefaultTCPConnection::onGetFAILUREPackage(FAILUREPackageRoom const &failurePackageRoom) {
    std::cout << failurePackageRoom << std::endl;
}

void DefaultTCPConnection::onGetAUTHENTICATEPackage(AUTHENTICATEPackageServer const &authenticatePackageServer) {
    std::cout << authenticatePackageServer << std::endl;

    static unsigned int userID = 1;

    RtypeGameServerTCPConnection *newc = new RtypeGameServerTCPConnection(*this, userID, authenticatePackageServer.roomNumber);
    clients->Move(this, newc);
    newc->WantReceive();
    newc->OnStart();
    ++userID;
}

bool DefaultTCPConnection::OnStart() {
    return (true);
}
